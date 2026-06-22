#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Clang Setup
#pragma clang diagnostic push
#include "lib/clangFlags.h"

// MiniAudio setup
#define MINIAUDIO_IMPLEMENTATION
#include "lib/miniaudio.h"

// Errors Setup 
#include "lib/errorsTimer.h"

// Macros
#define FOREVER 1

// Main Entry
int main(int argc, char **args)
{
    int hr, min, sec;
    const char soundPath[] = "/home/lbs/Desktop/BackYard/Timer/assets/sound.mp3";

    ma_result result; 
    ma_engine *pEngine = NULL;
    ma_sound *sound = NULL;

    // Allocate Memoery for the MiniAudio Engine
    pEngine = malloc(sizeof(ma_engine));
    sound = malloc(sizeof(ma_sound));

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
    result = ma_sound_init_from_file(pEngine, soundPath, MA_SOUND_FLAG_DECODE, NULL, NULL, sound);

    // Handle Sound Init Errors 
    if (result != MA_SUCCESS)
    {
        printf(ERROR_SOUND_INIT);
        exit(EXIT_FAILURE);
    }

    // Handle Arguments errors
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
    while(FOREVER)
    {
        // Print the timer
        system("clear");
        printf("%02d : %02d : %02d\n", hr, min, sec);
        
        // Logic for time 
        if (sec == 0 && min != 0)
        {    min--; sec = 59;   }

        else if (sec == 0 && min == 0 && hr != 0)
        {   hr--; min = 59; sec = 59;   }
        
        else sec--;

        // Check for time out 
        if (sec < 0) break;

        sleep(1);
    }

    // Set the looping of sound 
    ma_sound_set_looping(sound, MA_TRUE);

    // Player the Sound
    result = ma_sound_start(sound);

    // Handle Sound Start Error
    if (result != MA_SUCCESS)
    {
        printf(ERROR_SOUND_START);
        exit(EXIT_FAILURE);
    }

    // Wait for Enter Press
    getchar();

    // Stop Sound
    result = ma_sound_stop(sound);

    // Handle Sound Start Error
    if (result != MA_SUCCESS)
    {
        printf(ERROR_SOUND_STOP);
        exit(EXIT_FAILURE);
    }

    // Unint Engine and Sound
    ma_engine_uninit(pEngine);
    ma_sound_uninit(sound);

    // Free Structs
    free(sound);
    free(pEngine);

    return EXIT_SUCCESS;
}
#pragma clang diagnostic pop
