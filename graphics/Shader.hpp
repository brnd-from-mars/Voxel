//
// Created by Brendan Berg on 13.03.19.
//

#ifndef VOXEL_SHADER_HPP
#define VOXEL_SHADER_HPP

#include <string>

#include "Graphics.hpp"


class Shader
{

public:

    Shader (const std::string& vertexShaderFilePath,
            const std::string& fragmentShaderFilePath);

    void SetBoundState (bool bind);

    void Bind ();

    void Unbind ();


private:

    unsigned int m_ProgramAddress;

    bool m_Bound;

    void CreateProgram (const std::string& vertexShaderFilePath,
                        const std::string& fragmentShaderFilePath);

    unsigned int CreateShader (const std::string& shaderFilePath,
                               unsigned int type);

    std::string LoadFile (const std::string& filePath);


};


#endif //VOXEL_SHADER_HPP
