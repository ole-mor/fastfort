#include "can.h"
#include "hardware/spi.h"

// RP2040 has no native CAN peripheral.
// This implementation targets the MCP2515 CAN controller via SPI.
// MCP2515 register definitions (abbreviated)

#define MCP_RESET       0xC0
#define MCP_WRITE       0x02
#define MCP_READ        0x03
#define MCP_RTS_TXB0    0x81
#define MCP_READ_RXB0   0x90
#define MCP_CANSTAT     0x0E
#define MCP_CANCTRL     0x0F
#define MCP_CNF1        0x2A
#define MCP_CNF2        0x29
#define MCP_CNF3        0x28
#define MCP_TXB0SIDH    0x31
#define MCP_TXB0DLC     0x35
#define MCP_TXB0D0      0x36
#define MCP_RXB0SIDH    0x61
#define MCP_RXB0DLC     0x65
#define MCP_RXB0D0      0x66
#define MCP_EFLG        0x29
#define MCP_RXB0CTRL    0x60

#define CS_PIN  5   // default CS pin, adjust as needed

static spi_inst_t* can_spi = spi0;

static void mcp_write_reg(uint8_t addr, uint8_t value) {
    uint8_t buf[3] = {MCP_WRITE, addr, value};
    gpio_put(CS_PIN, 0);
    spi_write_blocking(can_spi, buf, 3);
    gpio_put(CS_PIN, 1);
}

static uint8_t mcp_read_reg(uint8_t addr) {
    uint8_t tx[3] = {MCP_READ, addr, 0x00};
    uint8_t rx[3] = {0};
    gpio_put(CS_PIN, 0);
    spi_write_read_blocking(can_spi, tx, rx, 3);
    gpio_put(CS_PIN, 1);
    return rx[2];
}

int8_t can_init(uint8_t bus_id, uint32_t baudrate) {
    spi_init(can_spi, 1000000);  // 1MHz SPI for MCP2515
    gpio_init(CS_PIN);
    gpio_set_dir(CS_PIN, GPIO_OUT);
    gpio_put(CS_PIN, 1);

    // reset MCP2515
    uint8_t reset_cmd = MCP_RESET;
    gpio_put(CS_PIN, 0);
    spi_write_blocking(can_spi, &reset_cmd, 1);
    gpio_put(CS_PIN, 1);

    // set 500kbps timing (assumes 8MHz crystal)
    mcp_write_reg(MCP_CNF1, 0x00);
    mcp_write_reg(MCP_CNF2, 0x90);
    mcp_write_reg(MCP_CNF3, 0x02);

    // normal mode
    mcp_write_reg(MCP_CANCTRL, 0x00);
    return 0;
}

int8_t can_deinit(uint8_t bus_id) {
    // put MCP2515 into sleep mode
    mcp_write_reg(MCP_CANCTRL, 0x20);
    spi_deinit(can_spi);
    return 0;
}

int8_t can_write(uint8_t bus_id, uint32_t id, const uint8_t* data, uint8_t len) {
    mcp_write_reg(MCP_TXB0SIDH, (id >> 3) & 0xFF);
    mcp_write_reg(MCP_TXB0SIDH + 1, (id & 0x07) << 5);
    mcp_write_reg(MCP_TXB0DLC, len & 0x0F);
    for (uint8_t i = 0; i < len; i++) {
        mcp_write_reg(MCP_TXB0D0 + i, data[i]);
    }
    uint8_t rts = MCP_RTS_TXB0;
    gpio_put(CS_PIN, 0);
    spi_write_blocking(can_spi, &rts, 1);
    gpio_put(CS_PIN, 1);
    return 0;
}

int8_t can_read(uint8_t bus_id, uint32_t* id, uint8_t* data, uint8_t* len) {
    uint8_t sidh = mcp_read_reg(MCP_RXB0SIDH);
    uint8_t sidl = mcp_read_reg(MCP_RXB0SIDH + 1);
    *id  = ((uint32_t)sidh << 3) | ((sidl >> 5) & 0x07);
    *len = mcp_read_reg(MCP_RXB0DLC) & 0x0F;
    for (uint8_t i = 0; i < *len; i++) {
        data[i] = mcp_read_reg(MCP_RXB0D0 + i);
    }
    return 0;
}

int8_t can_set_filter(uint8_t bus_id, uint32_t id, uint32_t mask) {
    // MCP2515 filter/mask registers — simplified
    mcp_write_reg(0x20, (id >> 3) & 0xFF);   // RXF0SIDH
    mcp_write_reg(0x21, (id & 0x07) << 5);   // RXF0SIDL
    mcp_write_reg(0x24, (mask >> 3) & 0xFF); // RXM0SIDH
    mcp_write_reg(0x25, (mask & 0x07) << 5); // RXM0SIDL
    return 0;
}

int16_t can_available(uint8_t bus_id) {
    uint8_t status = mcp_read_reg(MCP_RXB0CTRL);
    return (status & 0x01) ? 1 : 0;
}

int8_t can_flush(uint8_t bus_id) {
    // MCP2515 transmits immediately on RTS
    return 0;
}
