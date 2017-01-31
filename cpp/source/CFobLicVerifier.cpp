//
//  CFobLicVerifier.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-05-24.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "CFobLicVerifier.hpp"
#include "CFobInternal.hpp"
#include <iostream>
#include <openssl/engine.h>
#include <openssl/pem.h>
#include <string>
#include <vector>

extern "C" {
#include "decoder.h"
}

using namespace std::string_literals;

namespace cocoafob
{
CFobLicVerifier::CFobLicVerifier(CFobDSAKeyPEM&& dsaKey)
    : _dsaKey{std::move(dsaKey)}
{
    ;
}

CFobLicVerifier::CFobLicVerifier(const CFobDSAKeyPEM&& dsaKey)
    : _dsaKey{std::move(dsaKey)}
{
    ;
}

auto CFobLicVerifier::VerifyRegCodeForName(const std::string regCode,
                                           const std::string forName) const
    -> std::tuple< bool, ErrorMessage >
{
    if (regCode.length() == 0)
    {
        return {false, "Empty regCode string detected"s};
    }

    if (forName.length() == 0)
    {
        return {false, "Empty name string detected"s};
    }

    const auto strippedRegCode = CFob::Internal::StripFormattingFromBase32EncodedString(regCode);
    const auto decodedSize     = base32_decoder_buffer_size(strippedRegCode.length());

    auto       sig     = std::vector< uint8_t >(decodedSize, 0);
    const auto sigSize = base32_decode(
        sig.data(), decodedSize, (unsigned char*)strippedRegCode.c_str(), strippedRegCode.length());

    auto digest = std::vector< uint8_t >(SHA_DIGEST_LENGTH, 0);
    SHA1((unsigned char*)forName.data(), forName.length(), digest.data());

    const auto check = DSA_verify(
        0, digest.data(), static_cast< int32_t >(digest.size()), sig.data(), (int)sigSize, _dsaKey);
    const auto result = check > 0 ? true : false;

    const auto resultMessage = result ? "Verified"s : "Failed"s;

    return std::make_tuple(result, resultMessage);
}
}
