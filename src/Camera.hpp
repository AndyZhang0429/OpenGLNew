#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Basic.hpp"
class Camera{
    public:
        Camera(int x, int y, int z, int top, int bottom, int left, int right){
            ::pos = Vec3(x, y, z);
            ::top = top;
            ::bottom = bottom;
            ::left = left;
            ::right = right;
        }
        Camera(Vec3 pos, int top, int bottom, int left, int right){
            ::pos = pos;
            ::top = top;
            ::bottom = bottom;
            ::left = left;
            ::right = right;
        }
        Camera(){
            ::pos = Vec3(0, 0, 0);
            ::top = 0;
            ::bottom = 0;
            ::left = 0;
            ::right = 0;
        }
        void setPos(Vec3 pos){
            ::pos = pos;
        }
        void setPos(int x, int y, int z){
            ::pos = Vec3(x, y, z);
        }
        void setAngles(Vec3 angles){
            eular_angles = angles; 
        }
        void setAngles(int x, int y, int z){
            eular_angles = Vec3(x, y, z); 
        }
        void setPos(Vec4 pos){
            top = pos.first;
            bottom = pos.second;
            left = pos.third;
            right = pos.fourth;
        }
        void setFOV(double fov){
            ::fov = fov;
        }
        void use(glm::mat4* model = NULL, glm::mat4* view = NULL, glm::mat4* projection = NULL){
            glViewport(left, bottom, right - left, top - bottom);
            if(model != NULL){
                *model = glm::mat4(1.0f);
            }
            if(view != NULL){
                *view = glm::lookAt(
                    glm::vec3(pos.first, pos.second, pos.third),
                    glm::vec3(pos.first, pos.second, pos.third) + 
                    glm::vec3(
                        sin(glm::radians(eular_angles.first))*cos(glm::radians(eular_angels.second)), 
                        sin(glm::radians(eular_angles.second)), 
                        cos(glm::radians(eular_angles.first))*cos(glm::radians(eular_angels.second))
                    ),
                    glm::vec3(0, 1, 0)
                )
            }
            if(projection!= NULL){
                *projection = glm::perspective(
                    glm::radians(fov),
                    (right - left)/(top - bottom),
                    0.1f,
                    100.0f
                );
            }
        }
    private:
        Vec3 pos;
        Vec3 eular_angles;
        int top, bottom, left, right;
        double fov;

};
#endif