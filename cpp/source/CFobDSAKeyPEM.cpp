//
//  CFobDSAKeyPEM.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-31.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "CFobDSAKeyPEM.hpp"

namespace cocoafob
{
    
    CFobDSAKeyPEM::CFobDSAKeyPEM(const KeyType keyType,
                                 const std::string keyText)
    : _keyType{keyType}
    , _keyText{keyText}
    , _dsaKey{nullptr}
    {
        if (_keyText.length()==0)
        {
            throw std::exception();
        }
    }
    
    CFobDSAKeyPEM::operator DSA*() const
    {
        return _dsaKey;
    }
}