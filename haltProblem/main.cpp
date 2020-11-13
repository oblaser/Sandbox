/*

author:     Oliver Blaser

date c:     07.11.2020
date e:     13.11.2020

*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

namespace
{
    char resultFilename[] = "haltProblemResults.csv";
}

static unsigned int collatz(unsigned int n);
static unsigned int collatzQuiet(unsigned int n);

static void printHelp();
static void interactiveLoop();
static int analyzer(int max);
static int matlab(int max);

using namespace std;

int main(int argc, char** argv)
{
    int result = 0;
    
    if(argc > 1)
    {
        if((string(*(argv + 1)).compare("-l") == 0) && (argc == 2))
        {
            interactiveLoop();
        }
        
        else if((string(*(argv + 1)).compare("-a") == 0) && (argc == 3))
        {
            int tmpMax = atoi(*(argv + 2));
            
            if(tmpMax > 1) result = analyzer(tmpMax);
            else
            {
                cout << "Invalid MAXIN argument: " << *(argv + 2) << " => " << tmpMax << endl;
                result = 1;
            }
        }
        
        else if((string(*(argv + 1)).compare("-m") == 0) && (argc == 3))
        {
            int tmpMax = atoi(*(argv + 2));
            
            if(tmpMax > 1) result = matlab(tmpMax);
            else
            {
                cout << "Invalid MAXIN argument: " << *(argv + 2) << " => " << tmpMax << endl;
                result = 1;
            }
        }
        
        else if(((string(*(argv + 1)).compare("-h") == 0) ||
                    (string(*(argv + 1)).compare("--help") == 0)) && (argc == 2))
        {
            printHelp();
        }
        
        else if(((string(*(argv + 1)).compare("-v") == 0) ||
                    (string(*(argv + 1)).compare("--version") == 0)) && (argc == 2))
        {
            cout << "sandbox project => no versioning" << endl;
        }
        
        else
        {
            int tmpValue = atoi(*(argv + 1));
            
            if((tmpValue > 0) && (argc == 2))
            {
                unsigned int r = collatzQuiet(tmpValue);
                cout << r << endl;
            }
            
            else
            {
                cout << "invalid arguments" << endl;
                result = 1;
            }
        }
    }
    
    else
    {
        cout << "invalid arguments" << endl;
        result = 1;
    }

    return result;
}

static unsigned int collatz(unsigned int n)
{
    unsigned int cnt = 0;

    while(n > 1)
    {
        if(n & 0x00000001)
        {
            n = (3 * n) + 1;

            cout << "  + ";
        }
        else
        {
            n >>= 1;

            cout << " -  ";
        }

        ++cnt;

        cout << n << endl;
    }

    return cnt;
}

static unsigned int collatzQuiet(unsigned int n)
{
    unsigned int cnt = 0;

    while(n > 1)
    {
        if(n & 0x00000001) n = (3 * n) + 1;
        else n >>= 1;

        ++cnt;
    }

    return cnt;
}

static void printHelp()
{
    const int optWidth = 17;
    
    cout << "An example of the halting problem. Usage: haltProblem [options | number]\n";
    
    cout << "\nOptions:\n" << left;
    cout << setw(optWidth) << "  NUMBER"        << "Just returns the result. (-1 on error)\n";
    cout << setw(optWidth) << "  -m MAXIN"      << "Displays a Octave/Matlab script, for to copy-paste.\n";
    cout << setw(optWidth) << "  -a MAXIN"      << "Runs the algorithm with inputs from 1 to MAXIN and saves the results in \"" << resultFilename << "\". Existing files will be overwritten.\n" ;
    cout << setw(optWidth) << "  -l"            << "Enters an interactive loop. Can be terminated with an inputvalue of 0.\n";
    cout << setw(optWidth) << "  -h, --help"    << "Prints this help text.\n";
    
    cout << "\nOnly one option at once allowed.\n";
    
    cout << "\nSee https://github.com/oblaser/Sandbox/tree/master/haltProblem/ for more information.\n";
    
    cout << endl;
}

static void interactiveLoop()
{
    unsigned int n;
    unsigned int r;

    do
    {
        cout << "enter n: ";
        cin >> n;

        cout << endl;

        r = collatz(n);

        cout << "\n" << r << "\n" << endl;
    }
    while(n != 0);
}

static int analyzer(int max)
{
    int result = 0;
    
    if(max > 1)
    {
        ofstream fileStream;
        
        fileStream.open(resultFilename);
        
        if(fileStream.is_open())
        {
            for(int i = 1; i <= max; ++i)
            {
                unsigned int r = collatzQuiet(i);
                
                fileStream << i << ',' << r << endl;
            }
            
            fileStream.close();
        }
        
        else
        {
            cout << "Unable to open the file." << endl;
            result = 1;
        }
    }
    
    else
    {
        cout << "Invalid MAX value." << endl;
        result = 1;
    }
    
    return result;
}

static int matlab(int max)
{
    int result = 0;
    
    if(max > 1)
    {
        cout << "res = [";
        
        for(int i = 1; i <= max; ++i)
        {
            unsigned int r = collatzQuiet(i);
            
            if(i > 1) cout << ", ";
            
            cout << r;
        }
        
        cout << "];\nhist(res)" << endl;
    }
    
    else
    {
        cout << "Invalid MAX value." << endl;
        result = 1;
    }
    
    return result;
}
