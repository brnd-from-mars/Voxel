//
// Created by Brendan Berg on 16.03.19.
//

#include <sstream>
#include <algorithm>
#include <cctype>

#include "ConfigParser.hpp"


ConfigParser::ConfigParser (const std::string& filePath)
{
    m_File.open(filePath);
}


ConfigParser::~ConfigParser ()
{
    m_File.close();
}


bool
ConfigParser::ParseLine (std::string& command, CommandParameters& parameters)
{
    std::string line;
    bool flag = true;
    while (flag && std::getline(m_File, line))
    {
        flag = line.empty() | (line[0] == '#');
    }

    if (flag == true)
    {
        return false;
    }

    auto firstWordEndPos = line.find(' ');

    command = line.substr(0, firstWordEndPos);
    auto parameterString = line.substr(firstWordEndPos + 1);

    parameters.clear();
    ParseParameters(parameterString, parameters);

    return true;
}


bool ConfigParser::IsNumeric (const std::string& string)
{
    if (string.empty())
    {
        return false;
    }

    return std::find_if(string.begin(),
                        string.end(),
                        [](char c)
                        {
                            return !std::isdigit(c) && (c != '-');
                        }) == string.end();
}


unsigned int ConfigParser::UnserializeUnsigned (const std::string& string)
{
    return static_cast<unsigned int>(strtoul(string.c_str(), nullptr, 10));
}


std::pair<unsigned int, unsigned int>
ConfigParser::UnserializePair (const std::string& string)
{
    auto commaCharPos = string.find(',');
    auto first = string.substr(0, commaCharPos);
    auto second = string.substr(commaCharPos + 1);
    return std::make_pair(UnserializeUnsigned(first),
                          UnserializeUnsigned(second));
}


CommandParameters::const_iterator
ConfigParser::FindParameter (const CommandParameters& parameters,
                             const std::string& string)
{

    return std::find_if(parameters.begin(), parameters.end(),
                        [string](const CommandParameter& parameter)
                        {
                            return parameter.first == string;
                        });
}


void ConfigParser::ParseParameters (const std::string& parameterString,
                                    CommandParameters& parameters)
{
    std::stringstream parameterStringStream(parameterString);
    std::string parameter;

    while (parameterStringStream >> parameter)
    {
        parameters.push_back(ParseParameter(parameter));
    }
}


CommandParameter
ConfigParser::ParseParameter (const std::string& parameterString)
{
    auto equalCharPos = parameterString.find('=');

    if (equalCharPos == std::string::npos)
    {
        return std::make_pair(parameterString, std::string());
    }

    auto parameter = parameterString.substr(0, equalCharPos);
    auto value = parameterString.substr(equalCharPos + 1);
    return std::make_pair(parameter, value);
}
