#ifndef SANDBOX
#define SANDBOX

#include <SDL3/SDL.h>
#include <iostream>
#include <functional>
#include "renderer.cpp"
#include "particles_manager.cpp"
#include "input_handler.cpp"
#include "drawing_utility.cpp"
#include "elements_data.cpp"
#include "fps_manager.cpp"
#include "settings_manager.cpp"


#define WINDOW_NAME "Sandbox Engine"
// #define WINDOW_WIDTH 1280
// #define WINDOW_HEGHT 720
// #define PARTICLE_SIZE 4.0
// #define UI_SCALE 1.0


class Sandbox
{
    private: int windowWidth = 1280;
    private: int windowHeight = 720;
    private: float particleSize = 4.0;
    private: float uiScale = 1.0;

    SettingsManager settingsManager = SettingsManager();
    FPSManager fpsManager = FPSManager();
    ElementsData elementsData = ElementsData();
    ParticlesManager particlesManager = ParticlesManager();
    Renderer renderer = Renderer();
    InputHandler inputHandler = InputHandler();
    DrawingUtility drawingUtility = DrawingUtility( &particlesManager );

    SDL_Event event;
    bool running = true;
    SDL_FPoint mouseScreenPos;
    SDL_FPoint mouseBoardPos;
    bool wasClickingLastFrame = false;
    bool wasClickingBeforeSelection = false;


    public: void Start()
    {
        Init();

        while ( running ) 
        {
            fpsManager.Update();
            HandleInput();
            if ( fpsManager.shouldUpdateSimulation )
                UpdateSimulation();
            if ( fpsManager.shouldRender )
                Render();
        }
    }


    private: void Init()
    {
        settingsManager.TryLoadSettings();

        fpsManager.Init( settingsManager.simulationFps, settingsManager.renderFps );
        particlesManager.Init( settingsManager.windowWidth/settingsManager.particleSize, settingsManager.windowHeight/settingsManager.particleSize, &elementsData );
        elementsData.TryLoadElementsAndChems();
        // elementsData.LoadDefaultElements();
        // elementsData.LoadDefaultChems();
        int init_exit_code = renderer.Init( std::string( WINDOW_NAME ), settingsManager.windowWidth, settingsManager.windowHeight, settingsManager.particleSize, settingsManager.uiScale, particlesManager.GetBoard(), &elementsData );
        renderer.CreateSelectElementButtons( [this](int id){ drawingUtility.SelectElement( id ); } );
        if ( init_exit_code != 0 )
        {
            std::cerr << "Failed to init renderer. exit code: " << init_exit_code << "\n";
        }

        drawingUtility.onElementSelected = [ this ] ( int element ) { renderer.UpdateSelectedElement( element ); };
        drawingUtility.SelectElement( 0 );
    }


    private: void HandleInput()
    {
        inputHandler.HandleInput();
        mouseScreenPos = inputHandler.GetMousePos();
        mouseBoardPos = renderer.GetScreenToBoardSpace( mouseScreenPos.x, mouseScreenPos.y );
        bool isClicking = inputHandler.GetIsLeftClicking() || inputHandler.GetIsRightClicking();
        bool justClicked = isClicking && !wasClickingLastFrame;

        wasClickingBeforeSelection |= drawingUtility.GetJustSelectedElement() && wasClickingLastFrame;
        if ( !isClicking )
            wasClickingBeforeSelection = false;


        bool isMouseOnUI = renderer.HandleMouseInputForUI( mouseScreenPos, justClicked );

        if ( inputHandler.GetIsQuiting() )
            running = false;
        else if ( inputHandler.GetIsTogglingUI() )
            renderer.ToggleUI();
        else if ( inputHandler.GetIsTogglingSimulationPause() )
            fpsManager.TogglePause();
        else if ( inputHandler.GetIsLeftClicking() && !isMouseOnUI && !wasClickingBeforeSelection )
        {
            drawingUtility.AddParticles( mouseBoardPos.x, mouseBoardPos.y );
        }
        else if ( inputHandler.GetIsRightClicking() && !isMouseOnUI )
        {
            drawingUtility.EraseParticles( mouseBoardPos.x, mouseBoardPos.y );
        }

        else if ( inputHandler.GetIsMiddleClicking() && !isMouseOnUI )
        {
            drawingUtility.SelectElementFromBoard( mouseBoardPos.x, mouseBoardPos.y );
        }
        else if ( inputHandler.GetIsIncreasingBrushSize() )
        {
            drawingUtility.IncreaseBrushSize( 1 );
        }
        else if ( inputHandler.GetIsDecreasingBrushSize() )
        {
            drawingUtility.DecreaseBrushSize( 1 );
        }
        else
        {
            int selectingElement = inputHandler.GetIsSelectingElement();
            if ( selectingElement != -1 && selectingElement < elementsData.GetElementsCount() )
                drawingUtility.SelectElement( selectingElement );
        }

        wasClickingLastFrame = isClicking;
    }


    private: void UpdateSimulation()
    {
        particlesManager.Update();
    }


    private: void Render()
    {
        renderer.SetMousePos( mouseScreenPos );
        renderer.SetMouseMarkerRadius( drawingUtility.brushSize );
        renderer.SetFPSText( fpsManager.GetUpdateFPS() );
        renderer.Render();
    }
};

#endif