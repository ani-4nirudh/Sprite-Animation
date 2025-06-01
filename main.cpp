// C++ Standard Library
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

// 3rd Party Library
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

// Values for trees animation
const int ANIMATION_FRAMES = 6;
const int SPRITE_FRAME_WIDTH = 420;
const int SPRITE_FRAME_HEIGHT = 400;
const int START_Y_PIXEL = 0;
const int SECOND_ROW_Y = 480;
const int WINDOW_HEIGHT = SPRITE_FRAME_HEIGHT;
const int WINDOW_WIDTH = SPRITE_FRAME_WIDTH;
const std::string SPRITE_SHEET_PATH = "../assets/trees.png";
const std::string OUTPUT_FRAMES_DIR = "../frames";

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
        window = SDL_CreateWindow("Trees", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE); // SDL_WindowFlags is set to 0
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
    int animation_cycles = 2;
    SDL_FRect source, destination;
    source.x = 0; 
    source.y = START_Y_PIXEL;
    source.w = SPRITE_FRAME_WIDTH;
    source.h = SPRITE_FRAME_HEIGHT;
    destination.x = (WINDOW_WIDTH - SPRITE_FRAME_WIDTH) / 2.0f;
    destination.y = (WINDOW_HEIGHT - SPRITE_FRAME_HEIGHT) / 2.0f;
    destination.w = SPRITE_FRAME_WIDTH;
    destination.h = SPRITE_FRAME_HEIGHT;

    if (!std::filesystem::exists(OUTPUT_FRAMES_DIR))
    {
        std::filesystem::create_directory(OUTPUT_FRAMES_DIR);
    }

    while (isRunning && (animation_cycles > 0))
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

        int row = frame_count / 3; // Cycles between 0, 1 and 2
        int col = frame_count % 3; // Cycles between 0 and 1 
        
        source.x = col * SPRITE_FRAME_WIDTH;
        source.y = row * START_Y_PIXEL;

        SDL_RenderTexture(renderer, texture, &source, &destination);
        SDL_RenderPresent(renderer);

        SDL_Surface* screenshot = SDL_RenderReadPixels(renderer, NULL);
        if (screenshot)
        {
            std::string filename = OUTPUT_FRAMES_DIR + "/frame_" + std::to_string(animation_cycles) + "_" + std::to_string(frame_count) + ".png";
            IMG_SavePNG(screenshot, filename.c_str());
            SDL_DestroySurface(screenshot);
        }

        SDL_Delay(500);
        frame_count++;

        if (frame_count >= ANIMATION_FRAMES)
        {
            frame_count = 0; // Reset
            animation_cycles--;
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    std::cout << "!! SDL window closed !!" << std::endl;
    
    return EXIT_SUCCESS;
}
