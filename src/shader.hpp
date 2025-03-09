#ifndef SHADER_HPP
#define SHADER_HPP
#include"Basic.hpp"
String vertex_shader=readfile("../shaders/vertex_shader_test.glsl");
String fragment_shader=readfile("../shaders/fragment_shader_test.glsl");
GLuint compileShader(GLenum type, const char* source) {
	std::cout<<source<<std::endl;
    GLuint _shader = glCreateShader(type);
    glShaderSource(_shader, 1, &source, nullptr);
    glCompileShader(_shader);
    GLint success;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(_shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return _shader;
}
GLuint createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
	std::cout<<"0%\n";
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	std::cout<<"40%\n";
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	std::cout<<"80%\n";
 
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
	std::cout<<"90%\n";
 
    // ¼ì²éÁ´½Ó´íÎó
	std::cout<<"95%\n";
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
	std::cout<<"99%\n";
 
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
	std::cout<<"100%\n";
    return shaderProgram;
}
#endif
