/*

Author:     Oliver Blaser

Date c:     22.10.2020
Date e:     22.10.2020

(c) Oliver Blaser

*/

#include "echo.h"
#include "encoding.h"

int main(int argc, const char** argv)
{
    int r;

    //r = echo::main(argc, argv);
    r = encoding::main(argc, argv);

    return r;
}
