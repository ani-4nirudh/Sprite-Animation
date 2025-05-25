// C++ Standard Library
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

// 3rd Party Library
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

const int WINDOW_HEIGHT = 400;
const int WINDOW_WIDTH = 400;
const int FPS = 30;
const int ANIMATION_FRAME_COUNT = 6;
const int SPRITE_FRAME_WIDTH = 30;
const int SPRITE_FRAME_HEIGHT = 25;
const std::string SPRITE_SHEET_PATH = "../assets/dog_sprite.png";
// const std::string SPRITE_SHEET_PATH = "../assets/7966219.jpg";
const std::string OUTPUT_FRAMES_DIR = "frames";

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Surface* surface = NULL;
static SDL_Texture* texture = NULL;

bool isRunning = true;


int main(int argc, char* argv[])
{
    // Check if the SDL library is present
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "ERROR: SDL library not found" << SDL_GetError() << std::endl;
        std::cout << "!! Exiting the program !!" << std::endl;
        return EXIT_FAILURE;
    } else
    {
        std::cout << "!! Creating window and renderer !!" << std::endl;
        window = SDL_CreateWindow("Running Dog", WINDOW_HEIGHT, WINDOW_WIDTH, SDL_WINDOW_RESIZABLE); // SDL_WindowFlags is set to 0
        renderer = SDL_CreateRenderer(window, NULL); // SDL will choose the rendering driver on its own
    }

    surface = IMG_Load(SPRITE_SHEET_PATH.c_str());
    if (surface == NULL)
    {
        std::cout << "!! Exiting the program because of image load failure !!\n" << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    int frame_count = 0;
    SDL_FRect source, destination;
    source.x = 240;
    source.y = 10;
    source.w = SPRITE_FRAME_WIDTH;
    source.h = SPRITE_FRAME_HEIGHT;
    destination.x = (WINDOW_WIDTH - SPRITE_FRAME_WIDTH) / 2.0f;
    destination.y = (WINDOW_HEIGHT - SPRITE_FRAME_HEIGHT) / 2.0f;
    destination.w = SPRITE_FRAME_WIDTH;
    destination.h = SPRITE_FRAME_HEIGHT;

    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                isRunning = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        source.x = (frame_count % 7) * 70;
        SDL_RenderTexture(renderer, texture, &source, &destination);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        frame_count++;
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    std::cout << "!! SDL window closed !!" << std::endl;
    
    return EXIT_SUCCESS;
}
