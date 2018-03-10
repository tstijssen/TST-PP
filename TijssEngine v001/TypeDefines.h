#pragma once

#include <string>
#include <assert.h>
#include <SFML/Window.hpp>
#define M_PI 3.14159265358979323846

typedef std::string string;

//typedef sf::Vector2f vector2F;	// x, y, float vector. Imported from sfml library
//typedef sf::Vector2i vector2I;	// x, y, integer vector. Imported from sfml library
//typedef sf::Vector2u vector2U;	// x, y, unsigned int vector. Imported from sfml library
//
//typedef sf::Vector3f vector3F;	// x, y, z, float vector. Imported from sfml library
//typedef sf::Vector3i vector3I;	// x, y, z, integer vector. Imported from sfml library

typedef int int32;
typedef unsigned int uint32;

typedef float float32;
typedef double float64;

struct Vector2
{
	int x, y;
};

struct Vector3
{
	int x, y, z;
};

