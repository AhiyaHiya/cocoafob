//
//  CFob_ctest_common.hpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-26.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#ifndef CFob_ctest_common_hpp
#define CFob_ctest_common_hpp

#include "CFobDataTypes.hpp"

/*
 Functions for getting data used in testing.
 */
auto GetPartialPublicKey() -> std::string;
auto GetPublicKey() -> std::string;
auto GetPrivateKey() -> std::string;

auto GetRegCode() -> std::string;

#endif /* CFob_ctest_common_hpp */
