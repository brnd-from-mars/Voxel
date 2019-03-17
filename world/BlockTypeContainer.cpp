//
// Created by Brendan Berg on 16.03.19.
//

#include <algorithm>

#include "BlockTypeContainer.hpp"


BlockTypeContainer::BlockTypeContainer (const std::string& filePath)
{
    ConfigParser parser(filePath);

    std::string command;
    CommandParameters parameters;
    while (parser.ParseLine(command, parameters))
    {
        if (command == std::string("BLOCKCOUNT"))
        {
            SetBlockCount(parameters);
        }
        else if (command == std::string("BLOCK"))
        {
            AddBlockType(parameters);
        }
    }
}


void BlockTypeContainer::SetBlockCount (const CommandParameters& parameters)
{
    for (auto& parameter : parameters)
    {
        if (ConfigParser::IsNumeric(parameter.first))
        {
            m_BlockTypes.resize(
                ConfigParser::UnserializeUnsigned(parameter.first));
        }
    }
}


void BlockTypeContainer::AddBlockType (const CommandParameters& parameters)
{
    auto idPos = std::find_if(parameters.begin(),
                              parameters.end(),
                              [](const CommandParameter& parameter)
                              {
                                  return parameter.first == "id";
                              });
    if (idPos == parameters.end())
    {
        return;
    }
    auto id = ConfigParser::UnserializeUnsigned((*idPos).second);
    m_BlockTypes[id] = BlockType(id);
}
