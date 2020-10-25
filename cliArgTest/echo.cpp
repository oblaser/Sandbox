/*

Author:     Oliver Blaser

Date c:     22.10.2020
Date e:     22.10.2020

(c) Oliver Blaser

*/

#include <iostream>
#include <iomanip>
#include <string>

#include "echo.h"

using namespace std;

// test command: ./cliArgTest -a -f adsf argX -p

int echo::main(int argc, const char** argv)
{
    cout << "arguments:" << endl << endl;

#if(1)

    for(int i = 0; i < argc; ++i) cout << setw(4) << i << ": " << string(argv[i]) << endl;

#else

    for(int i = 0; i < argc; ++i)
    {
        //cout << setw(4) << i << ": " << argv[i] << endl;
        cout << setw(4) << i << ": " << *(argv + i) << endl;
    }

#endif

    cout << endl;

    return 0;
}
