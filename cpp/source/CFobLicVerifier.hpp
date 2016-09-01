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

namespace cocoafob
{
class CFobLicVerifier
{
public:
    /**
     Precondition(s):
     \param publicKey must be valid; exception thrown if empty or invalid
     */
    CFobLicVerifier(const std::string publicKey);
    
    CFobLicVerifier(DSA* pubKey, const std::string dsaPubKeyAsString);
    
    auto VerifyRegCodeForName(const std::string regCode, const std::string forName) -> std::tuple<bool, ErrorMessage>;
    
private:
    CFobLicVerifier() = delete;
    
//    std::unique_ptr<DSA, decltype(&::DSA_free)> _dsaPubKey;
    
    /// DSA, PEM
    const std::string _publicKey;
};

#if (0)
/*
 Factory function, which will check if the private key
 is valid before returning an instance to CFobLicGenerator.
 */
template <typename T = std::shared_ptr<CFobLicVerifier> >
T CreateCFobLicVerifier(const std::string publicKey )
{
    if (publicKey.length() == 0)
        return T{};
    
    auto dsaKeyResult = CFob::CreateDSAPubKeyFromPublicKeyPEM(publicKey);
    
    const auto success = std::get<0>(dsaKeyResult);
    const auto reason  = std::get<1>(dsaKeyResult);
    (void)reason; // for debugging purposes
    
    if (success)
    {
        auto pubKey = std::get<2>(dsaKeyResult);
        auto verifier = T {new CFobLicVerifier(pubKey, publicKey)};
        
        return verifier;
    }
    else
    {
        return T{};
    }
}
#endif
}

#endif /* CFobLicVerifier_hpp */
