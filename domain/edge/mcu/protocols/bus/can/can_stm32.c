#include "can.h"
#include "stm32f4xx_hal.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

static CAN_HandleTypeDef* buses[] = {&hcan1, &hcan2};

int8_t can_init(uint8_t bus_id, uint32_t baudrate) {
    // HAL init handled by generated code (MX_CANx_Init)
    HAL_CAN_Init(buses[bus_id]);
    HAL_CAN_Start(buses[bus_id]);
    return 0;
}

int8_t can_deinit(uint8_t bus_id) {
    HAL_CAN_Stop(buses[bus_id]);
    HAL_CAN_DeInit(buses[bus_id]);
    return 0;
}

int8_t can_write(uint8_t bus_id, uint32_t id, const uint8_t* data, uint8_t len) {
    CAN_TxHeaderTypeDef header = {
        .StdId = id,
        .IDE   = CAN_ID_STD,
        .RTR   = CAN_RTR_DATA,
        .DLC   = len,
    };
    uint32_t mailbox;
    HAL_StatusTypeDef status = HAL_CAN_AddTxMessage(buses[bus_id], &header, (uint8_t*)data, &mailbox);
    return status == HAL_OK ? 0 : -1;
}

int8_t can_read(uint8_t bus_id, uint32_t* id, uint8_t* data, uint8_t* len) {
    CAN_RxHeaderTypeDef header;
    HAL_StatusTypeDef status = HAL_CAN_GetRxMessage(buses[bus_id], CAN_RX_FIFO0, &header, data);
    if (status != HAL_OK) return -1;
    *id  = header.StdId;
    *len = header.DLC;
    return 0;
}

int8_t can_set_filter(uint8_t bus_id, uint32_t id, uint32_t mask) {
    CAN_FilterTypeDef filter = {
        .FilterIdHigh         = id << 5,
        .FilterIdLow          = 0x0000,
        .FilterMaskIdHigh     = mask << 5,
        .FilterMaskIdLow      = 0x0000,
        .FilterFIFOAssignment = CAN_RX_FIFO0,
        .FilterBank           = 0,
        .FilterMode           = CAN_FILTERMODE_IDMASK,
        .FilterScale          = CAN_FILTERSCALE_32BIT,
        .FilterActivation     = ENABLE,
    };
    HAL_CAN_ConfigFilter(buses[bus_id], &filter);
    return 0;
}

int16_t can_available(uint8_t bus_id) {
    return (int16_t)HAL_CAN_GetRxFifoFillLevel(buses[bus_id], CAN_RX_FIFO0);
}

int8_t can_flush(uint8_t bus_id) {
    while (HAL_CAN_GetTxMailboxesFreeLevel(buses[bus_id]) < 3);
    return 0;
}
