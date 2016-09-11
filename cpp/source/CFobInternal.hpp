//
//  CFobInternal.hpp
//  cocoafob
//
//  Created by Jaime Rios on 2016-08-25.
//  Copyright © 2016 Jaime O. Rios. All rights reserved.
//

#ifndef CFobInternal_hpp
#define CFobInternal_hpp

#include "CFobDataTypes.hpp"

namespace CFob
{
namespace Internal
{
auto StripFormattingFromBase32EncodedString(std::string formattedString) -> std::string;
auto FormatBase32EncodedString(std::string stringToFormat) -> std::string;
}
}

#endif /* CFobInternal_hpp */
