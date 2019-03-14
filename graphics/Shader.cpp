//
// Created by Brendan Berg on 13.03.19.
//

#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.hpp"


Shader::Shader (const std::string& vertexShaderFilePath,
                const std::string& fragmentShaderFilePath)
    : m_ProgramAddress(0)
{
    CreateProgram(vertexShaderFilePath, fragmentShaderFilePath);
    Bind();
}


void Shader::SetBoundState (bool bind)
{
    if (bind)
    {
        Bind();
    }
    else
    {
        Unbind();
    }
}


void Shader::Bind ()
{
    GLCall(glUseProgram(m_ProgramAddress));
    m_Bound = true;
}


void Shader::Unbind ()
{
    GLCall(glUseProgram(0));
    m_Bound = false;
}


void Shader::CreateProgram (const std::string& vertexShaderFilePath,
                            const std::string& fragmentShaderFilePath)
{
    m_ProgramAddress = glCreateProgram();

    auto vshaddr = CreateShader(vertexShaderFilePath, GL_VERTEX_SHADER);
    auto fshaddr = CreateShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(m_ProgramAddress, vshaddr));
    GLCall(glAttachShader(m_ProgramAddress, fshaddr));
    GLCall(glLinkProgram(m_ProgramAddress));
    GLCall(glValidateProgram(m_ProgramAddress));

    GLCall(glDeleteShader(vshaddr));
    GLCall(glDeleteShader(fshaddr));
}


unsigned int Shader::CreateShader (const std::string& shaderFilePath,
                                   unsigned int type)
{
    auto shaddr = glCreateShader(type);

    auto source = LoadFile(shaderFilePath);
    auto cSource = source.c_str();
    GLCall(glShaderSource(shaddr, 1, &cSource, nullptr));

    GLCall(glCompileShader(shaddr));

    int result;
    GLCall(glGetShaderiv(shaddr, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        char msg[512];
        GLCall(glGetShaderiv(shaddr, GL_INFO_LOG_LENGTH, &length));
        GLCall(glGetShaderInfoLog(shaddr, 512, &length, msg));
        GLCall(glDeleteShader(shaddr));
        std::cout << msg << std::endl;
        return 0;
    }

    return shaddr;
}


std::string Shader::LoadFile (const std::string& filePath)
{
    std::stringstream stream;

    std::ifstream file(filePath);
    stream << file.rdbuf();
    file.close();

    return stream.str();
}
