/*

Author:     Oliver Blaser

Date c:     29.11.2020
Date e:     29.11.2020

*/

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "subModule/subModule.h"

#define USE_TRYCATCH 1

using namespace std;

static void printArgs(int argc, char** argv);

int main(int argc, char** argv)
{

#if(USE_TRYCATCH)
    try
    {
#endif

        if(argc > 1)
        {
            if(string(argv[1]).compare("-l") == 0)
            {
                string path(argv[2]);
                vector<string> sv = subModule::getDirEntries(path);
                size_t maxStrLen = 0;

                sort(sv.begin(), sv.end());

                for(size_t i = 0; i < sv.size(); ++i) if(sv[i].length() > maxStrLen) maxStrLen = sv[i].length();

                cout << "elements of \"" << path << "\"" << left << endl;

                for(size_t i = 0; i < sv.size(); ++i)
                {
                    cout << setw(maxStrLen + 2) << sv[i];

                    std::filesystem::directory_entry de(std::filesystem::path(sv[i]));

                    if(de.is_block_file()) cout << " is_block_file";
                    if(de.is_character_file()) cout << " is_character_file";
                    if(de.is_directory()) cout << " is_directory";
                    if(de.is_fifo()) cout << " is_fifo";
                    if(de.is_other()) cout << " is_other";
                    if(de.is_regular_file()) cout << " is_regular_file";
                    if(de.is_socket()) cout << " is_socket";
                    if(de.is_symlink()) cout << " is_symlink";

                    try
                    {
                        if(!de.is_directory()) cout << "        " << de.file_size() << " Bytes";
                    }
                    catch (std::filesystem::filesystem_error ex)
                    {
                        cout << "file_size error: " << ex.code().message();
                    }

                    cout << endl;
                }
            }
            else if(string(argv[1]).compare("-c") == 0)
            {
                cout << subModule::calc(atoi(argv[2]), atoi(argv[3])) << endl;
            }
            else
            {
                printArgs(argc, argv);
            }
        }
        else
        {
            printArgs(argc, argv);
        }

#if(USE_TRYCATCH)
    }
    catch (std::filesystem::filesystem_error ex)
    {
        cout << "\ncatch std::filesystem::filesystem_error:" << endl;
        cout << "code:     " << ex.code().value() << " " << ex.code().message() << endl;
        cout << "what:     " << ex.what() << endl;
        cout << "path1:    " << ex.path1() << endl;
        cout << "path2:    " << ex.path2() << endl;
    }
    catch (std::system_error ex)
    {
        cout << "\ncatch std::filesystem::filesystem_error:" << endl;
        cout << "code:     " << ex.code().value() << " " << ex.code().message() << endl;
        cout << "what:     " << ex.what() << endl;
    }
    catch (std::exception ex) { cout << "\ncatch std::exception:\n" << ex.what() << endl; }
    catch (...) { cout << "\nlast catch" << endl; }
#endif
    
    return 0;
}

static void printArgs(int argc, char** argv)
{
    for(int i = 0; i <= 100; ++i)
    {
        if(i == argc) cout << "following with illegal access to environment vars:" << endl;

        cout << setw(2) << i << "  ";

        if(i == argc)
        {
            cout << "error: core dumped";
        }
        else
        {
            cout << argv[i];
        }

        cout << endl;
    }
}
