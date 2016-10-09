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
     
     Precondition(s):
     - non-empty DSA PEM string; complete or partial
     strings are valid as input 
     
     Postcondition(s):
     - C++11 struct with valid DSA pointer 
     - Throws on bad private/public keys passed in
     */
struct CFobDSAKeyPEM
{
  public:
    CFobDSAKeyPEM(const KeyType keyType, const std::string keyText);

    // movable
    CFobDSAKeyPEM(CFobDSAKeyPEM &&other);
    CFobDSAKeyPEM(const CFobDSAKeyPEM &&other);

    // not-copyable
    CFobDSAKeyPEM(CFobDSAKeyPEM const &) = delete;
    CFobDSAKeyPEM &operator=(CFobDSAKeyPEM const &) = delete;

    CFobDSAKeyPEM() = delete;

    operator DSA *() const;

    const KeyType _keyType;
    const std::string _keyText;

    DSA *_dsaKey;

  private:
    auto CheckKey(const std::string keyText) -> std::string;
    auto SetUpDSAPtr() -> DSA *;
};
}

#endif /* CFobDSAKeyPEM_hpp */
