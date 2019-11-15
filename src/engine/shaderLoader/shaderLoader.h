#include <iostream>
#include <fstream>
#include <string.h>

class ShaderLoader
{
public:
    char* getShaderString(std::string a_pathToShaderFile)
    {
        std::ifstream fileReader(a_pathToShaderFile, std::ios::binary);

        // Make sure to check that the file is open.
        if(fileReader.is_open())
        {
            // // Get the length of the file.
            // fileReader.seekg(0, fileReader.end); // Searches for the end of the string.
            // int length = fileReader.tellg(); // Gets the file length.
            // fileReader.seekg(0, fileReader.beg); // Gets the beginning of the file.

            fileReader.seekg(0, std::ios::beg);
            std::streampos begin = fileReader.tellg();
            fileReader.seekg(0, std::ios::end);
            std::streampos end = fileReader.tellg(); 

            std::cout << "size is: " << (end-begin) << " bytes.\n";

            // char* buffer = new char[length];


            // fileReader.read(buffer, length);

            fileReader.close();

            return nullptr;
        }
        else
        {
            std::cerr << "Could not open file." << std::endl;
        }

        return nullptr;
    }
};