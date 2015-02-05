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

extern Cvar *vid_width;
extern Cvar *vid_height;
extern Cvar *vid_fullscreen;

extern std::map<std::string, Shader *> shaderList;