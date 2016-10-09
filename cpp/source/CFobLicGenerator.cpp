//
//  CFobLicGenerator.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-05-17.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "CFobLicGenerator.hpp"
#import <openssl/err.h>
#import <openssl/evp.h>
#import <openssl/pem.h>

#include "CFobInternal.hpp"
#include <vector>

extern "C" {
#include "encoder.h"
}

namespace cocoafob
{

CFobLicGenerator::CFobLicGenerator(CFobDSAKeyPEM &&dsaKey)
    : _dsaKey{std::move(dsaKey)}
{
}

CFobLicGenerator::CFobLicGenerator(const CFobDSAKeyPEM &&dsaKey)
    : _dsaKey{std::move(dsaKey)}
{
}

auto CFobLicGenerator::GenerateRegCodeForName(const std::string name) const -> std::tuple<bool, RegCode>
{
    if (name.length() == 0)
    {
        return {false, "Non-empty string required for name parameter"};
    }

    auto digest = std::vector<uint8_t>(SHA_DIGEST_LENGTH, 0);
    SHA1((unsigned char *)name.data(), name.length(), digest.data());

    auto siglen = 0u;
    auto sig = std::vector<uint8_t>(100, 0);
    const auto check = DSA_sign(NID_sha1,
                                digest.data(),
                                static_cast<int32_t>(digest.size()),
                                sig.data(),
                                &siglen,
                                _dsaKey);

    if (!check)
    {
        return {false, "Signing failed"};
    }

    const auto bufSize = base32_encoder_buffer_size(siglen);
    auto buffer = std::vector<char>(bufSize + 1, 0);
    buffer[bufSize] = 0;

    base32_encode(reinterpret_cast<uint8_t *>(buffer.data()),
                  bufSize,
                  sig.data(),
                  siglen);

    const auto regCode = CFob::Internal::FormatBase32EncodedString(buffer.data());

    return {true, regCode};
}
}
