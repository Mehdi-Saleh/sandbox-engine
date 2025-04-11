#include <SDL3/SDL.h>
#include <iostream>
#include </home/mehdi/My Projects/sandbox-engine/renderer.cpp>


#define WINDOW_NAME "Sandbox Engine"
#define WINDOW_WIDTH 640
#define WINDOW_HEGHT 480

int main(int argc, char* argv[]) 
{
    Renderer renderer = Renderer( string( WINDOW_NAME ), WINDOW_WIDTH, WINDOW_HEGHT );
    int init_exit_code = renderer.Init();
    if ( init_exit_code != 0 )
    {
        cerr << "Failed to init renderer. exit code: " << init_exit_code << "\n";
        return 1;
    }

    SDL_Event e;
    bool running = true;

    while ( running ) 
    {
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) 
            {
                running = false;
            }
        }

        renderer.RenderBoard();
    }
    
    return 0;
}