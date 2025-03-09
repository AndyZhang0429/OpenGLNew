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
extern std::map<Vec3,Block*> block_list; // ����λ��ӳ��
extern std::map<String,texture> UIs; // ����λ��ӳ��
extern std::map<int,unsigned long long> rands; // ������洢
extern unsigned long long seed; // ���������

extern Timer display_timer; // ��ʱ��
extern unsigned tick;
extern double time_since_last_tick;
extern std::set<unsigned> events_happened_in_tick; 

extern GLuint Block_shader,Line_loop_shader,UI_shader,VAO;   // OpenGL��ɫ���Ͷ����������
extern glm::mat4 modelMat,viewMat,projectionMat; // ģ�͡���ͼ��ͶӰ����


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
std::map<Vec3,Block*> block_list; // ����λ��ӳ��
std::map<String,texture> UIs; // ����λ��ӳ��
std::map<int,unsigned long long> rands; // ������洢
unsigned long long seed = 16907425472287337063ull; // ���������

Timer display_timer; // ��ʱ��
unsigned tick = 0;
double time_since_last_tick = 0;
std::set<unsigned> events_happened_in_tick; 

GLuint Block_shader,Line_loop_shader,UI_shader,VAO;   // OpenGL��ɫ���Ͷ����������
glm::mat4 modelMat,viewMat,projectionMat; // ģ�͡���ͼ��ͶӰ����


#endif