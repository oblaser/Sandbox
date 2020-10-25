/*

Author:     Oliver Blaser

Date c:     22.10.2020
Date e:     22.10.2020

(c) Oliver Blaser

*/

#include <iostream>
#include <iomanip>
#include <string>

#include "encoding.h"

using namespace std;

static void printHex(const uint8_t value)
{
    char lookUp[] = "0123456789ABCDEF";

    cout << lookUp[(value >> 4) & 0x0F];
    cout << lookUp[value & 0x0F];
}

// test command: ./cliArgTest -a b ä en äöü test ÿ

int encoding::main(int argc, const char** argv)
{
    cout << "arguments:" << endl << endl;

    for (int i = 1; i < argc; ++i)
    {
        int nBytes = 0;

        cout << setw(4) << i << ": " << left << setw(15) << argv[i] << right;

        for (int j = 0; argv[i][j] != 0; ++j)
        {
            ++nBytes;
            cout << " ";
            printHex(argv[i][j]);
        }

        cout << " nBytes: " << nBytes << endl;
    }

    cout << endl;

    return 0;
}
