#ifndef MACHO_CONFIG_H
#define MACHO_CONFIG_H

#include <stdint.h>

// ── Mach-O Magic / Identity ───────────────────────────────────────────────────
#define MACHO_MAGIC         0xFEEDFACF      // 64-bit little-endian
#define MACHO_CPU_TYPE      0x01000007      // x86_64
#define MACHO_CPU_SUBTYPE   0x00000003      // all
#define MACHO_FILETYPE      0x1             // MH_OBJECT (relocatable)
#define MACHO_FLAGS         0x0

// ── Load Command Types ────────────────────────────────────────────────────────
#define LC_SEGMENT_64       0x19
#define LC_MAIN             0x80000028
#define LC_LOAD_DYLIB       0xC

// ── Segment Config ────────────────────────────────────────────────────────────
#define SEG_TEXT_NAME       "__TEXT"
#define SEG_DATA_NAME       "__DATA"
#define SEG_TEXT_MAXPROT    7               // rwx
#define SEG_TEXT_INITPROT   5               // r-x
#define SEG_DATA_MAXPROT    7               // rwx
#define SEG_DATA_INITPROT   3               // rw-

// ── Section Types ─────────────────────────────────────────────────────────────
#define S_REGULAR           0x0
#define S_CSTRING_LITERALS  0x2
#define S_MOD_INIT_FUNC     0x9

// ── Section Config ────────────────────────────────────────────────────────────
#define SECT_CSTRING_NAME   "__cstring"
#define SECT_TEXT_NAME      "__text"
#define SECT_DATA_NAME      "__data"
#define SECT_CSTRING_ALIGN  0               // 2^0 = 1 byte
#define SECT_TEXT_ALIGN     4               // 2^4 = 16 byte (standard for code)
#define SECT_DATA_ALIGN     3               // 2^3 = 8 byte

// ── Output Config ─────────────────────────────────────────────────────────────
#define MACHO_OUTPUT_PATH   "./hello_world"
#define MACHO_PAYLOAD       "hello world"

// ── Structs ───────────────────────────────────────────────────────────────────

typedef struct {
    uint32_t magic;
    int32_t  cputype;
    int32_t  cpusubtype;
    uint32_t filetype;
    uint32_t ncmds;
    uint32_t sizeofcmds;
    uint32_t flags;
    uint32_t reserved;
} macho_header;

typedef struct {
    uint32_t cmd;
    uint32_t cmdsize;
} macho_load_cmd;

typedef struct {
    char     segname[16];
    uint64_t vmaddr;
    uint64_t vmsize;
    uint64_t fileoff;
    uint64_t filesize;
    int32_t  maxprot;
    int32_t  initprot;
    uint32_t nsects;
    uint32_t flags;
} macho_segment;

typedef struct {
    char     sectname[16];
    char     segname[16];
    uint64_t addr;
    uint64_t size;
    uint32_t offset;
    uint32_t align;
    uint32_t reloff;
    uint32_t nreloc;
    uint32_t flags;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t reserved3;
} macho_section;

static inline macho_header macho_default_header(uint32_t ncmds, uint32_t sizeofcmds) {
    macho_header h = {0};
    h.magic      = MACHO_MAGIC;
    h.cputype    = MACHO_CPU_TYPE;
    h.cpusubtype = MACHO_CPU_SUBTYPE;
    h.filetype   = MACHO_FILETYPE;
    h.ncmds      = ncmds;
    h.sizeofcmds = sizeofcmds;
    h.flags      = MACHO_FLAGS;
    h.reserved   = 0;
    return h;
}

static inline macho_section macho_cstring_section(uint64_t size, uint32_t file_offset) {
    macho_section s = {0};
    __builtin_memcpy(s.sectname, SECT_CSTRING_NAME, sizeof(SECT_CSTRING_NAME));
    __builtin_memcpy(s.segname,  SEG_TEXT_NAME,     sizeof(SEG_TEXT_NAME));
    s.size   = size;
    s.offset = file_offset;
    s.align  = SECT_CSTRING_ALIGN;
    s.flags  = S_CSTRING_LITERALS;
    return s;
}

static inline macho_segment macho_text_segment(uint64_t vmsize, uint64_t fileoff,
                                                uint64_t filesize, uint32_t nsects) {
    macho_segment s = {0};
    __builtin_memcpy(s.segname, SEG_TEXT_NAME, sizeof(SEG_TEXT_NAME));
    s.vmsize   = vmsize;
    s.fileoff  = fileoff;
    s.filesize = filesize;
    s.maxprot  = SEG_TEXT_MAXPROT;
    s.initprot = SEG_TEXT_INITPROT;
    s.nsects   = nsects;
    return s;
}

#endif
