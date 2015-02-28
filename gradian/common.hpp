/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

// Std. Includes
#include <string>
#include <vector>
#include <array>
#include <map>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Exception
#include "exception.hpp"

// Console Variables
#include "cvar.hpp"

// Console commands and console itself
#include "console.hpp"

// Math and Usefull utilities
#include "math.hpp"


// Shader loading
#include "gl_shader.hpp"
#include "gl_object.hpp"

#include "gl_text.hpp"

// Drawing
#include "gl_draw.hpp"

//Main core class
#include "Gradian.hpp"

// Input
#include "input.hpp"

// Textures
#include "gl_texture.hpp"

// Sprites
#include "gl_sprite.hpp"



//debuging and error message handlers, depends on system we are running on
void debugPrint(std::string message);
void errorPrint(std::string message);