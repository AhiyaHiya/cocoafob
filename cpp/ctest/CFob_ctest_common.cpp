//
//  CFob_ctest_common.cpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-26.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#include "CFob_ctest_common.hpp"

auto GetPartialPublicKey() -> std::string
{
    auto publicKey = std::string{""};

    publicKey += "MIHxMIGoBgcqhkj";
    publicKey += "OOAQBMIGcAkEA8wm04e0QcQRoAVJW";
    publicKey += "WnUw/4rQEKbLKjujJu6o\n";
    publicKey += "yE";
    publicKey += "v7Y2oT3itY5pbObgYCHEu9FBizqq7apsWYSF3YX";
    publicKey += "iRjKlg10wIVALfs9eVL10Ph\n";
    publicKey += "oV6zczFpi3C7FzWNAkBaPhALEKlgIltHsumHdTSBqaVoR1/bmlgw";
    publicKey += "/BCC13IAsW40\n";
    publicKey += "nkFNsK1OVwjo2ocn";
    publicKey += "3M";
    publicKey += "wW";
    publicKey += "4Rdq6uLm3DlENRZ5bYrTA";
    publicKey += "0QAAkEA4reDYZKAl1vx+8EI\n";
    publicKey += "MP/+";
    publicKey += "2Z7ekydHfX0sTMDgkxhtRm6qtcywg01X847Y9ySgNepqleD+Ka2Wbucj1pOr\n";
    publicKey += "y8MoDQ==\n";

    return publicKey;
}

auto GetPublicKey() -> std::string
{
    const auto publicKey = R"PEM(-----BEGIN PUBLIC KEY-----
MIHxMIGoBgcqhkjOOAQBMIGcAkEA8wm04e0QcQRoAVJWWnUw/4rQEKbLKjujJu6o
yEv7Y2oT3itY5pbObgYCHEu9FBizqq7apsWYSF3YXiRjKlg10wIVALfs9eVL10Ph
oV6zczFpi3C7FzWNAkBaPhALEKlgIltHsumHdTSBqaVoR1/bmlgw/BCC13IAsW40
nkFNsK1OVwjo2ocn3MwW4Rdq6uLm3DlENRZ5bYrTA0QAAkEA4reDYZKAl1vx+8EI
MP/+2Z7ekydHfX0sTMDgkxhtRm6qtcywg01X847Y9ySgNepqleD+Ka2Wbucj1pOr
y8MoDQ==
-----END PUBLIC KEY-----
)PEM";

    return publicKey;
}

auto GetPrivateKey() -> std::string
{
    const auto privateKeyPEM = R"PEM(-----BEGIN PRIVATE KEY-----
MIH5AgEAAkEA8wm04e0QcQRoAVJWWnUw/4rQEKbLKjujJu6oyEv7Y2oT3itY5pbO
bgYCHEu9FBizqq7apsWYSF3YXiRjKlg10wIVALfs9eVL10PhoV6zczFpi3C7FzWN
AkBaPhALEKlgIltHsumHdTSBqaVoR1/bmlgw/BCC13IAsW40nkFNsK1OVwjo2ocn
3MwW4Rdq6uLm3DlENRZ5bYrTAkEA4reDYZKAl1vx+8EIMP/+2Z7ekydHfX0sTMDg
kxhtRm6qtcywg01X847Y9ySgNepqleD+Ka2Wbucj1pOry8MoDQIVAIXgAB9GBLh4
keUwLHBtpClnD5E8
-----END PRIVATE KEY-----
)PEM";

    return privateKeyPEM;
}

auto GetRegCode() -> std::string
{
    return std::string{"GAWQE-F9AQP-XJCCL-PAFAX-NU5XX-EUG6W-KLT3H-VTEB9-A9KHJ-8DZ5R-DL74G-TU4BN-7ATPY-3N4XB-V4V27-Q"};
}
