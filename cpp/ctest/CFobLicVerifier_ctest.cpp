//
//  CFobLicVerifier_ctest.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-05-24.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "catch.hpp"

#include "CFobLicVerifier.hpp"
#include "CFob_ctest_common.hpp"
#include <string>

using namespace std::string_literals;

SCENARIO("License verifier should only be created if a public key is passed in", "[verifier] [publicKey]")
{
    GIVEN("No public key")
    {
        THEN("The constructor should throw")
        {
            try
            {
                const auto dsaKey = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Private, ""s};
                const auto verifier = cocoafob::CFobLicVerifier{std::forward<const cocoafob::CFobDSAKeyPEM>(dsaKey)};
                CHECK(false);
            }
            catch (...)
            {
                CHECK(true);
            }
        }
    }
}

SCENARIO("License generators should be created when a public key is passed in", "[verifier] [publicKey]")
{
    GIVEN("A public key")
    {
        const auto publicKey = GetPublicKey();
        try
        {
            const auto dsaKey = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Public, publicKey};
            const auto licenseVer = cocoafob::CFobLicVerifier{std::forward<const cocoafob::CFobDSAKeyPEM>(dsaKey)};

            THEN("The operation should not have thrown by now")
            {
                CHECK(true);
            }
        }
        catch (...)
        {
            CHECK(false);
        }
    }
}


SCENARIO("License verifier should handle bad data gracefully", "[verifier]")
{
    GIVEN("A constructed non-nullptr instance to license verifier")
    {
        const auto pubKey = GetPartialPublicKey();
        const auto key = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Public, pubKey};
        
        const auto licenseVer = cocoafob::CFobLicVerifier(std::forward<const cocoafob::CFobDSAKeyPEM>(key));

        WHEN("Bad data is passed in")
        {
            auto result = licenseVer.VerifyRegCodeForName("", "");

            THEN("The result should point to an error of some sort")
            {
                auto boolResult = std::get<0>(result);
                REQUIRE_FALSE(boolResult);

                auto errorMessage = std::get<1>(result);
                REQUIRE(errorMessage.length() != 0);
            }
        }
    }
}

SCENARIO("License verifier should handle good data", "[verifier]")
{
    GIVEN("A constructed non-nullptr instance to license verifier")
    {
        const auto pubKey = GetPublicKey();
        const auto key = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Public, pubKey};
        
        const auto licenseVer = cocoafob::CFobLicVerifier(std::forward<const cocoafob::CFobDSAKeyPEM>(key));

        WHEN("Good data is passed in")
        {
            const auto regCode = GetRegCode();
            const auto name = std::string{"Joe Bloggs"};

            auto result = licenseVer.VerifyRegCodeForName(regCode, name);

            THEN("The result should not have any error")
            {
                auto boolResult = std::get<0>(result);
                CHECK(boolResult);

                auto errorMessage = std::get<1>(result);
                CHECK(errorMessage == "");
            }
        }
    }
}

SCENARIO("License verifier should work with complete PEM key", "[verifier] [publicKey]")
{
    GIVEN("A constructed non-nullptr instance to license verifier")
    {
        const auto pubKey = GetPartialPublicKey();
        const auto key = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Public, pubKey};
        const auto licenseVer = cocoafob::CFobLicVerifier(std::forward<const cocoafob::CFobDSAKeyPEM>(key));

        WHEN("Good data is passed in")
        {
            const auto regCode = GetRegCode();
            const auto name = std::string{"Joe Bloggs"};

            const auto result = licenseVer.VerifyRegCodeForName(regCode, name);

            THEN("The result should not have any error")
            {
                auto boolResult = std::get<0>(result);
                CHECK(boolResult);

                auto errorMessage = std::get<1>(result);
                CHECK(errorMessage == "");
            }
        }
    }
}

TEST_CASE("Exercise verifier", "[verifier]")
{
    const auto pubKey = GetPartialPublicKey();
    const auto key = cocoafob::CFobDSAKeyPEM{cocoafob::KeyType::Public, pubKey};

    const auto licenseVer = cocoafob::CFobLicVerifier(std::forward<const cocoafob::CFobDSAKeyPEM>(key));
}
