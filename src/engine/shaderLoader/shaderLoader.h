#include <iostream>
#include <fstream>
#include <string.h>

class ShaderLoader
{
public:
    char* getShaderString(std::string a_pathToShaderFile)
    {
        char* output;

        std::ifstream fileReader;
        fileReader.open(a_pathToShaderFile);

        // Make sure to check that the file is open.
        if(fileReader.is_open())
        {
            std::string line;

            // Loop over all of the file lines and add it's contents to the output pointer.
            while(std::getline(fileReader, line))
            {
                output << line.data();

                // strcat(output, code);
            }

            fileReader.close();
        }
        else
        {
            std::cout << "Could not open file." << std::endl;
        }

        return output;
    }
};