//
//  CFobDSAKeyPEM.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-31.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "CFobDSAKeyPEM.hpp"
#include "CFobCrypto.hpp"

#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#include <stdexcept>

using namespace std::string_literals;

namespace cocoafob
{

CFobDSAKeyPEM::CFobDSAKeyPEM(const KeyType keyType,
                             const std::string keyText)
    : _keyType{keyType}, _keyText{CheckKey(keyText)}, _dsaKey{SetUpDSAPtr()}
{
    ;
}

CFobDSAKeyPEM::CFobDSAKeyPEM(CFobDSAKeyPEM &&other)
    : _keyType{other._keyType}, _keyText{other._keyText}, _dsaKey{other._dsaKey}
{
}

CFobDSAKeyPEM::CFobDSAKeyPEM(const CFobDSAKeyPEM &&other)
    : _keyType{other._keyType}, _keyText{other._keyText}, _dsaKey{other._dsaKey}
{
}

CFobDSAKeyPEM::operator DSA *() const
{
    return _dsaKey;
}

/**
     Precondition(s):
     - Non-empty string
     
     Postcondition(s):
     - Completes key if BEGIN/END missing from PEM string
     */
auto CFobDSAKeyPEM::CheckKey(const std::string keyText) -> std::string
{
    if (keyText.length() == 0)
    {
        throw std::invalid_argument("Non-empty DSA PEM key required"s);
    }

    const auto isCompleteKey = IsKeyComplete(_keyType, keyText);

    if (isCompleteKey)
    {
        return keyText;
    }
    else
    {
        const auto completeKey = CompleteKeyPEM(_keyType, keyText);
        return completeKey;
    }
}

auto CFobDSAKeyPEM::SetUpDSAPtr() -> DSA *
{
    auto dsa = DSA_new();
    auto bio = BIO_MEM_uptr{BIO_new_mem_buf((void *)_keyText.c_str(), -1), ::BIO_free};

    const auto result =
        _keyType == KeyType::Private ? PEM_read_bio_DSAPrivateKey(bio.get(), &dsa, NULL, NULL) : PEM_read_bio_DSA_PUBKEY(bio.get(), &dsa, NULL, NULL);

    if (result == nullptr)
    {
        ERR_load_crypto_strings();

        const auto message = (_keyType == KeyType::Private ? "Private"s : "Public"s) +
                             " key dsa failure: "s +
                             ERR_error_string(ERR_get_error(), nullptr);
        DSA_free(dsa);
        throw std::runtime_error(message);
    }
    else
    {
        return dsa;
    }
}
}
