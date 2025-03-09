#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include"Basic.hpp"

std::map<String,GLuint>combined;

struct texture{
	texture(String filename){
		file = (String)"../assets/textures/"+filename+".png";
		// load();//���⺯��
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
	
	if(combined.count(target->file)){//���仯 
		target->sequal=combined[target->file];
		return 1;
	}
	
    int Status = FALSE;//**��Ҫ�������߼�** 
	int width, height, channels;
    unsigned char *image_data = stbi_load(target->file.c_str(), &width, &height, &channels, 0);//����ͼƬ 
    Status = TRUE;
    glGenTextures(1, &(target->sequal));//����������
    glBindTexture(GL_TEXTURE_2D, target->sequal);//�����ɵ������Ű󶨲��� 
    if(channels==3)
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);//�������� 
    else if(channels==4)
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);//�������� 
    else
    	return -1;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//������ʾ��ʽ 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//������ʾ��ʽ 
	glGenerateMipmap(GL_TEXTURE_2D);
    //�ͷ�ͼ����ڴ棬��Ϊ�Ѿ����������ˣ�û����
    stbi_image_free(image_data);  // �ͷ�����ͼ��ռ�õ��ڴ�
    
    combined[target->file]=target->sequal;
    
    return Status;
}
#endif
