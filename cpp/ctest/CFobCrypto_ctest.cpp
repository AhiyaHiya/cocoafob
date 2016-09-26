//
//  CFobCrypto_ctest.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-25.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "catch.hpp"

#include "CFobCrypto.hpp"

TEST_CASE("Public key exercise", "[utility]")
{
    // this should fail compilation
    CHECK(false);
}

SCENARIO("Public key exercise", "[utility]")
{
    WHEN("An empty string is passed")
    {
        auto result = cocoafob::IsPublicKeyComplete("");
        THEN("result should be false")
        {
            CHECK_FALSE(result);
        }
    }
    AND_WHEN("A garbage string is passed")
    {
        auto result = cocoafob::IsPublicKeyComplete("Holy cow");
        THEN("result should be false")
        {
            CHECK_FALSE(result);
        }
    }
}
