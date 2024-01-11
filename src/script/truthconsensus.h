// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020-2024 The Truth Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TRUTH_RAVENCONSENSUS_H
#define TRUTH_RAVENCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_TRUTH_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/truth-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBTRUTHCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define TRUTHCONSENSUS_API_VER 1

typedef enum truthconsensus_error_t
{
    truthconsensus_ERR_OK = 0,
    truthconsensus_ERR_TX_INDEX,
    truthconsensus_ERR_TX_SIZE_MISMATCH,
    truthconsensus_ERR_TX_DESERIALIZE,
    truthconsensus_ERR_AMOUNT_REQUIRED,
    truthconsensus_ERR_INVALID_FLAGS,
} truthconsensus_error;

/** Script verification flags */
enum
{
    truthconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    truthconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    truthconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    truthconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    truthconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    truthconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    truthconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    truthconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = truthconsensus_SCRIPT_FLAGS_VERIFY_P2SH | truthconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               truthconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | truthconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               truthconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | truthconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int truthconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, truthconsensus_error* err);

EXPORT_SYMBOL int truthconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, truthconsensus_error* err);

EXPORT_SYMBOL unsigned int truthconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // TRUTH_TRUTHCONSENSUS_H
