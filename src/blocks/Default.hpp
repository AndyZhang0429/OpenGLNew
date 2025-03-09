#ifndef _Default_HPP
#define _Default_HPP

#include"../Basic.hpp"
#include"../Texture.hpp"
#include"../Model.hpp"
#include"../vec3.hpp"

#include"Full_Block.hpp"

class Default:public Full_Block{
	public:
		Default(Vec3 pos):Full_Block(pos){}
		unsigned getID() override{
			return 0;
		}
		String getName() override{
			return GAMENAME+".default";
		}
		std::map<String,texture> getTextures() override{
			return textures;
		}
	private:
		static std::map<String,texture> textures;
		
};
std::map<String,texture> Default::textures
({
	{"top",texture("blocks/default")},
	{"bottom",texture("blocks/default")},
	{"left",texture("blocks/default")},
	{"right",texture("blocks/default")},
	{"front",texture("blocks/default")},
	{"back",texture("blocks/default")}
});

#endif
