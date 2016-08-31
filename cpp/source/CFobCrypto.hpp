//
//  CFobCrypto.hpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-25.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#ifndef CFobCrypto_hpp
#define CFobCrypto_hpp

#include <tuple>
#include "CFobDataTypes.hpp"

namespace CFob
{
    auto IsPublicKeyComplete(const std::string publicKey) -> bool;
    
    auto CompletePublicKeyPEM(const std::string partialPEM) -> std::string;
    
    auto CreateDSAPubKeyFromPublicKeyPEM(const std::string publicKey) -> std::tuple<bool, ErrorMessage, DSA*>;
    
    auto CreateDSAPrivateKeyFromPrivateKeyPEM(const std::string privateKey) -> std::tuple<bool, ErrorMessage, DSA*>;
}


#endif /* CFobCrypto_hpp */
