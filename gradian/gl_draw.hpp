/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/


void renderScene();

void reshape(GLFWwindow* window, int w, int h);


int initShaders();
int initDisplay();

extern int window_width;
extern int window_height;

extern std::map<std::string, Shader *> shaderList;