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
int initDraw();

void Draw_Rectangle(int x, int y, int width, int height, glm::vec4 color, float angle);


extern Cvar *vid_width;
extern Cvar *vid_height;
extern Cvar *vid_fullscreen;
extern Cvar *vid_monitor;
extern Cvar *vid_vsync;

extern std::map<std::string, Shader *> shaderList;