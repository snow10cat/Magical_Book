
#ifndef __EXTERNAL_LIB_H__
#define __EXTERNAL_LIB_H__

// OpenAL
#include <alure.h>

// OpenGL
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

// Libpng
#include <png.hpp>
#include <zlib.h>

// C++ STL
#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>

// Windows
#ifdef _WIN32

#define NOMINMAX
#include <Windows.h>

#endif // Platform

#endif // __EXTERNAL_LIB_H__