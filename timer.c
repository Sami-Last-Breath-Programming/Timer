#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// Clang Setup
#pragma clang diagnostic push
#include "clangFlags.h"

// MiniAudio setup
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

// Error Macros
#define ERROR_ARGS "Please Enter the hr:min:sec\n"
#define ENGINE_ALLOCATION_ERROR "Error: Can't Allocate MiniAudio Engine\n"
#define ERROR_ENGINE_INIT "Error: Can't Init MiniAudio Engine\n"
#define ERROR_SOUND_INIT "Error: Can't Init Sound from file\n"

// Main Entry
int main(int argc, char **args)
{
    bool isTimeout = false;
    int hr, min, sec; 

    ma_result result; 
    ma_engine *pEngine;
    ma_sound sound;

    // Allocate Memoery for the MiniAudio Engine
    pEngine = malloc(sizeof(ma_engine));

    // Handle the Allocations Errors
    if (pEngine == NULL)
    {
        printf(ENGINE_ALLOCATION_ERROR);
        exit(EXIT_FAILURE);
    }

    // Init the Engine 
    result = ma_engine_init(NULL, pEngine);

    // Handle Engine Init Errors 
    if (result != MA_SUCCESS)
    {
        printf(ERROR_ENGINE_INIT);
        exit(EXIT_FAILURE);
    }

    // Init the Sound from file 
    result = ma_sound_init_from_file(pEngine, "sound.mp3", 0, NULL, NULL, &sound);

    // Handle Sound Init Errors 
    if (result != MA_SUCCESS)
    {
        printf(ERROR_SOUND_INIT);
        exit(EXIT_FAILURE);
    }

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

    // Player the Sound
    ma_sound_start(&sound);

    // Wait for Enter to Press
    getchar();

    // Stop Sound
    ma_sound_stop(&sound);

    // Free the Engine
    ma_engine_uninit(pEngine);

    return EXIT_SUCCESS;
}
#pragma clang diagnostic pop
