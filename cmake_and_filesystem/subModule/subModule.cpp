/*

Author:     Oliver Blaser

Date c:     29.11.2020
Date e:     29.11.2020

*/
 
#include <filesystem>
 
#include "subModule.h"

namespace fs = std::filesystem;

int subModule::calc(int a, int b)
{
    return a*a + b;
}

std::vector<std::string> subModule::getDirEntries(std::string& dir)
{
    std::vector<std::string> r(0);

    for(const auto& entry: fs::directory_iterator(dir))
    {
        r.push_back(entry.path().lexically_normal());
    }

    return r;
}
