#ifndef ELEMENTS_DATA
#define ELEMENTS_DATA

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <SDL3/SDL.h>


#define PARTICLE_STATE_SOLID 0
#define PARTICLE_STATE_POWDER 1
#define PARTICLE_STATE_LIQUID 2
#define PARTICLE_STATE_GAS 3

#define ELEMENTS_FILE_PATH "./elements.txt"


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


    public: bool TryLoadElementsAndChems()
    {
        ClearElements();
        ClearChems();
        bool successful = true;
        try
        {   
            std::ifstream file( ELEMENTS_FILE_PATH );
            if ( !file.is_open() ) 
            {
                std::cerr << "Error opening the elements file!" << std::endl;
                successful = false;
            }

            const int MODE_ELEMENT = 0;
            const int MODE_CHEM = 1;
            int mode = MODE_ELEMENT;
            std::string line;
            while ( getline( file, line ) )
            {
                if ( line.empty() )
                    continue;
                if ( line.compare( "#Elements" ) == 0 )
                {
                    mode = MODE_ELEMENT;
                    continue;
                }
                else if ( line.compare( "#Chems" ) == 0 )
                {
                    mode = MODE_CHEM;
                    continue;
                }
                
                if ( mode == MODE_ELEMENT )
                    if ( !AddElement( line ) )
                        successful = false;
                if ( mode == MODE_CHEM )
                    if ( !AddChem( line ) )
                        successful = false;
            }

            file.close();
        }
        catch(const std::exception& e)
        {
            std::cerr << "Could not load elements/chems from file correctly: " << e.what() << std::endl;
            successful = false;
        }

        if ( !successful )
        {
            ClearElements();
            ClearChems();
            LoadDefaultElements();
            LoadDefaultChems();
        }
        
        return successful;
    }


    public: void LoadDefaultElements()
    {
        AddElement( "Ground Solid 5.0 #1e1e1e" );
        AddElement( "Stone Solid 10.0 #505555" );
        AddElement( "Wood Solid 2.0 #693406" );
        AddElement( "Lit_Wood Solid 2.0 #fc2c03" );
        AddElement( "Sand Powder 5.0 #fcdb03" );
        AddElement( "Dust Powder 10.0 #635c5c" );
        AddElement( "Snow Powder 0.9 #fffafa" );
        AddElement( "Water Liquid 1.0 #0703db" );
        AddElement( "Oil Liquid 0.8 #ab830a" );
        AddElement( "Lit_Oil Liquid 0.8 #fc4a03" );
        AddElement( "Lava Liquid 8.0 #fc3003" );
        AddElement( "Steam Gas 0.05 #5c626e" );
        AddElement( "Smoke Gas 0.03 #464862" );
        AddElement( "Fire Gas 0.001 #fc8312" );
    }


    public: void LoadDefaultChems()
    {
        AddChem( "Lava Water =1.0 Stone Steam");
        AddChem( "Lava Snow =0.1 Water");
        AddChem( "Lava Stone =0.01 Lava Lava");
        AddChem( "Lava Dust =0.02 Lava Lava");
        AddChem( "Lava Wood =0.02 Lava Lit_Wood");
        AddChem( "Lava Oil =0.02 Lava Lit_Oil");
        AddChem( "Fire =0.15");
        AddChem( "Fire Water =0.1 Steam");
        AddChem( "Fire Snow =0.1 Water");
        AddChem( "Fire Stone =0.01 Lava");
        AddChem( "Fire Dust =0.02 Lava");
        AddChem( "Fire Wood =0.02 Lit_Wood");
        AddChem( "Wood Lit_Wood =0.005 Lit_Wood Lit_Wood");
        AddChem( "Lit_Wood Water =0.2 Wood Steam");
        AddChem( "Lit_Wood =0.001 Wood");
        AddChem( "Fire Oil =0.1 Lit_Oil");
        AddChem( "Oil Lit_Oil =0.05 Lit_Oil Lit_Oil");
        AddChem( "Lit_Oil Water =0.2 Oil Steam");
        AddChem( "Lit_Oil =0.001 Oil");
        AddChem( "Wood Lit_Oil =0.05 Lit_Wood Lit_Oil");
        AddChem( "Oil Lit_Wood =0.05 Lit_Oil Lit_Wood");
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
        // Example:
        // E0 E2 =CHANCE E3 E4
        // Stone Lava =0.01 Lava Lava
        
        bool successful = true;
        ChemData finalChemData;

        try
        {
            std::vector<std::string> substrings = SplitString( chemData, ' ' );
            int i = 0;
            for ( ; i < substrings.size(); i++ )
            {
                if ( substrings[i].front() == '=' )
                    break;
                int chem = GetStringToChemId( substrings[i] );
                if ( chem != -1 )
                    finalChemData.inElements.insert( chem );
                else
                    successful = false;
            }
            finalChemData.chance = std::stof( substrings[i].substr( 1, substrings[i].size()-1 ) );
            i++;
            for ( ; i < substrings.size(); i++ )
            {
                int chem = GetStringToChemId( substrings[i] );
                if ( chem != -1 )
                    finalChemData.outElements.insert( chem );
                else
                    successful = false;
            }
        }
        catch( const std::exception& e )
        {
            std::cerr << "Could not parse chemistry data \"" << chemData << "\":" << e.what() << '\n';
            successful = false;
        }
        
        if ( successful )
        {
            chemsData.push_back( finalChemData );
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


    public: ChemData GetChem( int chemId )
    {
        return chemsData[chemId];
    }


    public: ChemData& DecideChem( std::multiset<int> &inElements )
    {
        std::vector<int> possibleChems = GetAllPossibleChems( inElements );
        if ( possibleChems.empty() )
            return emptyChemData;
        
        for ( int chem : possibleChems )
        {
            if ( SDL_randf() < chemsData[chem].chance )
                return chemsData[chem];
        }
        return emptyChemData;
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


    private: inline int GetStringToChemId( const std::string input )
    {
        for ( int i = 0; i < elementsCount; i++ )
            if ( elementsRenderingData[i].name.compare( input ) == 0 )
                return i;
        std::cerr << "Could not parse element name \"" << input << "\"\n";
        return -1;
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