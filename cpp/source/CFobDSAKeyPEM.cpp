//
//  CFobDSAKeyPEM.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-31.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "CFobDSAKeyPEM.hpp"
#include "CFobCrypto.hpp"

namespace cocoafob
{
    auto TakeCareOfKey(const KeyType keyType, const std::string keyText)
    {
        if (keyText.length()==0)
        {
            return std::string{};
        }
        
        auto isCompleteKey = IsKeyComplete(keyType, keyText);
        
        if(isCompleteKey)
        {
            return keyText;
        }
        else
        {
            auto completeKey = CompleteKeyPEM(keyType, keyText);
            return completeKey;
        }
    }
    
    CFobDSAKeyPEM::CFobDSAKeyPEM(const KeyType keyType,
                                 const std::string keyText)
    : _keyType{keyType}
    , _keyText{TakeCareOfKey(keyType, keyText)}
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
