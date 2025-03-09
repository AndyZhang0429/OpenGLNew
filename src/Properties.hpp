#ifndef PROPERTIES_HPP
#define PROPERTIES_HPP
#include"Basic.hpp"
#include"time.hpp"
#include"Blocks.hpp"
#include"Vec3.hpp"


extern double fov,x,y,z,yaw,pitch,roll;
extern double sensitivity_mouse;
extern double speed,speed_sprint;
extern int HEIGHT_OF_WINDOW,WIDTH_OF_WINDOW;
extern char WINDOW_NAME[];
extern HWND winND;
extern HGLRC winRC;
extern HDC winDC;

extern POINT lastpt;
extern std::set<Block*>toDisplay;
extern std::map<Vec3,Block*> block_list; // 方块位置映射
extern std::map<String,texture> UIs; // 方块位置映射
extern std::map<int,unsigned long long> rands; // 随机数存储
extern unsigned long long seed; // 随机数种子

extern Timer display_timer; // 计时器
extern unsigned tick;
extern double time_since_last_tick;
extern std::set<unsigned> events_happened_in_tick; 

extern GLuint Block_shader,Line_loop_shader,UI_shader,VAO;   // OpenGL着色器和顶点数组对象
extern glm::mat4 modelMat,viewMat,projectionMat; // 模型、视图、投影矩阵


double fov = 70,
x = 0,y = 64,z = 0,
yaw = 0,pitch = 0,roll = 0;
double sensitivity_mouse = 0.6;
double speed=3,speed_sprint=4;

int HEIGHT_OF_WINDOW=600,WIDTH_OF_WINDOW=800;
char WINDOW_NAME[]="0.3 demo test";
HWND winND;
HGLRC winRC;
HDC winDC;

POINT lastpt;

std::set<Block*>toDisplay;
std::map<Vec3,Block*> block_list; // 方块位置映射
std::map<String,texture> UIs; // 方块位置映射
std::map<int,unsigned long long> rands; // 随机数存储
unsigned long long seed = 16907425472287337063ull; // 随机数种子

Timer display_timer; // 计时器
unsigned tick = 0;
double time_since_last_tick = 0;
std::set<unsigned> events_happened_in_tick; 

GLuint Block_shader,Line_loop_shader,UI_shader,VAO;   // OpenGL着色器和顶点数组对象
glm::mat4 modelMat,viewMat,projectionMat; // 模型、视图、投影矩阵


#endif