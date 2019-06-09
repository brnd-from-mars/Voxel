//
// Created by Brendan Berg on 16.03.19.
//

#ifndef VOXEL_CONFIGPARSER_HPP
#define VOXEL_CONFIGPARSER_HPP

#include <vector>
#include <map>
#include <fstream>


typedef std::pair<std::string, std::string> CommandParameter;

typedef std::vector<CommandParameter> CommandParameters;


class ConfigParser
{
public:

    explicit ConfigParser (const std::string& filePath);

    ~ConfigParser ();

    bool ParseLine (std::string& command, CommandParameters& parameters);

    static bool IsNumeric (const std::string& string);

    static unsigned int UnserializeUnsigned (const std::string& string);

    static std::pair<unsigned int, unsigned int>
        UnserializePair (const std::string& string);

    static CommandParameters::const_iterator
        FindParameter (const CommandParameters& parameters,
                       const std::string& string);


private:

    void ParseParameters (const std::string& parameterString,
                         CommandParameters& parameters);

    CommandParameter ParseParameter (const std::string& parameterString);

    std::ifstream m_File;


};


#endif //VOXEL_CONFIGPARSER_HPP
