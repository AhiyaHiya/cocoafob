//
//  CFobCrypto.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-25.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "CFobCrypto.hpp"

#import <openssl/err.h>
#import <openssl/evp.h>
#import <openssl/pem.h>

using namespace std::string_literals;

namespace cocoafob
{

auto CreateDSAPubKeyFromPublicKeyPEM(const std::string publicKeyPEM) -> std::tuple<bool, ErrorMessage, DSA *>
{
    if (publicKeyPEM.length() == 0)
    {
        return {false, "Empty PEM string detected"s, nullptr};
    }

    const auto completeKey = IsPublicKeyComplete(publicKeyPEM) ? publicKeyPEM : CompletePublicKeyPEM(publicKeyPEM);

    ERR_load_crypto_strings();

    auto bio = BIO_MEM_uptr{BIO_new_mem_buf((void *)completeKey.c_str(), -1), ::BIO_free};
    auto dsa = DSA_new();
    auto result = PEM_read_bio_DSA_PUBKEY(bio.get(), &dsa, NULL, NULL);

    if (result != nullptr)
    {
        return {true, "Success"s, dsa};
    }
    else
    {
#if defined(DEBUG)
        ERR_print_errors_fp(stdout);
#endif
        const auto message = std::string{ERR_error_string(ERR_get_error(), nullptr)};
        return {false, message, nullptr};
    }
}

auto CreateDSAPrivateKeyFromPrivateKeyPEM(const std::string privateKey) -> std::tuple<bool, ErrorMessage, DSA *>
{
    if (privateKey.length() == 0)
    {
        return {false, "Empty PEM string detected"s, nullptr};
    }

    ERR_load_crypto_strings();

    auto dsa = DSA_new();
    auto bio = BIO_MEM_uptr{BIO_new_mem_buf((void *)privateKey.c_str(), -1), ::BIO_free};
    auto result = PEM_read_bio_DSAPrivateKey(bio.get(), &dsa, NULL, NULL);

    if (result != nullptr)
    {
        return {true, "Success"s, dsa};
    }
    else
    {
#if defined(DEBUG)
        ERR_print_errors_fp(stdout);
#endif
        const auto message = std::string{ERR_error_string(ERR_get_error(), nullptr)};
        return {false, message, nullptr};
    }
}

auto IsKeyComplete(const KeyType keyType, const std::string keyText) -> bool
{
    const auto keyTypeString = keyType == KeyType::Private ? "DSA PRIVATE"s : "PUBLIC"s;

    const auto beginKey = "-----BEGIN "s +
                          keyTypeString +
                          " KEY-----"s;

    const auto endKey = "-----END "s +
                        keyTypeString +
                        " KEY-----"s;

    const auto foundBeginning = keyText.find(beginKey) != std::string::npos;
    const auto foundEnd = keyText.find(endKey) != std::string::npos;

    return foundBeginning && foundEnd;
}

auto IsPublicKeyComplete(const std::string publicKey) -> bool
{
    const auto found = publicKey.find("-----BEGIN PUBLIC KEY-----"s) != std::string::npos;
    return found;
}

auto CompleteKeyPEM(const KeyType keyType, const std::string partialPEM) -> std::string
{
    const auto dashes = "-----"s;
    const auto begin = "BEGIN"s;
    const auto end = "END"s;
    const auto key = "KEY"s;
    const auto pub = (keyType == KeyType::Private ? "PRIVATE"s : "PUBLIC"s);
    
    auto pem = dashes;

    pem += begin;
    pem += " "s;
    pem += pub;
    pem += " "s;
    pem += key;
    pem += dashes;
    pem += "\n"s;
    pem += partialPEM;
    pem += dashes;
    pem += end;
    pem += " "s;
    pem += pub;
    pem += " "s;
    pem += key;
    pem += dashes;
    pem += "\n"s;

    return pem;
}

auto CompletePublicKeyPEM(const std::string partialPEM) -> std::string
{
    const auto dashes = "-----"s;
    const auto begin = "BEGIN"s;
    const auto end = "END"s;
    const auto key = "KEY"s;
    const auto pub = "DSA PUBLIC"s;

    auto pem = dashes;

    pem += begin;
    pem += " "s;
    pem += pub;
    pem += " "s;
    pem += key;
    pem += dashes;
    pem += "\n"s;
    pem += partialPEM;
    pem += dashes;
    pem += end;
    pem += " "s;
    pem += pub;
    pem += " "s;
    pem += key;
    pem += dashes;
    pem += "\n"s;

    return pem;
}

} // CFob
