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

using namespace std::string_literals;

SCENARIO("With valid data, generator should create registration code", "[base] [generator]")
{
    try
    {
        const auto privateKeyPEM = GetPrivateKey();
        const auto &&key = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Private, privateKeyPEM};
        CHECK(true);

        const auto generator = cocoafob::CFobLicGenerator(std::forward<const cocoafob::CFobDSAKeyPEM>(key));

        const auto name = "decloner|Joe Bloggs"s;

        const auto values = generator.GenerateRegCodeForName(name);
        const auto sucess = std::get<0>(values);
        const auto registrationCode = std::get<1>(values);

        CHECK(sucess);
        
        const auto baselineRegCode = "GAWQE-F9AQP-XJCCL-PAFAX-NU5XX-EUG6W-KLT3H-VTEB9-A9KHJ-8DZ5R-DL74G-TU4BN-7ATPY-3N4XB-V4V27-Q"s;
        CHECK(registrationCode == baselineRegCode);
    }
    catch (...)
    {
        CHECK(false);
    }
}
