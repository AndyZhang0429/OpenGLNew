#ifndef _Soil_HPP
#define _Soil_HPP

#include"../Basic.hpp"
#include"../Texture.hpp"
#include"../Model.hpp"
#include"../vec3.hpp"

#include"Full_Block.hpp"

class Soil:public Full_Block{
	public:
	Soil(Vec3 pos):Full_Block(pos){}
		unsigned getID() override{
			return 2;
		}
		String getName() override{
			return GAMENAME+".soil";
		}
		std::map<String,texture> getTextures() override{
			return textures;
		}
		model getModel() override{
			return _mod;
		}
	private:
		static std::map<String,texture> textures;
		static model _mod;
		static Vec4 colorf[8];
};
Vec4 Soil::colorf[8]{
	Vec4(0.43,0.25,0.05,1),
	Vec4(0.43,0.25,0.05,1),
	Vec4(0.43,0.25,0.05,1),
	Vec4(0.43,0.25,0.05,1),
	Vec4(0.43,0.25,0.05,1),
	Vec4(0.43,0.25,0.05,1),
	Vec4(0.43,0.25,0.05,1),
	Vec4(0.43,0.25,0.05,1),
};
std::map<String,texture> Soil::textures
({
	{"top",texture("blocks/grass")},
	{"bottom",texture("blocks/grass")},
	{"left",texture("blocks/grass")},
	{"right",texture("blocks/grass")},
	{"front",texture("blocks/grass")},
	{"back",texture("blocks/grass")}
});
model Soil::_mod = {
{String("top"), {
    {Vec3(0,1,0), {Point(0,0), Soil::colorf[2]}},
    {Vec3(0,1,1), {Point(0,1), Soil::colorf[3]}},
    {Vec3(1,1,1), {Point(1,1), Soil::colorf[7]}},
    {Vec3(1,1,0), {Point(1,0), Soil::colorf[6]}}
}},
{String("bottom"), {
    {Vec3(0,0,0), {Point(1,0), Soil::colorf[0]}},
    {Vec3(1,0,0), {Point(0,0), Soil::colorf[4]}},
    {Vec3(1,0,1), {Point(0,1), Soil::colorf[5]}},
    {Vec3(0,0,1), {Point(1,1), Soil::colorf[1]}}
}},
{String("front"), {
    {Vec3(0,0,0), {Point(1,1), Soil::colorf[0]}},
    {Vec3(0,1,0), {Point(1,0), Soil::colorf[2]}},
    {Vec3(1,1,0), {Point(0,0), Soil::colorf[6]}},
    {Vec3(1,0,0), {Point(0,1), Soil::colorf[4]}}
}},
{String("back"), {
    {Vec3(0,0,1), {Point(0,1), Soil::colorf[1]}},
    {Vec3(1,0,1), {Point(1,1), Soil::colorf[5]}},
    {Vec3(1,1,1), {Point(1,0), Soil::colorf[7]}},
    {Vec3(0,1,1), {Point(0,0), Soil::colorf[3]}}
}},
{String("left"), {
    {Vec3(0,0,0), {Point(0,1), Soil::colorf[0]}},
    {Vec3(0,0,1), {Point(1,1), Soil::colorf[1]}},
    {Vec3(0,1,1), {Point(1,0), Soil::colorf[3]}},
    {Vec3(0,1,0), {Point(0,0), Soil::colorf[2]}}
}},
{String("right"), {
    {Vec3(1,0,0), {Point(1,1), Soil::colorf[4]}},
    {Vec3(1,1,0), {Point(1,0), Soil::colorf[6]}},
    {Vec3(1,1,1), {Point(0,0), Soil::colorf[7]}},
    {Vec3(1,0,1), {Point(0,1), Soil::colorf[5]}}
}}
};

#endif
