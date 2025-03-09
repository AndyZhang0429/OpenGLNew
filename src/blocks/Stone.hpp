#ifndef _Stone_HPP
#define _Stone_HPP

#include"../Basic.hpp"
#include"../Texture.hpp"
#include"../Model.hpp"
#include"../vec3.hpp"

#include"Full_Block.hpp"

class Stone:public Full_Block{
	public:
		Stone(Vec3 pos):Full_Block(pos){}
		unsigned getID() override{
			return 3;
		}
		String getName() override{
			return GAMENAME+".stone";
		}
		std::map<String,texture> getTextures() override{
			return textures;
		}
	private:
		static std::map<String,texture> textures;
		
};
std::map<String,texture> Stone::textures
({
	{"top",texture("blocks/stone")},
	{"bottom",texture("blocks/stone")},
	{"left",texture("blocks/stone")},
	{"right",texture("blocks/stone")},
	{"front",texture("blocks/stone")},
	{"back",texture("blocks/stone")}
});

#endif
