#ifndef API_H
#define API_H

#include "iota_io.h"
#include "iota/signing.h"
#include "iota/bundle.h"

// state bit flags
#define BUNDLE_INITIALIZED (1 << 0)
#define BUNDLE_FINALIZED (1 << 1)
#define SIGNING_STARTED (1 << 2)

#define IO_STRUCT struct __attribute__((packed, may_alias))
typedef struct API_CTX {
    /// BIP32 path used for seed derivation
    unsigned int bip32_path[BIP32_PATH_MAX_LEN];
    uint8_t bip32_path_length;

    uint8_t security; ///< used security level

    unsigned char seed_bytes[NUM_HASH_BYTES]; ///< IOTA seed

    BUNDLE_CTX bundle_ctx;
    SIGNING_CTX signing_ctx;

    unsigned int state_flags;
} API_CTX;

/// global context with everything related to the current api state
extern API_CTX api;

#define SET_SEED_REQUIRED_STATE 0
#define SET_SEED_FORBIDDEN_STATE 0

typedef IO_STRUCT SET_SEED_INPUT
{
    uint8_t security;
    uint32_t bip32_path_length;
    uint32_t bip32_path[];
}
SET_SEED_INPUT;

#define PUBKEY_REQUIRED_STATE 0
#define PUBKEY_FORBIDDEN_STATE                                                 \
    (BUNDLE_INITIALIZED | BUNDLE_FINALIZED | SIGNING_STARTED)

typedef IO_STRUCT PUBKEY_INPUT
{
    uint32_t address_idx;
}
PUBKEY_INPUT;

typedef IO_STRUCT PUBKEY_OUTPUT
{
    char address[81];
}
PUBKEY_OUTPUT;

#define TX_REQUIRED_STATE 0
#define TX_FORBIDDEN_STATE (BUNDLE_FINALIZED)

typedef IO_STRUCT TX_INPUT
{
    char address[81];
    uint32_t address_idx;
    int64_t value;
    char tag[27];
    uint32_t current_index;
    uint32_t last_index;
    uint32_t timestamp;
}
TX_INPUT;

typedef IO_STRUCT TX_OUTPUT
{
    bool finalized;
    char bundle_hash[81];
}
TX_OUTPUT;

#define SIGN_REQUIRED_STATE (BUNDLE_FINALIZED)
#define SIGN_FORBIDDEN_STATE 0

typedef IO_STRUCT SIGN_INPUT
{
    uint32_t transaction_idx;
}
SIGN_INPUT;

typedef IO_STRUCT SIGN_OUTPUT
{
    char signature_fragment[SIGNATURE_FRAGMENT_SIZE * 81];
    bool fragments_remaining;
}
SIGN_OUTPUT;

#define GET_APP_CONFIG_REQUIRED_STATE 0
#define GET_APP_CONFIG_FORBIDDEN_STATE 0

// no GET_APP_CONFIG_INPUT

typedef IO_STRUCT GET_APP_CONFIG_OUTPUT
{
    uint8_t app_version_major;
    uint8_t app_version_minor;
    uint8_t app_version_patch;
    uint8_t app_max_bundle_size;
    uint8_t app_flags;
}
GET_APP_CONFIG_OUTPUT;

#define RESET_REQUIRED_STATE 0
#define RESET_FORBIDDEN_STATE 0

// no RESET_INPUT

// no RESET_OUTPUT

/** @brief Clear and initialize the entire API context. */
void api_initialize(void);

unsigned int api_pubkey(uint8_t p1, const unsigned char *input_data,
                        unsigned int len);
unsigned int api_tx(uint8_t p1, const unsigned char *input_data,
                    unsigned int len);
unsigned int api_sign(uint8_t p1, const unsigned char *input_data,
                      unsigned int len);
unsigned int api_get_app_config(uint8_t p1, const unsigned char *input_data,
                                unsigned int len);
unsigned int api_reset(uint8_t p1, const unsigned char *input_data,
                       unsigned int len);

/** @brief Callback function when bundle is accepted. */
void user_sign_tx(void);

#endif // API_H
