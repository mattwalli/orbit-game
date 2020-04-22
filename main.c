#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

struct key_states
{
    bool space, left, right, enter;
};

void place_sprite( SDL_Renderer* renderer, SDL_Texture* sprite, double x, double y, double angle, double scale );

// Main function handles creation of window, loading sprites, event capture, and rendering.
// I am new to SDL2. This code is hobbled together from multiple tutorials.
// https://lazyfoo.net/tutorials/SDL/ and http://www.programmersranch.com/p/sdl2-tutorials.html

int main(void)
{
    struct key_states user_keys = { false, false, false, false };

    const int NUM_SPRITES = 4;
    const char* const SPRITE_FILES[] = {
        "img/earth.png",
        "img/rocket.png",
        "img/satellite.png",
        "img/fire.png"
    };
    enum sprite_name { EARTH, ROCKET, SATELLITE, FIRE };
    double dx = 0.0;
    double ds = 0.6;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* image = NULL;
    SDL_Texture* sprites[NUM_SPRITES] = { NULL };
    SDL_Texture* text_display = NULL;

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
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC );
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
                    case SDL_KEYDOWN: //Key state changes
                    case SDL_KEYUP:
                        if( !event.key.repeat ) //Filter out key hold repeats
                        {
                            switch( event.key.keysym.sym ) //Set new key state in struct
                            {
                            case SDLK_SPACE:
                                user_keys.space = event.key.state;
                                break;
                            case SDLK_LEFT:
                                user_keys.left = event.key.state;
                                break;
                            case SDLK_RIGHT:
                                user_keys.right = event.key.state;
                                break;
                            case SDLK_RETURN:
                            case SDLK_RETURN2: //Either enter key
                                user_keys.enter = event.key.state;
                                break;
                            default:
                                break;
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }

                //Update game simulation

                //Place sprites
                if( user_keys.space )
                {
                    ds -= 0.01;
                }
                if( user_keys.left )
                {
                    dx -= 0.05;
                }
                if( user_keys.right )
                {
                    dx += 0.05;
                }
                if( user_keys.enter )
                {
                    dx = 0.0;
                    ds = 0.6;
                    user_keys.enter = false;
                }
                place_sprite( renderer, sprites[EARTH], dx, 0.0, 0.0, ds );

                //Update screen
                SDL_RenderPresent( renderer );
                SDL_RenderClear( renderer );
            }
        }
    }
    //Cleanup
    for( int i = 0; i < NUM_SPRITES; i++ )
    {
        SDL_DestroyTexture( sprites[i] );
    }
    SDL_DestroyTexture( text_display );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    IMG_Quit();
    SDL_Quit();

    return 0;
}

// Send given sprite to renderer with screen relative floating point coordinates

void place_sprite( SDL_Renderer* renderer, SDL_Texture* sprite, double x, double y, double angle, double scale )
{
    double f_screen_size = (SCREEN_WIDTH < SCREEN_HEIGHT) ? (SCREEN_WIDTH / 2.0) : (SCREEN_HEIGHT / 2.0);
    SDL_Rect dstrect = { (int)( f_screen_size * (1.0 + x - scale) ), (int)( f_screen_size * (1.0 + y - scale) ),
        (int)( f_screen_size * 2.0 * scale ), (int)( f_screen_size * 2.0 * scale ) };
    SDL_RenderCopyEx(renderer, sprite, NULL, &dstrect, angle, NULL, SDL_FLIP_NONE);
}