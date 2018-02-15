#pragma once

#include <string>

using namespace std;

#if defined (_MSC_VER)
	//#include "MSDefines.h"
#else
#error "Only Windows & Visual Studio supported"
#endif

namespace gen
{

	/////////////////////////////////////
	//  Types

	// An entity UID is just a 32 bit value
	typedef unsigned int TEntityUID;
	const TEntityUID SystemUID = 0xffffffff;

} // namespace gen