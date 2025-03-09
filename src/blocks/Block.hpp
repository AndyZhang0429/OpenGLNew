#ifndef _Block_HPP
#define _Block_HPP

#include"../Basic.hpp"
#include"../Texture.hpp"
#include"../Model.hpp"
#include"../vec3.hpp"

//extract base class
class Block{
	public:
		Block(Vec3 pos):position(pos){}
		Vec3 position;
		std::map<String,GLuint> buffers;
		std::set<String>faces_to_show;
		virtual unsigned getID()=0;
		virtual String getName()=0;
		virtual std::map<String,texture> getTextures()=0;
		virtual model getModel()=0;
		virtual void set_show(unsigned char type)=0;
		virtual void refreshBuffer(){
            for(std::pair<String,GLuint> buffer:buffers){
                if(!faces_to_show.count(buffer.first)){
                    glDeleteBuffers(1, &buffer.second);
                    buffers.erase(buffer.first);
                }
            }
            for(String face:faces_to_show){
                if(buffers.find(face)==buffers.end()){
                    float buf[36];
                    buffers[face]=0;
                    glGenBuffers(1,&buffers[face]);
                    glBindBuffer(GL_ARRAY_BUFFER, buffers[face]);
                    int c = 0;
                    for(auto vertex : getModel()[face]){    
                        buf[9*c+0]=vertex.first.first+position.first;
                        buf[9*c+1]=vertex.first.second+position.second;
                        buf[9*c+2]=vertex.first.third+position.third;
                        buf[9*c+3]=vertex.second.first.x;
                        buf[9*c+4]=vertex.second.first.y;
                        buf[9*c+5]=vertex.second.second.first;
                        buf[9*c+6]=vertex.second.second.second;
                        buf[9*c+7]=vertex.second.second.third;
                        buf[9*c+8]=vertex.second.second.fourth;
                        c++;
                    }
                    glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
                }
            }
        }
		virtual void delBuffer(){
            for(std::pair<String,GLuint> buffer:buffers){
				glDeleteBuffers(1, &buffer.second);
				buffers.erase(buffer.first);
            }
		}
		virtual ~Block(){}
};
#endif
