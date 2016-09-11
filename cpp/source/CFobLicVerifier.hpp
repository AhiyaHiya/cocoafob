//
//  CFobLicVerifier.hpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-05-24.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#ifndef CFobLicVerifier_hpp
#define CFobLicVerifier_hpp

#include "CFobCrypto.hpp"

namespace cocoafob
{
class CFobLicVerifier
{
  public:
    /**
     Precondition(s):
     \param publicKey must be valid; exception thrown if empty or invalid
     */
    CFobLicVerifier(const std::string publicKey);

    CFobLicVerifier(DSA *pubKey, const std::string dsaPubKeyAsString);

    auto VerifyRegCodeForName(const std::string regCode, const std::string forName) -> std::tuple<bool, ErrorMessage>;

  private:
    CFobLicVerifier() = delete;

    const std::string _publicKey;
};
}

#endif /* CFobLicVerifier_hpp */
