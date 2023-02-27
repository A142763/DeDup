// DeDup.cpp : This file contains the 'main' function. Program execution begins and ends there.
// (c) 2023 Jimmy James

#include <iostream>
#include <filesystem>
#include <stdio.h>
#include <sstream>
#include <string>


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

void list_files_recursive(const std::filesystem::path& path) {
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::cout << entry.path() << std::endl;
        }
        else if (entry.is_directory()) {
            list_files_recursive(entry.path());
        }
    }
}


int main()
{
    // This is the delimiter for the parts of the command result cmdrslt
    // and set the method used for hashing
    
    const char delimiter = '\n';
    const std::string method = "MD5";

    // The location to de-dup
    const std::string path = "E:\\library";

    list_files_recursive(path);


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





