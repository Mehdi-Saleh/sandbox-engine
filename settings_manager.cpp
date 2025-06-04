#ifndef SETTINGS_MANAGER
#define SETTINGS_MANAGER

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define SETTINGS_FILE_PATH "./settings.txt"

class SettingsManager
{
    public: int windowWidth = 1280;
    public: int windowHeight = 720;
    public: float particleSize = 4.0;
    public: float uiScale = 1.0;
    public: float simulationFps = 60.0;
    public: float renderFps = 60.0;


    public: void LoadDefaultSettings()
    {
        windowWidth = 1280;
        windowHeight = 720;
        particleSize = 4.0;
        uiScale = 1.0;
    }


    public: bool TryLoadSettings()
    {
        bool successful = true;
        try
        {   
            std::ifstream file( SETTINGS_FILE_PATH );
            if ( !file.is_open() ) 
            {
                std::cerr << "Error opening the settings file!" << std::endl;
                successful = false;
            }

            std::string line;
            while ( getline( file, line ) )
                if ( !LoadSetting( line ) )
                    successful = false;

            file.close();
        }
        catch(const std::exception& e)
        {
            std::cerr << "Could not load settings from file correctly: " << e.what() << std::endl;
            successful = false;
        }

        if ( !successful )
            LoadDefaultSettings();
        
        return successful;
    }


    private: bool LoadSetting( const std::string& setting )
    {
        std::vector<std::string> parts = SplitString( setting, ' ' );
        
        if ( parts[0] == "WINDOW_WIDTH" )
        {
            windowWidth = std::stoi( parts[1] );
        }
        else if ( parts[0] == "WINDOW_HEIGHT" )
        {
            windowHeight = std::stoi( parts[1] );
        }
        else if ( parts[0] == "PARTICLE_SIZE" )
        {
            particleSize = std::stof( parts[1] );
        }
        else if ( parts[0] == "UI_SCALE" )
        {
            uiScale = std::stof( parts[1] );
        }
        else if ( parts[0] == "SIMULATION_FPS" )
        {
            simulationFps = std::stof( parts[1] );
        }
        else if ( parts[0] == "RENDER_FPS" )
        {
            renderFps = std::stof( parts[1] );
        }
        else if ( parts[0][0] == '#' )
        {
            // pass
        }
        else
        {
            std::cerr << "Could not load setting \"" << setting << "\"" << std::endl;
            return false;
        }

        return true;
    }


    private: std::vector<std::string> SplitString( const std::string &input, char seperator ) 
    {
        std::stringstream stream( input );
        std::string supstring;
        std::vector<std::string> output;
        while ( std::getline( stream, supstring, seperator ) ) 
        {
            output.push_back( supstring );
        }
        return output;
    }
};

#endif