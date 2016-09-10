//
//  CFobDSAKeyPEM.hpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-31.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#ifndef CFobDSAKeyPEM_hpp
#define CFobDSAKeyPEM_hpp

#include "CFobDataTypes.hpp"

namespace cocoafob
{
    /**
     \brief Movable only struct for DSA key
     \remarks Throws on bad private/public keys passed in
     
     */
    struct CFobDSAKeyPEM
    {
    public:
        CFobDSAKeyPEM(const KeyType keyType, const std::string keyText);
        
        CFobDSAKeyPEM(CFobDSAKeyPEM const&) = delete;
        CFobDSAKeyPEM& operator=(CFobDSAKeyPEM const&) = delete;
        
        CFobDSAKeyPEM() = delete;
        
        operator DSA*() const;

        const KeyType     _keyType;
        const std::string _keyText;
        
        DSA* _dsaKey;
    };
}

#endif /* CFobDSAKeyPEM_hpp */
