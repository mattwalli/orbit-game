#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Main function handles creation of window, loading sprites, event capture, and rendering.
// I am new to SDL2. This code is hobbled together from multiple tutorials.
// https://lazyfoo.net/tutorials/SDL/ and http://www.programmersranch.com/p/sdl2-tutorials.html

int main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 800;
    const int NUM_SPRITES = 4;
    const char* const SPRITE_FILES[] = {
        "fire.png",
        "rocket.png",
        "satellite.png",
        "earth.png"
    };

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;

    SDL_Texture* sprites[NUM_SPRITES] = { NULL };

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "Orbit Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Initialize PNG loading
            if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            }

            //Load sprites
            renderer = SDL_CreateRenderer( window, -1, 0 );
            for( int i = 0; i < NUM_SPRITES; i++ )
            {
                image = IMG_Load( SPRITE_FILES[i] );
                if( image == NULL )
                {
                    printf( "Unable to load image! SDL_image Error: %s\n", IMG_GetError() );
                }
                else
                {
                    sprites[i] = SDL_CreateTextureFromSurface( renderer, image );
                    if( sprites[i] == NULL )
                    {
                        printf( "Unable to load texture! SDL_image Error: %s\n", IMG_GetError() );
                    }
                    SDL_FreeSurface( image );
                }
            }

            //Event handler
            SDL_Event event;

            //Main loop
            bool quit = false;
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &event ) != 0 )
                {
                    switch( event.type )
                    {
                    case SDL_QUIT: //User requested quit
                        quit = true;
                        break;
                    }
                }

                //Decorate the surface
                SDL_RenderCopy(renderer, sprites[3], NULL, NULL);
                SDL_RenderPresent(renderer);
            
                //Update the surface
                SDL_UpdateWindowSurface( window );
            }
        }
    }
    //Cleanup
    SDL_DestroyTexture( texture );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    IMG_Quit();
    SDL_Quit();

    return 0;
}