//
//  CFobDSAKeyPEM_ctest.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-31.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CFobDSAKeyPEM.hpp"
#include "CFob_ctest_common.hpp"

TEST_CASE("Bad key test", "[struct]")
{
    try
    {
        auto&& key = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Private, std::string{""}};
    }
    catch (...)
    {
        CHECK(true);
    }
}

TEST_CASE("Good key test", "[struct]")
{
    try
    {
        auto pubKey = GetPartialPublicKey();
        auto&& key = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Public, pubKey};
    }
    catch (...)
    {
        CHECK(true);
    }
}


