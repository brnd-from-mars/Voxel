//
// Created by Brendan Berg on 13.03.19.
//

#ifndef VOXEL_SHADER_HPP
#define VOXEL_SHADER_HPP

#include <string>

#include <glm/glm.hpp>

#include "Graphics.hpp"


class Shader
{

public:

    Shader (const std::string& vertexShaderFilePath,
            const std::string& fragmentShaderFilePath);

    void Bind ();

    void Unbind ();

    template <typename T>
    void SetUniformValue (const std::string& name, T data);

    template <typename T>
    void SetUniformVector (const std::string& name, const T& data);

    template <typename T>
    void SetUniformMatrix (const std::string& name, const T& data);


private:

    int GetUniformLocation (const std::string& name);

    void CreateProgram (const std::string& vertexShaderFilePath,
                        const std::string& fragmentShaderFilePath);

    unsigned int CreateShader (const std::string& shaderFilePath,
                               unsigned int type);

    std::string LoadFile (const std::string& filePath);

    unsigned int m_ProgramAddress;


};


template <>
void Shader::SetUniformValue<int> (const std::string& name, int data);


template <>
void Shader::SetUniformVector<glm::vec4> (const std::string& name,
                                          const glm::vec4& data);


template <>
void Shader::SetUniformMatrix<glm::mat4> (const std::string& name,
                                          const glm::mat4& data);


#endif //VOXEL_SHADER_HPP
