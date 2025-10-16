#include <stdint.h>
#include "ahci.h"

int block_read(uint64_t lba, uint8_t *buf, size_t count) {
    // Stub: read from AHCI port
    return ahci_read_sector(0, lba, buf, count); // port 0
}

int block_write(uint64_t lba, const uint8_t *buf, size_t count) {
    // Stub: write to AHCI port
    return ahci_write_sector(0, lba, buf, count);
}#include <stdint.h>
#include "ahci.h"

int block_read(uint64_t lba, uint8_t *buf, size_t count) {
    // Stub: read from AHCI port
    return ahci_read_sector(0, lba, buf, count); // port 0
}

int block_write(uint64_t lba, const uint8_t *buf, size_t count) {
    // Stub: write to AHCI port
    return ahci_write_sector(0, lba, buf, count);
}
