#ifndef ELEMENTS_DATA
#define ELEMENTS_DATA

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <set>
#include <algorithm>
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


struct ChemData
{
    public: std::multiset<int> inElements;
    public: std::multiset<int> outElements;
    public: float chance;

    public: bool empty()
    {
        return inElements.empty();
    }
};


class ElementsData
{
    private: std::vector<ElementParticleData> elementsParticleData;
    private: std::vector<ElementRenderingData> elementsRenderingData;
    private: std:: vector<ChemData> chemsData;

    private: ElementParticleData emptyParticleData = ElementParticleData();
    private: ElementRenderingData emptyRenderingData = ElementRenderingData();
    private: ChemData emptyChemData = ChemData();
    private: int elementsCount = 0;


    public: ElementsData()
    {
        emptyRenderingData.color.r = 255;
        emptyRenderingData.color.g = 0;
        emptyRenderingData.color.b = 255;
        emptyRenderingData.color.a = 255;
        emptyChemData.chance = 0.0;
    }


    ~ElementsData()
    {
        ClearElements();
        ClearChems();
    }


    public: void LoadDefaultElements()
    {
        AddElement( "Ground Solid 5.0 #1e1e1e" );
        AddElement( "Sand Powder 5.0 #fcdb03" );
        AddElement( "Stone Powder 10.0 #635c5c" );
        AddElement( "Snow Powder 0.9 #fffafa" );
        AddElement( "Water Liquid 1.0 #0703db" );
        AddElement( "Oil Liquid 0.8 #ab830a" );
        AddElement( "Magma Liquid 8.0 #fc3003" );
        AddElement( "Steam Gas 0.05 #5c626e" );
        AddElement( "Smoke Gas 0.03 #464862" );
    }


    public: void LoadDefaultChems()
    {
        // Add default chems
        // Sand Water =>1.0 Stone
        chemsData.push_back(
            ChemData {
                std::multiset<int> { 6, 4 },
                std::multiset<int> { 2, 7 },
                1.0
            }
        );

        // Stone Oil =>1.0 Pufff!
        chemsData.push_back(
            ChemData {
                std::multiset<int> { 6, 2 },
                std::multiset<int> { 6, 6 },
                1.0
            }
        );
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


    private: void ClearChems()
    {
        chemsData.clear();
    }


    public: bool AddChem( std::string chemData )
    {
        // TODO
        return true;
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


    public: ChemData GetChem( int chemId )
    {
        return chemsData[chemId];
    }


    public: ChemData& DecideChem( std::multiset<int> &inElements )
    {
        std::vector<int> possibleChems = GetAllPossibleChems( inElements );
        if ( possibleChems.empty() )
            return emptyChemData;
        
        return chemsData[possibleChems[0]];
    }


    public: std::vector<int> GetAllPossibleChems( std::multiset<int> &inElements )
    {
        std::vector<int> possibleChems;

        int count = GetChemsCount();
        for ( int i = 0; i < count; i++ )
        {
            if ( std::includes( 
                inElements.begin(), inElements.end(), 
                chemsData[i].inElements.begin(), chemsData[i].inElements.end() 
                ) 
                )
                possibleChems.push_back( i );
        }

        return possibleChems;
    }


    public: int GetElementsCount() const
    {
        return elementsCount;
    }


    public: int GetChemsCount() const
    {
        return chemsData.size();
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
        else
            return PARTICLE_STATE_SOLID;
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


    struct SetIsGreaterComparator 
    {
        // Operator() overloading
        bool operator()( std::multiset<int> &s0, std::multiset<int> &s1 ) const
        {
            // new definition
            return s0.size() > s1.size();
        }
    };
};

#endif