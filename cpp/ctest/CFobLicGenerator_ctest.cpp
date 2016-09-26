//
//  CFobLicGenerator_ctest.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-05-17.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "catch.hpp"

#include "CFobLicGenerator.hpp"
#include "CFob_ctest_common.hpp"

SCENARIO("With valid data, generator should create registration code", "[base] [generator]")
{
    try
    {
        auto privateKeyPEM = GetPrivateKey();
        auto &&key = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Private, privateKeyPEM};
        CHECK(true);

        auto generator = cocoafob::CFobLicGenerator(std::forward<cocoafob::CFobDSAKeyPEM>(key));

        auto name = "Joe Bloggs";

        auto values = generator.GenerateRegCodeForName(name);
        auto sucess = std::get<0>(values);
        auto registrationCode = std::get<1>(values);

        CHECK(sucess);
        CHECK(registrationCode != "");
    }
    catch (...)
    {
        CHECK(false);
    }
}
