#include <iostream>
#include "headers/shaderLoader/shaderLoader.h"

std::string ShaderLoader::getShaderString(std::string a_pathToShaderFile)
{
    std::ifstream fileReader;
    fileReader.open(a_pathToShaderFile, std::ios::binary);

    // Make sure to check that the file is open.
    if(fileReader.is_open())
    {
        fileReader.seekg(0, std::ios::beg);

        std::string line;
        std::string output;
        while (std::getline(fileReader, line))
        {
            output.append(line);
            output.append("\n");
        }

        output.append("\0");

        return output;
    }
    else
    {
        std::cerr << "Could not open file." << std::endl;
    }

    return nullptr;
}
