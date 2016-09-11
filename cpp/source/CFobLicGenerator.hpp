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
#include "CFobDataTypes.hpp"

namespace cocoafob
{
/*
 Class follows model created in Swift
 */
class CFobLicGenerator
{
  public:
    CFobLicGenerator(const std::string privateKey);
    auto SetPrivateKey() -> std::tuple<bool, ErrorMessage>;
    auto GenerateRegCodeForName(const std::string name) -> std::tuple<bool, RegCode>;

  private:
    CFobLicGenerator() = delete;

    const std::string _privateKey;
};
}

#endif /* CFobLicGenerator_hpp */
