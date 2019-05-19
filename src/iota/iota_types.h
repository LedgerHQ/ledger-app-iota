#ifndef IOTA_TYPES_H
#define IOTA_TYPES_H

#include <stdint.h>
#include "kerl.h"

typedef int8_t trit_t;
typedef int8_t tryte_t;

#define MIN_TRIT_VALUE (-1)
#define MAX_TRIT_VALUE 1

#define MIN_TRYTE_VALUE (-13)
#define MAX_TRYTE_VALUE 13

#define TRITS_PER_TRYTE 3

#define MAX_IOTA_VALUE INT64_C(2779530283277761) // (3^33-1) / 2

#define MIN_SECURITY_LEVEL 1
#define MAX_SECURITY_LEVEL 3

#define NUM_HASH_TRYTES 81
#define NUM_HASH_TRITS (NUM_HASH_TRYTES * TRITS_PER_TRYTE)
#define NUM_HASH_BYTES (KERL_HASH_SIZE)
#define NUM_CHECKSUM_TRYTES 9
#define NUM_ADDRESS_TRYTES (NUM_HASH_TRYTES + NUM_CHECKSUM_TRYTES)

#endif // IOTA_TYPES_H
