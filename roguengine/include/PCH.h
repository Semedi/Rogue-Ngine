#ifndef PCH_H
#define PCH_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include <memory>

#include <Util.h>
#include <TextureManager.h>
#include <SoundBufferManager.h>
#include <iostream>

#include <modules/RE_imgui-sfml_binds/imgui.h>
#include <modules/RE_imgui-sfml_binds/imgui-SFML.h>

// Preprocessor trick to allow nested loops
#define _PP_CAT_IMPL(a, b) a ## b
#define _PP_CAT(a, b) _PP_CAT_IMPL(a, b)
#define _ID(identifier) _PP_CAT(auroraDetail_, identifier)
#define _LINE_ID(identifier) _PP_CAT(_ID(identifier), __LINE__)

/*
* Macro to emulate C++11 range-based loop
* Example:
* std::vector<int> v = ...;
* FOREACH(int& i, v)
*    i += 2;
* 
* Based on Foreach.hpp from SFML-Game-Development-Book
*/
#define FOREACH(declaration, container)																											\
	if (bool _LINE_ID(broken) = false) {} else																								\
	for (auto _LINE_ID(itr) = (container).begin(); _LINE_ID(itr) != (container).end() && !_LINE_ID(broken); ++_LINE_ID(itr))	\
	if (bool _LINE_ID(passed) = false) {} else																								\
	if (_LINE_ID(broken) = true, false) {} else																								\
	for (declaration = *_LINE_ID(itr); !_LINE_ID(passed); _LINE_ID(passed) = true, _LINE_ID(broken) = false)

#endif
