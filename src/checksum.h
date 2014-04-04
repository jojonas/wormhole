#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdint.h> // fuer uint8_t/uint32_t
#include <stddef.h> // fuer size_t
uint32_t adler32(const void *buf, size_t buflength);

#endif // CHECKSUM_H
