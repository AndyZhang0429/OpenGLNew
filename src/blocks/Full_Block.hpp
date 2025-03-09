#ifndef _Full_Block_HPP
#define _Full_Block_HPP

#include"../Basic.hpp"
#include"../Texture.hpp"
#include"../Model.hpp"
#include"../vec3.hpp"

#include"Block.hpp"
//extract base class
class Full_Block:public Block{
	public:
		Full_Block(Vec3 pos):Block(pos){}
		model getModel() override{
			return mod;
		}
		void set_show(unsigned char type){
			std::set<String>faces;
			if(type&0x20){//x+
				faces.insert("right");
			}
			if(type&0x10){//x-
				faces.insert("left");
			}
			if(type&0x8){//y+
				faces.insert("top");
			}
			if(type&0x4){//y-
				faces.insert("bottom");
			}
			if(type&0x2){//z+
				faces.insert("front");
			}
			if(type&0x1){//z-
				faces.insert("back");
			}
			faces_to_show=faces;
		}
	private:
		static model mod;
}; 
model Full_Block::mod = {
    {String("top"), {
        {Vec3(0,1,0), {Point(0,0), Vec4(1,1,1,1)}},
        {Vec3(0,1,1), {Point(0,1), Vec4(1,1,1,1)}},
        {Vec3(1,1,1), {Point(1,1), Vec4(1,1,1,1)}},
        {Vec3(1,1,0), {Point(1,0), Vec4(1,1,1,1)}}
    }},
    {String("bottom"), {
        {Vec3(0,0,0), {Point(1,0), Vec4(1,1,1,1)}},
        {Vec3(1,0,0), {Point(0,0), Vec4(1,1,1,1)}},
        {Vec3(1,0,1), {Point(0,1), Vec4(1,1,1,1)}},
        {Vec3(0,0,1), {Point(1,1), Vec4(1,1,1,1)}}
    }},
    {String("front"), {
        {Vec3(0,0,0), {Point(1,1), Vec4(1,1,1,1)}},
        {Vec3(0,1,0), {Point(1,0), Vec4(1,1,1,1)}},
        {Vec3(1,1,0), {Point(0,0), Vec4(1,1,1,1)}},
        {Vec3(1,0,0), {Point(0,1), Vec4(1,1,1,1)}}
    }},
    {String("back"), {
        {Vec3(0,0,1), {Point(0,1), Vec4(1,1,1,1)}},
        {Vec3(1,0,1), {Point(1,1), Vec4(1,1,1,1)}},
        {Vec3(1,1,1), {Point(1,0), Vec4(1,1,1,1)}},
        {Vec3(0,1,1), {Point(0,0), Vec4(1,1,1,1)}}
    }},
    {String("left"), {
        {Vec3(0,0,0), {Point(0,1), Vec4(1,1,1,1)}},
        {Vec3(0,0,1), {Point(1,1), Vec4(1,1,1,1)}},
        {Vec3(0,1,1), {Point(1,0), Vec4(1,1,1,1)}},
        {Vec3(0,1,0), {Point(0,0), Vec4(1,1,1,1)}}
    }},
    {String("right"), {
        {Vec3(1,0,0), {Point(1,1), Vec4(1,1,1,1)}},
        {Vec3(1,1,0), {Point(1,0), Vec4(1,1,1,1)}},
        {Vec3(1,1,1), {Point(0,0), Vec4(1,1,1,1)}},
        {Vec3(1,0,1), {Point(0,1), Vec4(1,1,1,1)}}
    }}
};
#endif
