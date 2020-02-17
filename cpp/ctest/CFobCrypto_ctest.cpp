//
//  CFobCrypto_ctest.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-25.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "CFobCrypto.hpp"
#include "catch2/catch.hpp"

SCENARIO("Public key exercise", "[utility]")
{
    WHEN("An empty string is passed")
    {
        const auto result = cocoafob::IsPublicKeyComplete("");
        THEN("result should be false")
        {
            CHECK_FALSE(result);
        }
    }
    AND_WHEN("A garbage string is passed")
    {
        const auto result = cocoafob::IsPublicKeyComplete("Holy cow");
        THEN("result should be false")
        {
            CHECK_FALSE(result);
        }
    }
}
