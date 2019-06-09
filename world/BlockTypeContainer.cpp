//
// Created by Brendan Berg on 16.03.19.
//

#include <algorithm>
#include <limits>

#include "BlockTypeContainer.hpp"


BlockTypeContainer::BlockTypeContainer (const std::string& filePath)
{
    ConfigParser parser(filePath);

    std::string command;
    CommandParameters parameters;
    while (parser.ParseLine(command, parameters))
    {
        if (command == std::string("BLOCKDB"))
        {
            SetBlockDataBase(parameters);
        }
        else if (command == std::string("BLOCKTXT"))
        {
            SetBlockTexture(parameters);
        }
        else if (command == std::string("BLOCK"))
        {
            AddBlockType(parameters);
        }
    }
}


const BlockType& BlockTypeContainer::GetBlock (unsigned int id) const
{
    return m_BlockTypes.at(id);
}


void BlockTypeContainer::SetBlockDataBase (const CommandParameters& parameters)
{
    for (auto& parameter : parameters)
    {
        if (parameter.first == "count")
        {
            auto count = ConfigParser::UnserializeUnsigned(parameter.second);
            m_BlockTypes.resize(count);
        }
    }
}


void BlockTypeContainer::SetBlockTexture (const CommandParameters& parameters)
{
    for (auto& parameter : parameters)
    {
        if (parameter.first == "file")
        {
            m_TextureFileName = parameter.second;
        }
        else if (parameter.first == "totaltiles")
        {
            auto k = ConfigParser::UnserializePair(parameter.second);
            m_TextureTileSize = glm::vec2(1.0f / static_cast<float>(k.first),
                                          1.0f / static_cast<float>(k.second));
        }
    }
}


void BlockTypeContainer::AddBlockType (const CommandParameters& parameters)
{
    unsigned int id;
    std::string name;

    auto idPos = ConfigParser::FindParameter(parameters, "id");
    auto namePos = ConfigParser::FindParameter(parameters, "name");

    id = ConfigParser::UnserializeUnsigned(idPos->second);
    name = namePos->second;

    m_BlockTypes[id] = BlockType(id, name);

    for (auto& parameter : parameters)
    {
        if (parameter.first == "solid")
        {
            m_BlockTypes[id].SetSolid();
        }
        if (parameter.first == "opaque")
        {
            m_BlockTypes[id].SetOpaque();
        }
        if (parameter.first == "tile")
        {
            AddBlockTypeTexture(id, parameter.second);
        }
        if (parameter.first == "tilet")
        {
            auto t = AddBlockTypeTexture(id, parameter.second);
            m_BlockTypes[id].SetSideTexture(BlockSide::Top, t);
        }
        if (parameter.first == "tileb")
        {
            auto t = AddBlockTypeTexture(id, parameter.second);
            m_BlockTypes[id].SetSideTexture(BlockSide::Bottom, t);
        }
    }
}


unsigned int
BlockTypeContainer::AddBlockTypeTexture (unsigned int id,
                                         const std::string& parameter)
{
    auto k = ConfigParser::UnserializePair(parameter);
    auto v = glm::vec2(
        m_TextureTileSize.x * static_cast<float>(k.first),
        m_TextureTileSize.y * static_cast<float>(k.second)
    );

    return m_BlockTypes[id].AddTexture(
        std::make_pair(v + 0.00f * m_TextureTileSize,
                       v + 1.00f * m_TextureTileSize));
}
