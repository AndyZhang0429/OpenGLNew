#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include"Basic.hpp"

std::map<String,GLuint>combined;

struct texture{
	texture(String filename){
		file = (String)"../assets/textures/"+filename+".png";
		// load();//问题函数
	}
	texture(){
		file = "";
	}
	String file;
	GLuint sequal;
	void load();
};
int LoadGLTextures(texture *target);

void texture::load(){
	LoadGLTextures(this);
}
int LoadGLTextures(texture *target)
{
	
	if(combined.count(target->file)){//记忆化 
		target->sequal=combined[target->file];
		return 1;
	}
	
    int Status = FALSE;//**需要错误处理逻辑** 
	int width, height, channels;
    unsigned char *image_data = stbi_load(target->file.c_str(), &width, &height, &channels, 0);//加载图片 
    Status = TRUE;
    glGenTextures(1, &(target->sequal));//生成纹理编号
    glBindTexture(GL_TEXTURE_2D, target->sequal);//将生成的纹理编号绑定操作 
    if(channels==3)
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);//生成纹理 
    else if(channels==4)
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);//生成纹理 
    else
    	return -1;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//设置显示样式 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//设置显示样式 
	glGenerateMipmap(GL_TEXTURE_2D);
    //释放图像的内存，因为已经生成纹理了，没用了
    stbi_image_free(image_data);  // 释放纹理图像占用的内存
    
    combined[target->file]=target->sequal;
    
    return Status;
}
#endif
