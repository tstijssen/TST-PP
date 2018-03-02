#pragma once

#include <string>

using namespace std;

#if defined (_MSC_VER)
	//#include "MSDefines.h"
#else
#error "Only Windows & Visual Studio supported"
#endif
typedef unsigned int TEntityUID;

namespace gen
{

	/////////////////////////////////////
	//  Types

	// An entity UID is just a 32 bit value
	const TEntityUID SystemUID = 0xffffffff;

} // namespace gen