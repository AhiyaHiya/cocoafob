//
//  CFobCrypto.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-25.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "CFobCrypto.hpp"

#import <openssl/evp.h>
#import <openssl/err.h>
#import <openssl/pem.h>

namespace CFob
{
    

auto CreateDSAPubKeyFromPublicKeyPEM(const std::string publicKeyPEM) -> std::tuple<bool, ErrorMessage, DSA*>
{
    if (publicKeyPEM.length()==0)
    {
        return {false, std::string{"Empty PEM string detected"}, nullptr};
    }
    
    const auto completeKey = IsPublicKeyComplete(publicKeyPEM) ? publicKeyPEM : CompletePublicKeyPEM(publicKeyPEM);

    ERR_load_crypto_strings();
    
    auto bio    = BIO_MEM_uptr{BIO_new_mem_buf((void *)completeKey.c_str(), -1), ::BIO_free};
    auto dsa    = DSA_new();
    auto result = PEM_read_bio_DSA_PUBKEY(bio.get(), &dsa, NULL, NULL);
#if (1)
    if (result != nullptr)
    {
        return {true, std::string{"Success"}, dsa};
    }
    else
    {
#if defined(DEBUG)
        ERR_print_errors_fp(stdout);
#endif
        const auto message = std::string{ERR_error_string(ERR_get_error(), nullptr)};
        return {false, message, nullptr};
    }
#else
    (void)result;
    return {true, std::string{"Success"}, dsa};
#endif
}

auto IsPublicKeyComplete(const std::string publicKey) -> bool
{
    const auto found = publicKey.find(std::string{"-----BEGIN DSA PUBLIC KEY-----"}) != std::string::npos;
    return found;
}


auto CompletePublicKeyPEM(const std::string partialPEM) -> std::string
{
    using namespace std::string_literals;
    
    const auto dashes = "-----"s;
    const auto begin  = "BEGIN"s;
    const auto end    = "END"s;
    const auto key    = "KEY"s;
    const auto pub    = "DSA PUBLIC"s;
    
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
