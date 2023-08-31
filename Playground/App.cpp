#include <fstream>
#include <string>
#include <iostream>

struct vertex
{
    float x, y, z;
};

struct 

void readFile(const std::string& filename)
{
    std::string lineHeader;

    std::ifstream istrm(filename, std::ios::binary);
    if (!istrm.is_open())
    {
        std::cout << "failed to open " << filename << std::endl;
        return;
    }
    
    if (istrm >> lineHeader)                        
        std::cout << "read from file: " << lineHeader << std::endl;
}

int main()
{
	
    readFile("cube.obj");

	return 0;
}