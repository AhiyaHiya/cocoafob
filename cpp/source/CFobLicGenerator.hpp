//
//  CFobLicGenerator.hpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-05-17.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#ifndef CFobLicGenerator_hpp
#define CFobLicGenerator_hpp

#include "CFobDataTypes.hpp"
#include "CFobCrypto.hpp"

/*
 Class follows model created in Swift
 */
class CFobLicGenerator
{
public:
    auto SetPrivateKey() -> std::tuple<bool, ErrorMessage>;
    
    auto GenerateRegCodeForName(const std::string name) -> std::tuple<bool, RegCode>;
    
private:
    template <typename T>
    friend T CreateCFobLicGenerator(const std::string privateKey );
    
    CFobLicGenerator(DSA* privKey, const std::string privateKey);
    
    CFobLicGenerator() = delete;
    
    std::unique_ptr<DSA, decltype(&::DSA_free)> _dsaPrivKey;
    const std::string _privateKey;
};

/*
 Factory function, which will check if the private key
 is valid before returning an instance to CFobLicGenerator.
 */
template <typename T = std::shared_ptr<CFobLicGenerator> >
T CreateCFobLicGenerator(const std::string privateKey )
{
    if (privateKey.length() == 0)
        return T{};
    
    auto dsaKeyResult = CFob::CreateDSAPrivateKeyFromPrivateKeyPEM(privateKey);
    
    const auto success = std::get<0>(dsaKeyResult);
    const auto reason  = std::get<1>(dsaKeyResult);
    (void)reason; // for debugging purposes
    
    if (success)
    {
        auto privKey = std::get<2>(dsaKeyResult);
        auto generator = T {new CFobLicGenerator(privKey, privateKey)};
        
        return generator;
    }
    else
    {
        return T{};
    }
}

#endif /* CFobLicGenerator_hpp */
