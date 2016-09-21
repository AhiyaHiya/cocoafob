//
//  CFobDSAKeyPEM_ctest.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-31.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#define CATCH_CONFIG_MAIN
#include "CFobDSAKeyPEM.hpp"
#include "CFob_ctest_common.hpp"
#include "catch.hpp"

SCENARIO("When a bad key is passed in", "[struct]")
{
    THEN("The class should throw and never exist")
    {
        try
        {
            auto &&key = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Private, std::string{""}};
            CHECK(false);
        }
        catch (...)
        {
            CHECK(true);
        }
    }
}

TEST_CASE("Good key test", "[struct]")
{
    try
    {
        auto pubKey = GetPartialPublicKey();
        auto &&key = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Public, pubKey};
        CHECK(true);
    }
    catch (...)
    {
        CHECK(false);
    }
}
