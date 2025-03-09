#ifndef _Grass_HPP
#define _Grass_HPP

#include"../Basic.hpp"
#include"../Texture.hpp"
#include"../Model.hpp"
#include"../vec3.hpp"

#include"Full_Block.hpp"

class Grass:public Full_Block{
	public:
		Grass(Vec3 pos):Full_Block(pos){}
		unsigned getID() override{
			return 1;
		}
		String getName() override{
			return GAMENAME+".grass";
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
Vec4 Grass::colorf[8]{
	Vec4(0.4,1,0,1),
	Vec4(0.4,1,0,1),
	Vec4(0.4,1,0,1),
	Vec4(0.4,1,0,1),
	Vec4(0.4,1,0,1),
	Vec4(0.4,1,0,1),
	Vec4(0.4,1,0,1),
	Vec4(0.4,1,0,1),
};
std::map<String,texture> Grass::textures
({
	{"top",texture("blocks/grass")},
	{"bottom",texture("blocks/grass")},
	{"left",texture("blocks/grass")},
	{"right",texture("blocks/grass")},
	{"front",texture("blocks/grass")},
	{"back",texture("blocks/grass")}
});
model Grass::_mod = {
{String("top"), {
    {Vec3(0,1,0), {Point(0,0), Grass::colorf[2]}},
    {Vec3(0,1,1), {Point(0,1), Grass::colorf[3]}},
    {Vec3(1,1,1), {Point(1,1), Grass::colorf[7]}},
    {Vec3(1,1,0), {Point(1,0), Grass::colorf[6]}}
}},
{String("bottom"), {
    {Vec3(0,0,0), {Point(1,0), Grass::colorf[0]}},
    {Vec3(1,0,0), {Point(0,0), Grass::colorf[4]}},
    {Vec3(1,0,1), {Point(0,1), Grass::colorf[5]}},
    {Vec3(0,0,1), {Point(1,1), Grass::colorf[1]}}
}},
{String("front"), {
    {Vec3(0,0,0), {Point(1,1), Grass::colorf[0]}},
    {Vec3(0,1,0), {Point(1,0), Grass::colorf[2]}},
    {Vec3(1,1,0), {Point(0,0), Grass::colorf[6]}},
    {Vec3(1,0,0), {Point(0,1), Grass::colorf[4]}}
}},
{String("back"), {
    {Vec3(0,0,1), {Point(0,1), Grass::colorf[1]}},
    {Vec3(1,0,1), {Point(1,1), Grass::colorf[5]}},
    {Vec3(1,1,1), {Point(1,0), Grass::colorf[7]}},
    {Vec3(0,1,1), {Point(0,0), Grass::colorf[3]}}
}},
{String("left"), {
    {Vec3(0,0,0), {Point(0,1), Grass::colorf[0]}},
    {Vec3(0,0,1), {Point(1,1), Grass::colorf[1]}},
    {Vec3(0,1,1), {Point(1,0), Grass::colorf[3]}},
    {Vec3(0,1,0), {Point(0,0), Grass::colorf[2]}}
}},
{String("right"), {
    {Vec3(1,0,0), {Point(1,1), Grass::colorf[4]}},
    {Vec3(1,1,0), {Point(1,0), Grass::colorf[6]}},
    {Vec3(1,1,1), {Point(0,0), Grass::colorf[7]}},
    {Vec3(1,0,1), {Point(0,1), Grass::colorf[5]}}
}}
};

#endif
