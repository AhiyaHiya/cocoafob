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
#include "CFobDSAKeyPEM.hpp"

namespace cocoafob
{
class CFobLicVerifier
{
  public:
    CFobLicVerifier(CFobDSAKeyPEM &&dsaKey);
    CFobLicVerifier(const CFobDSAKeyPEM &&dsaKey);

    auto VerifyRegCodeForName(const std::string regCode, const std::string forName) -> std::tuple<bool, ErrorMessage>;

  private:
    CFobLicVerifier() = delete;

    CFobDSAKeyPEM _dsaKey;
};
}

#endif /* CFobLicVerifier_hpp */
