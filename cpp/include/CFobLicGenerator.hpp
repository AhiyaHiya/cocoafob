//
//  CFobLicGenerator.hpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-05-17.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#ifndef CFobLicGenerator_hpp
#define CFobLicGenerator_hpp

#include "CFobCrypto.hpp"
#include "CFobDSAKeyPEM.hpp"
#include "CFobDataTypes.hpp"

namespace cocoafob
{
/*
 Class follows model created in Swift
 */
class CFobLicGenerator
{
  public:
    CFobLicGenerator(CFobDSAKeyPEM &&dsaKey);
    CFobLicGenerator(const CFobDSAKeyPEM &&dsaKey);
    auto GenerateRegCodeForName(const std::string name) const -> std::tuple<bool, RegCode>;

  private:
    CFobLicGenerator() = delete;

    CFobDSAKeyPEM _dsaKey;
};
}

#endif /* CFobLicGenerator_hpp */
