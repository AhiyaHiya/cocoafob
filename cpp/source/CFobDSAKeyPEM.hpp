//
//  CFobDSAKeyPEM.hpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-31.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#ifndef CFobDSAKeyPEM_hpp
#define CFobDSAKeyPEM_hpp

#include <string>

namespace cocoafob
{
    enum KeyType
    {
        Public = 0,
        Private
    };
    
    /**
     \brief Movable only struct for DSA key
     \remarks Throws on bad private/public keys passed in
     
     */
    struct CFobDSAKeyPEM
    {
    public:
        CFobDSAKeyPEM(const KeyType keyType, const std::string keyText);
        
        CFobDSAKeyPEM() = delete;
        
        const KeyType _keyType;
        const std::string _keyText;
    };
}

#endif /* CFobDSAKeyPEM_hpp */
