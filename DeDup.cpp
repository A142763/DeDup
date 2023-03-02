// DeDup.cpp : This file contains the 'main' function. Program execution begins and ends there.
// (c) 2023 Jimmy James

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <io.h>
#include <fcntl.h>

// Function to execute an external command and return the result string
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


using namespace std::string_literals;
namespace fs = std::filesystem;

// , const std::string& search_string
void search_files(const fs::path& path, const std::vector<std::string>& extensions)
{
    for (const auto& entry : fs::recursive_directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            const auto extension = entry.path().extension().string();
            if (std::find(extensions.begin(), extensions.end(), extension) != extensions.end())
            {
                // std::ifstream file(entry.path());
                // std::string line;
                std::wcout << entry.path() << std::endl;
            }
        }
    }
}


int main()
{
    // This is the delimiter for the parts of the command result cmdrslt
    // and set the method used for hashing
    
    const fs::path path = u8"E:\\library\\Mainframe";
    const std::vector<std::string> extensions = { ".pdf"s };
    // const std::string search_string = "pdf";
    _setmode(_fileno(stdout), _O_U16TEXT);
    search_files(path, extensions);
    return 0;


    const char delimiter = '\n';
    const std::string method = "MD5";

    // The location to de-dup
    // const std::wstring path = L"E:\\library\\Mainframe\\Hercules_Explode";

    // list_files_recursive(path,L".pdf");
    return 0;

    // The file to compute a hash for
    std::string file = "E:\\library\\docs\\numerical_recipes.pdf";
    
    // Build the command with hash method MD5 or SHA256
    std::string cmd = "certutil -hashfile " + file + " " + method;

    // Run the external command and capture the result to cmdrslt
    std::string cmdrslt = exec(cmd.c_str());

    // Now lets tear it apart based on the delimiter
    std::istringstream ss(cmdrslt);
    std::string token;

    // Read and discard the first token
    std::getline(ss, token, delimiter);

    // Read the second token
    if (std::getline(ss, token, delimiter))
    {
        // Do something with the second token
        std::cout << method << " hash of " << file << ": " << token << std::endl;
        // printf("MD5 hash of %s: %s\n", file.c_str(), token.c_str());
    }
    
    return 0;
}





