#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// Clang Flags
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"

// Error Macros
#define ERROR_ARGS "Please Enter the hr:min:sec\n"

// Main Entry
int main(int argc, char **args)
{
    bool isTimeout = false;
    int hr, min, sec; 

    // Handle arguments errors
    if (argc < 4)
    {
        printf(ERROR_ARGS);
        exit(EXIT_FAILURE);
    }

    // Assign Arguments
    hr = atoi(args[1]);
    min = atoi(args[2]);
    sec = atoi(args[3]);

    // Main Loop
    while (!isTimeout)
    {
        if (sec == 0 && min != 0)
        {
            min--;
            sec = 59;
        }
        else if (sec == 0 && min == 0 && hr != 0)
        {
            hr--;
            min = 59;
            sec = 59;
        }
        else sec--;
    
        // Wait for 1 second
        sleep(1);

        // Check for time out 
        if (sec < 0)
            break;
        
        // Print the timer
        system("clear");
        printf("%02i : %02i : %02i\n", hr, min, sec);

    }
    return EXIT_SUCCESS;
}
#pragma clang diagnostic pop
