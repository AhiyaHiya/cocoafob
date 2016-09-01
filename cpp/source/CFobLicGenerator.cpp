//
//  CFobLicGenerator.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-05-17.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "CFobLicGenerator.hpp"

namespace cocoafob
{
    
    CFobLicGenerator::CFobLicGenerator(const std::string privateKey)
    {
        
    }
    
//CFobLicGenerator::CFobLicGenerator(DSA* privKey, const std::string privateKey)
//: _dsaPrivKey{privKey, ::DSA_free}
//, _privateKey(privateKey)
//{
//    ;
//}


auto CFobLicGenerator::SetPrivateKey() -> std::tuple<bool, ErrorMessage>
{
    return {false, "Not implemented"};
}

auto CFobLicGenerator::GenerateRegCodeForName(const std::string name) -> std::tuple<bool, RegCode>
{
    return {false, "Not implemented"};
}
}
