#ifndef BASIC
#define BASIC

#define GAMENAME String("a")
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include<stb_image.h>

#include<GL/glew.h>
#include<GL/glu.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>  
#include<glm/gtc/type_ptr.hpp>

#include<windows.h>

#include<iostream>
#include<fstream>
#include<cmath>
#include<chrono>

#include<map>
#include<vector>
#include<string>
#include<set>

#define PI 3.141592653589793

//动作设置 
#define BREAK_BLOCK 0
#define PUT_BLOCK 1 


const short player = 0;//发出动作者设置 

const float toRad = PI/180;

typedef std::string String;

inline String readfile(String name){
	std::ifstream file(name);
    if (!file.is_open()) {
        std::cerr << "error" << std::endl;
        return "";
    }
 
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close(); 
    return content;
}

inline POINT getcursor(HWND hwnd){
	POINT pt;
	GetCursorPos(&pt);
	return pt;
}

// 改进的平滑插值函数
inline double fade(double l, double r, double t) {
    // 使用更高效的多项式计算
    double t3 = t * t * t;
    double t4 = t3 * t;
    double t5 = t4 * t;
    double val = 6 * t5 - 15 * t4 + 10 * t3;
    
    return l + val * (r - l);
}

bool getERR(){
    bool rr = true;
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL_Error(" << error<<")]" << std::endl;
        rr=false;
    }
	DWORD Err = GetLastError();
	std::cout<<Err<<std::endl;
    return rr;
}

void init_window(HWND hWnd,HGLRC& RC,HDC& DC)
{
    //获取DC
    DC = GetDC(hWnd);

    //初始化像素格式
    static PIXELFORMATDESCRIPTOR pfd =    
    {
        sizeof(PIXELFORMATDESCRIPTOR),    //上述格式描述符的大小
        1,                                //版本号
        PFD_DRAW_TO_WINDOW |              //格式支持窗口
        PFD_SUPPORT_OPENGL |              //格式必须支持OpenGL
        PFD_DOUBLEBUFFER,                 //必须支持双缓冲
        PFD_TYPE_RGBA,                    //申请RGBA 格式
        32,                               //选定色彩深度
        0, 0, 0, 0, 0, 0, 8, 0,           //忽略RGBA
        0,                                //无累加缓存
        0, 0, 0, 0,                       //忽略聚集位
        32,                               //32位Z-缓存(深度缓存)
        0,                                //无蒙板缓存
        0,                                //无辅助缓存
        PFD_MAIN_PLANE,                   //主绘图层
        0,                                //Reserved
        0, 0, 0                           //忽略层遮罩
    };

    //选择一个最适合pfd描述的像素格式索引值
    int PixelFormat = ChoosePixelFormat(DC, &pfd);

    //为DC设置像素格式
    SetPixelFormat(DC, PixelFormat, &pfd);

    //创建RC
    RC = wglCreateContext(DC);
}


#endif
