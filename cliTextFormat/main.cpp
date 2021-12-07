/*

author:     Oliver Blaser

date c:     15.10.2020
date e:     13.11.2020

*/

#include "cli.h"
#include "project.h"

using namespace cli;

int main()
{   
    println("some tests with formatting in concole applications...");

    print("bright", FGC_BRIGHT_BLACK);
    println("black", FGC_BLACK);
    print("bright", FGC_BRIGHT_RED);
    println("red", FGC_RED);
    print("bright", FGC_BRIGHT_YELLOW);
    println("yellow", FGC_YELLOW);
    print("bright", FGC_BRIGHT_GREEN);
    println("green", FGC_GREEN);
    print("bright", FGC_BRIGHT_CYAN);
    println("cyan", FGC_CYAN);
    print("bright", FGC_BRIGHT_BLUE);
    println("blue", FGC_BLUE);
    print("bright", FGC_BRIGHT_MAGENTA);
    println("magenta", FGC_MAGENTA);
    print("bright", FGC_BRIGHT_WHITE);
    println("white", FGC_WHITE);

    sgrParam(SGR_BGCOLOR_BRIGHT_SET_BASE + SGRCOLOR_WHITE);
    print("bright", FGC_BRIGHT_BLACK);
    print("black", FGC_BLACK);
    sgrParam(SGR_BGCOLOR_DEFAULT);
    print("\n");
    sgrParam(SGR_BGCOLOR_BRIGHT_SET_BASE + SGRCOLOR_WHITE);
    print("bright", FGC_BRIGHT_RED);
    print("red", FGC_RED);
    sgrParam(SGR_BGCOLOR_DEFAULT);
    print("\n");
    sgrParam(SGR_BGCOLOR_BRIGHT_SET_BASE + SGRCOLOR_WHITE);
    print("bright", FGC_BRIGHT_YELLOW);
    print("yellow", FGC_YELLOW);
    sgrParam(SGR_BGCOLOR_DEFAULT);
    print("\n");
    sgrParam(SGR_BGCOLOR_BRIGHT_SET_BASE + SGRCOLOR_WHITE);
    print("bright", FGC_BRIGHT_GREEN);
    print("green", FGC_GREEN);
    sgrParam(SGR_BGCOLOR_DEFAULT);
    print("\n");
    sgrParam(SGR_BGCOLOR_BRIGHT_SET_BASE + SGRCOLOR_WHITE);
    print("bright", FGC_BRIGHT_CYAN);
    print("cyan", FGC_CYAN);
    sgrParam(SGR_BGCOLOR_DEFAULT);
    print("\n");
    sgrParam(SGR_BGCOLOR_BRIGHT_SET_BASE + SGRCOLOR_WHITE);
    print("bright", FGC_BRIGHT_BLUE);
    print("blue", FGC_BLUE);
    sgrParam(SGR_BGCOLOR_DEFAULT);
    print("\n");
    sgrParam(SGR_BGCOLOR_BRIGHT_SET_BASE + SGRCOLOR_WHITE);
    print("bright", FGC_BRIGHT_MAGENTA);
    print("magenta", FGC_MAGENTA);
    sgrParam(SGR_BGCOLOR_DEFAULT);
    print("\n");
    sgrParam(SGR_BGCOLOR_BRIGHT_SET_BASE + SGRCOLOR_WHITE);
    print("bright", FGC_BRIGHT_WHITE);
    print("white", FGC_WHITE);
    sgrParam(SGR_BGCOLOR_DEFAULT);

    println("\n");

#if(PRJ_WIN32 || PRJ_LINUX_ARM) // windows sadly does not have a UTF8 console, or I just didn't figure it out (EDIT: see https://github.com/oblaser/omw)
    char block[] = "#";
#else
    char block[] = { (char)0xE2, (char)0x96, (char)0x84, (char)0x00 };
#endif
    
    print(block, FGC_BRIGHT_RED);
    print(block, FGC_BRIGHT_YELLOW);
    print(block, FGC_BRIGHT_GREEN);
    print(block, FGC_BRIGHT_CYAN);
    print(block, FGC_BRIGHT_BLUE);
    print(block, FGC_BRIGHT_MAGENTA);
    print(block, FGC_BLACK);
    print(block, FGC_BRIGHT_BLACK);
    print(block, FGC_WHITE);
    print(block, FGC_BRIGHT_WHITE);
    
    println("\n");

    print("normal ");
    sgrParam(SGR_BOLD);
    print("bold");
    sgrParam(SGR_BOLD_FAINT_OFF);
    print(" ");
    sgrParam(SGR_UNDERLINE);
    print("underline");
    sgrParam(SGR_UNDERLINE_OFF);
    print(" ");
    sgrParam(SGR_STRIKE_OUT);
    print("stroke-out");
    sgrParam(SGR_STRIKE_OUT_OFF);

    println("\n");

    print("or ");
    sgrParam(SGR_BOLD);
    print("a w");
    sgrParam(SGR_UNDERLINE);
    print("i");
    print("l", FGC_GREEN, FS_REVERSED);
    sgrParam(SGR_BOLD_FAINT_OFF);
    print("d", FGC_GREEN, FS_REVERSED);
    print(" com");
    sgrParam(SGR_BLINK_SLOW);
    print("bi");
    sgrParam(SGR_UNDERLINE_OFF);
    print("nat");
    sgrParam(SGR_BLINK_OFF);
    println("ion");

    println("\n");

    return 0;
}
