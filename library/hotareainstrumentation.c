#ifndef INSTRUMENTATION_H
#define INSTRUMENTATION_H

#include <stdint.h>
#include <stdio.h>

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

const char *bb_filename = "basic_block.trace";
static FILE *bb_out = NULL;
const char *ac_filename = "access.trace";
static FILE *ac_out = NULL;

#define LOG_INFO(format, args...) fprintf(stderr, "[+] " format"\n", ##args)

void logInit(int functionId) {
    if (unlikely(bb_out == NULL)) {
        LOG_INFO("Opening log file %s...", bb_filename);
        bb_out = fopen(bb_filename, "w");
    }
    if (unlikely(ac_out == NULL)) {
        LOG_INFO("Opening log file %s...", ac_filename);
        ac_out = fopen(ac_filename, "w");
    }
}

void logExit(int functionId) {
    if (bb_out != NULL) {
        LOG_INFO("Closing log file %s...", bb_filename);
        fclose(bb_out);
        bb_out = NULL;
    }
    if (ac_out != NULL) {
        LOG_INFO("Closing log file %s...", ac_filename);
        fclose(ac_out);
        ac_out = NULL;
    }
}

void logBasicBlock(int blockid, int file, int line, int col) {
    if (bb_out == NULL)
        return;
    fprintf(bb_out, "%d %d %d\n", blockid, file, line);
    fflush(bb_out);
}

void logFnBegin(int functionId) {
}

void logFnEnd(int functionId) {
}

void logAlloc(void *addr, uint64_t size, uint64_t num, int type, int file, int line, int col) {
}

void logAccessPtr(void *ptr, void *value, int type, int file, int line, int col, int typeId, int varId) {
}

void logAccessStaticString(void *ptr, void *value, int type, int file, int line, int col, int typeId, int varId) {
}

void logAccessI8(void *ptr, uint8_t value, int type, int file, int line, int col, int typeId, int varId) {
    fprintf(ac_out, "%p %u %c %d %d %d %d %d\n", ptr, value, type, file, line, col, typeId, varId);
    fflush(ac_out);
}

void logAccessI16(void *ptr, uint16_t value, int type, int file, int line, int col, int typeId, int varId) {
    fprintf(ac_out, "%p %hu %c %d %d %d %d %d\n", ptr, value, type, file, line, col, typeId, varId);
    fflush(ac_out);
}

void logAccessI32(void *ptr, uint32_t value, int type, int file, int line, int col, int typeId, int varId) {
    fprintf(ac_out, "%p %u %c %d %d %d %d %d\n", ptr, value, type, file, line, col, typeId, varId);
    fflush(ac_out);
}

void logAccessI64(void *ptr, uint64_t value, int type, int file, int line, int col, int typeId, int varId) {
    fprintf(ac_out, "%p %lu %c %d %d %d %d %d\n", ptr, value, type, file, line, col, typeId, varId);
    fflush(ac_out);
}

/* =============================
 These don't exist: */

void logAccessF8(void *ptr, uint8_t value, int type, int file, int line, int col, int typeId, int varId) {
    fprintf(ac_out, "%p %c %c %d %d %d %d %d\n", ptr, value, type, file, line, col, typeId, varId);
    fflush(ac_out);
}

void logAccessF16(void *ptr, uint16_t value, int type, int file, int line, int col, int typeId, int varId) {
    fprintf(ac_out, "%p %hu %c %d %d %d %d %d\n", ptr, value, type, file, line, col, typeId, varId);
    fflush(ac_out);
}

/* ============================= */

void logAccessF32(void *ptr, float value, int type, int file, int line, int col, int typeId, int varId) {
    fprintf(ac_out, "%p %f %c %d %d %d %d %d\n", ptr, value, type, file, line, col, typeId, varId);
    fflush(ac_out);
}

void logAccessF64(void *ptr, double value, int type, int file, int line, int col, int typeId, int varId) {
    fprintf(ac_out, "%p %lf %c %d %d %d %d %d\n", ptr, value, type, file, line, col, typeId, varId);
    fflush(ac_out);
}
#endif

