#ifndef ELEMENTS_DATA
#define ELEMENTS_DATA

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <SDL3/SDL.h>


#define PARTICLE_STATE_SOLID 0
#define PARTICLE_STATE_POWDER 1
#define PARTICLE_STATE_LIQUID 2
#define PARTICLE_STATE_GAS 3


struct ElementParticleData
{
    public: int state;
    public: float density;

};


struct ElementRenderingData
{
    public: std::string name;
    public: SDL_Color color;

};


class ElementsData
{
    private: std::vector<ElementParticleData> elementsParticleData;
    private: std::vector<ElementRenderingData> elementsRenderingData;

    private: ElementParticleData emptyParticleData = ElementParticleData();
    private: ElementRenderingData emptyRenderingData = ElementRenderingData();
    private: int elementsCount = 0;


    public: ElementsData()
    {
        emptyRenderingData.color.r = 255;
        emptyRenderingData.color.g = 0;
        emptyRenderingData.color.b = 255;
        emptyRenderingData.color.a = 255;
    }


    ~ElementsData()
    {
        ClearElements();
    }


    public: void LoadDefaultElements()
    {
        AddElement( "Ground Solid 5.0 #1e1e1e" );
        AddElement( "Sand Powder 5.0 #fcdb03" );
        AddElement( "Stone Powder 10.0 #635c5c" );
        AddElement( "Snow Powder 0.9 #fffafa" );
        AddElement( "Water Liquid 1.0 #0703db" );
        AddElement( "Oil Liquid 0.8 #ab830a" );
        AddElement( "Steam Gas 0.05 #5c626e" );
        AddElement( "Smoke Gas 0.03 #464862" );
    }


    private: void ClearElements()
    {
        elementsParticleData.clear();
        elementsRenderingData.clear();
        elementsCount = 0;
    }


    public: bool AddElement( std::string elementData )
    {
        // Example:
        // NAME STATE DENSITY HEX_COLOR
        // Sand Powder 5.0 FFFFFF
        
        bool successful = true;
        ElementParticleData particleData;
        ElementRenderingData renderingData;

        try
        {
            std::vector<std::string> substrings = SplitString( elementData, ' ' );
            renderingData.name = substrings[0];
            particleData.state = GetStringToState( substrings[1] );
            particleData.density = std::stof( substrings[2] );
            renderingData.color = GetHexToColor( substrings[3] );
        }
        catch( const std::exception& e )
        {
            std::cerr << "Could not parse element data \"" << elementData << "\":" << e.what() << '\n';
            successful = false;
        }
        
        if ( successful )
        {
            elementsParticleData.push_back( particleData );
            elementsRenderingData.push_back( renderingData );
            elementsCount = elementsParticleData.size();
        }

        return successful;
    }


    public: ElementParticleData* GetParticleData( int id )
    {
        if ( id >= elementsCount || id < 0 )
        {
            std::cerr << "Element's particle data with id \"" << id << "\" doesn't exist! \n";
            return &emptyParticleData;
        }
        return &elementsParticleData[id];
    }


    public: ElementRenderingData* GetRenderingData( int id )
    {
        if ( id >= elementsCount || id < 0 )
        {
            std::cerr << "Element's rendering data with id \"" << id << "\" doesn't exist! \n";
            return &emptyRenderingData;
        }
        return &elementsRenderingData[id];
    }


    public: int GetElementsCount() const
    {
        return elementsCount;
    }


    private: SDL_Color GetHexToColor( std::string hex )
    {
        SDL_Color color = SDL_Color();
        if ( hex[0] == '#' )
            hex = hex.substr( 1 );
        color.r = std::stoi( hex.substr( 0, 2 ), nullptr, 16 );
        color.g = std::stoi( hex.substr( 2, 2 ), nullptr, 16 );
        color.b = std::stoi( hex.substr( 4, 2 ), nullptr, 16 );
        color.a = 255;
        return color;
    }


    private: inline int GetStringToState( const std::string input )
    {
        if ( input == "Solid" )
            return PARTICLE_STATE_SOLID;
        else if ( input == "Powder" )
            return PARTICLE_STATE_POWDER;
        else if ( input == "Liquid" )
            return PARTICLE_STATE_LIQUID;
        else if ( input == "Gas" )
            return PARTICLE_STATE_GAS;
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