#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main(void)
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;

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

            //Load textures
            renderer = SDL_CreateRenderer(window, -1, 0);
            image = IMG_Load("earth.png");
            if( image == NULL )
            {
                printf( "Unable to load image! SDL_image Error: %s\n", IMG_GetError() );
            }
            texture = SDL_CreateTextureFromSurface(renderer, image);
            if( texture == NULL )
            {
                printf( "Unable to load texture! SDL_image Error: %s\n", IMG_GetError() );
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
                    switch(event.type)
                    {
                    case SDL_QUIT: //User requested quit
                        quit = true;
                        break;
                    }
                }

                //Decorate the surface
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
            
                //Update the surface
                SDL_UpdateWindowSurface( window );
            }
        }
    }
    //Cleanup
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    IMG_Quit();
    SDL_Quit();

    return 0;
}