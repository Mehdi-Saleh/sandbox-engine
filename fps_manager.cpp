#ifndef FPS_MANAGER
#define FPS_MANAGER

#include <SDL3/SDL.h>

#define TARGET_SIMULATION_FPS 60
#define TARGET_RENDER_FPS 60
#define OLD_FPS_STRENGTH_IN_TOTAL_FPS 5

class FPSManager
{
    public: bool shouldUpdateSimulation = true;
    public: bool shouldRender = true;
    
    
    private: float targetUpdateDelay = FPSToDelayInMilliseconds( TARGET_SIMULATION_FPS );
    private: float targetRenderDelay = FPSToDelayInMilliseconds( TARGET_RENDER_FPS );
    private: Uint64 lastUpdateTimeInMilliseconds = 0;
    private: Uint64 lastRenderTimeInMilliseconds = 0;
    private: float averageUpdateDelay = FPSToDelayInMilliseconds( TARGET_SIMULATION_FPS );
    private: float averageRenderDelay = FPSToDelayInMilliseconds( TARGET_RENDER_FPS );


    public: void Update()
    {
        CheckShouldUpdateOrRender();
    }


    public: int GetUpdateFPS() const
    {
        return DelayInMillisecondsToFPS( averageUpdateDelay ) + 1;
    }


    public: int GetRenderFPS() const
    {
        return DelayInMillisecondsToFPS( averageRenderDelay ) + 1;
    }


    private: void CheckShouldUpdateOrRender()
    {
        Uint64 newTimePassed = SDL_GetTicks();

        shouldUpdateSimulation = false;
        int timeSinceLastUpdate = newTimePassed - lastUpdateTimeInMilliseconds;
        if ( timeSinceLastUpdate > targetUpdateDelay )
        {
            shouldUpdateSimulation = true;
            lastUpdateTimeInMilliseconds = newTimePassed;
            UpdateAverageUpdateDelay( timeSinceLastUpdate );
        }

        shouldRender = false;
        int timeSinceLastRender = newTimePassed - lastRenderTimeInMilliseconds;
        if ( timeSinceLastRender > targetRenderDelay )
        {
            shouldRender = true;
            lastRenderTimeInMilliseconds = newTimePassed;
            UpdateAverageRenderDelay( timeSinceLastRender );
        }
    }


    private: void UpdateAverageUpdateDelay( int thisFramesDelay )
    {
        averageUpdateDelay = (
            ( averageUpdateDelay * OLD_FPS_STRENGTH_IN_TOTAL_FPS + thisFramesDelay ) 
            / ( OLD_FPS_STRENGTH_IN_TOTAL_FPS + 1 )
            );
    }


    private: void UpdateAverageRenderDelay( int thisFramesDelay )
    {
        averageRenderDelay = (
            ( averageRenderDelay * OLD_FPS_STRENGTH_IN_TOTAL_FPS + thisFramesDelay ) 
            / ( OLD_FPS_STRENGTH_IN_TOTAL_FPS + 1 )
            );
    }


    private: inline float FPSToDelayInMilliseconds( float fps ) const
    {
        return 1000.0 / fps;
    }


    private: inline float DelayInMillisecondsToFPS( float delayInMilliseconds ) const
    {
        return 1000.0 / delayInMilliseconds;
    }
};

#endif