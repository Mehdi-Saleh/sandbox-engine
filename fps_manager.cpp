#ifndef FPS_MANAGER
#define FPS_MANAGER

#include <SDL3/SDL.h>

// #define TARGET_SIMULATION_FPS 60
// #define TARGET_RENDER_FPS 60
#define OLD_FPS_STRENGTH_IN_TOTAL_FPS 5

class FPSManager
{
    public: bool shouldUpdateSimulation = true;
    public: bool shouldRender = true;
    public: bool isPaused = false;

    private: float targetSimulationFPS = 60;
    private: float targetRenderFPS = 60;
    
    private: float targetUpdateDelay;
    private: float targetRenderDelay;
    private: Uint64 lastUpdateTimeInMilliseconds = 0;
    private: Uint64 lastRenderTimeInMilliseconds = 0;
    private: float averageUpdateDelay;
    private: float averageRenderDelay;


    public: void Init( float targetSimulationFPS, float targetRenderFPS )
    {
        this->targetSimulationFPS = targetSimulationFPS;
        this->targetRenderFPS = targetRenderFPS;

        lastUpdateTimeInMilliseconds = 0;
        lastRenderTimeInMilliseconds = 0;
        targetUpdateDelay = FPSToDelayInMilliseconds( targetSimulationFPS );
        targetRenderDelay = FPSToDelayInMilliseconds( targetRenderFPS );
        averageUpdateDelay = FPSToDelayInMilliseconds( targetSimulationFPS );
        averageRenderDelay = FPSToDelayInMilliseconds( targetRenderFPS );
    }


    public: void Update()
    {
        CheckShouldUpdateOrRender();
    }


    public: int GetUpdateFPS() const
    {
        if ( isPaused )
            return 0;
        else
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
        if ( isPaused )
            shouldUpdateSimulation = false;

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


    public: void TogglePause()
    {
        isPaused = !isPaused;
    }
};

#endif