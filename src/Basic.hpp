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

//�������� 
#define BREAK_BLOCK 0
#define PUT_BLOCK 1 


const short player = 0;//�������������� 

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

// �Ľ���ƽ����ֵ����
inline double fade(double l, double r, double t) {
    // ʹ�ø���Ч�Ķ���ʽ����
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
    //��ȡDC
    DC = GetDC(hWnd);

    //��ʼ�����ظ�ʽ
    static PIXELFORMATDESCRIPTOR pfd =    
    {
        sizeof(PIXELFORMATDESCRIPTOR),    //������ʽ�������Ĵ�С
        1,                                //�汾��
        PFD_DRAW_TO_WINDOW |              //��ʽ֧�ִ���
        PFD_SUPPORT_OPENGL |              //��ʽ����֧��OpenGL
        PFD_DOUBLEBUFFER,                 //����֧��˫����
        PFD_TYPE_RGBA,                    //����RGBA ��ʽ
        32,                               //ѡ��ɫ�����
        0, 0, 0, 0, 0, 0, 8, 0,           //����RGBA
        0,                                //���ۼӻ���
        0, 0, 0, 0,                       //���Ծۼ�λ
        32,                               //32λZ-����(��Ȼ���)
        0,                                //���ɰ建��
        0,                                //�޸�������
        PFD_MAIN_PLANE,                   //����ͼ��
        0,                                //Reserved
        0, 0, 0                           //���Բ�����
    };

    //ѡ��һ�����ʺ�pfd���������ظ�ʽ����ֵ
    int PixelFormat = ChoosePixelFormat(DC, &pfd);

    //ΪDC�������ظ�ʽ
    SetPixelFormat(DC, PixelFormat, &pfd);

    //����RC
    RC = wglCreateContext(DC);
}


#endif
