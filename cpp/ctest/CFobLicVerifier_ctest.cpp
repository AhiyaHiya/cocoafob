//
//  CFobLicVerifier_ctest.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-05-24.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "catch.hpp"
#include "CFob_ctest_common.hpp"
#include "CFobLicVerifier.hpp"

#if (0)
SCENARIO( "License generators should only be created if a public key is passed in", "[verifier] [publicKey]" )
{
    GIVEN("No public key")
    {
        THEN( "The constructor should throw" )
        {
            try
            {
                auto verifier = cocoafob::CFobLicVerifier{""};
            }
            catch (...)
            {
                CHECK(true);
            }
            
//            CHECK_THROWS(cocoafob::CFobLicVerifier{""});
        }
    }
}

SCENARIO( "License generators should be created when a public key is passed in", "[verifier] [publicKey]" )
{
    GIVEN("A public key")
    {
        const auto publicKey = GetPublicKey();
        auto licenseVer = cocoafob::CFobLicVerifier{publicKey};
        
        THEN( "The result should be a valid ptr" )
        {
//            CHECK(licenseVer != nullptr);
        }
    }
}
#endif
#if (0)
SCENARIO( "License verifier should handle bad data gracefully", "[verifier]" )
{
    GIVEN("A constructed non-nullptr instance to license verifier")
    {
        auto publicKey = GetPublicKey();
        auto licenseVer = cocoafob::CFobLicVerifier(publicKey);
        REQUIRE(licenseVer != nullptr);
        
        WHEN( "Bad data is passed in" )
        {
            auto result = licenseVer->VerifyRegCodeForName("", "");
            
            THEN( "The result should point to an error of some sort" )
            {
                auto boolResult = std::get<0>(result);
                REQUIRE_FALSE(boolResult);
                
                auto errorMessage = std::get<1>(result);
                REQUIRE( errorMessage.length() != 0 );
            }
        }
    }
}

SCENARIO( "License verifier should handle good data", "[verifier]" )
{
    GIVEN("A constructed non-nullptr instance to license verifier")
    {
        auto publicKey = GetPublicKey();
        auto licenseVer = CreateCFobLicVerifier(publicKey);
        REQUIRE(licenseVer != nullptr);
        
        WHEN( "Good data is passed in" )
        {
            const auto regCode = GetRegCode();
            const auto name    = std::string{"Joe Bloggs"};
            
            auto result = licenseVer->VerifyRegCodeForName(regCode, name);
            
            THEN( "The result should not have any error" )
            {
                auto boolResult = std::get<0>(result);
                CHECK(boolResult);
                
                auto errorMessage = std::get<1>(result);
                CHECK( errorMessage == "" );
            }
        }
    }
}

SCENARIO("License verifier should work with complete PEM key", "[verifier] [publicKey]")
{
    GIVEN("A constructed non-nullptr instance to license verifier")
    {
        const auto publicKey = GetPublicKey();
        auto licenseVer = CreateCFobLicVerifier(publicKey);
        REQUIRE(licenseVer != nullptr);
        
        WHEN( "Good data is passed in" )
        {
            const auto regCode = GetRegCode();
            const auto name    = std::string{"Joe Bloggs"};
            
            auto result = licenseVer->VerifyRegCodeForName(regCode, name);
            
            THEN( "The result should not have any error" )
            {
                auto boolResult = std::get<0>(result);
                CHECK(boolResult);
                
                auto errorMessage = std::get<1>(result);
                CHECK( errorMessage == "" );
            }
        }

    }
}


#endif
