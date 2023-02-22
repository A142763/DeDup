// DeDup.cpp : This file contains the 'main' function. Program execution begins and ends there.
// (c) 2023 Jimmy James

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>

std::string exec(const char* cmd)
{
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try
    {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) { result += buffer; }
    }
    catch (...)
    {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
    return result;
}

int main()
{
    const char delimiter = '\n';
    std::string file = "E:\\library\\docs\\numerical_recipes.pdf";
    // MD5 SHA256
    std::string cmd = "certutil -hashfile " + file + " MD5";
    std::string cmdrslt = exec(cmd.c_str());
    std::istringstream ss(cmdrslt);
    std::string token;

    // Read and discard the first token
    std::getline(ss, token, delimiter);

    // Read the second token
    if (std::getline(ss, token, delimiter))
    {
        // Do something with the second token
        // std::cout << "The second token is: " << token << std::endl;
        printf("MD5 hash of %s: %s\n", file.c_str(), token.c_str());
    }
    
    return 0;
}
