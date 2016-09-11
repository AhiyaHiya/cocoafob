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

namespace cocoafob
{
CFobLicVerifier::CFobLicVerifier(CFobDSAKeyPEM&& dsaKey)
    : _dsaKey{std::move(dsaKey)}
{
    ;
}

auto CFobLicVerifier::VerifyRegCodeForName(const std::string regCode, const std::string forName) -> std::tuple<bool, ErrorMessage>
{
    if (regCode.length() == 0)
    {
        return {false, std::string{"Empty regCode string detected"}};
    }

    if (forName.length() == 0)
    {
        return {false, std::string{"Empty name string detected"}};
    }

    const auto strippedRegCode = CFob::Internal::StripFormattingFromBase32EncodedString(regCode);
    const auto decodedSize = base32_decoder_buffer_size(strippedRegCode.length());

    auto sig = std::vector<uint8_t>(decodedSize, 0);
    const auto sigSize = base32_decode(sig.data(),
                                       decodedSize,
                                       (unsigned char *)strippedRegCode.c_str(),
                                       strippedRegCode.length());

    auto digest = std::vector<uint8_t>(0, SHA_DIGEST_LENGTH);
    SHA1((unsigned char *)forName.data(), forName.length(), digest.data());
#if (0)
    const auto check = DSA_verify(0,
                                  digest.data(),
                                  static_cast<int32_t>(digest.size()),
                                  sig.data(),
                                  (int)sigSize,
                                  _pub.get());
    auto result = check > 0 ? true : false;
#endif
    auto result = false;
    const auto resultMessage = result ? std::string{"Verified"} : std::string{"Failed"};

    return {result, resultMessage}; //std::make_tuple(result, resultMessage);
}
}
