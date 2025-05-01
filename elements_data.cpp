#ifndef ELEMENTS_DATA
#define ELEMENTS_DATA

#include <iostream>
#include <SDL3/SDL.h>
#include <string>


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
    private: int elementsCount = 0;
    private: ElementParticleData* elementsParticleData = nullptr;
    private: ElementRenderingData* elementsRenderingData = nullptr;

    private: ElementParticleData emptyParticleData = ElementParticleData();
    private: ElementRenderingData emptyRenderingData = ElementRenderingData();


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
        elementsParticleData = new ElementParticleData[6];
        elementsRenderingData = new ElementRenderingData[6];
        elementsCount = 6;

        // Element 0
        elementsParticleData[0].state = PARTICLE_STATE_SOLID;
        elementsParticleData[0].density = 5.0;
        elementsRenderingData[0].name = "Ground";
        SDL_Color color = SDL_Color();
        color.r = 30;
        color.g = 30;
        color.b = 30;
        color.a = 255;
        elementsRenderingData[0].color = color;

        // Element 1
        elementsParticleData[1].state = PARTICLE_STATE_POWDER;
        elementsParticleData[1].density = 5.0;
        elementsRenderingData[1].name = "Sand";
        color = SDL_Color();
        color.r = 252;
        color.g = 219;
        color.b = 3;
        color.a = 255;
        elementsRenderingData[1].color = color;

        // Element 2
        elementsParticleData[2].state = PARTICLE_STATE_LIQUID;
        elementsParticleData[2].density = 1.0;
        elementsRenderingData[2].name = "Water";
        color = SDL_Color();
        color.r = 6;
        color.g = 3;
        color.b = 219;
        color.a = 255;
        elementsRenderingData[2].color = color;

        // Element 3
        elementsParticleData[3].state = PARTICLE_STATE_GAS;
        elementsParticleData[3].density = 0.05;
        elementsRenderingData[3].name = "Steam";
        color = SDL_Color();
        color.r = 92;
        color.g = 98;
        color.b = 110;
        color.a = 255;
        elementsRenderingData[3].color = color;

        // Element 4
        elementsParticleData[4].state = PARTICLE_STATE_LIQUID;
        elementsParticleData[4].density = 0.8;
        elementsRenderingData[4].name = "Oil";
        color = SDL_Color();
        color.r = 171;
        color.g = 131;
        color.b = 10;
        color.a = 255;
        elementsRenderingData[4].color = color;


        // Element 5
        elementsParticleData[5].state = PARTICLE_STATE_GAS;
        elementsParticleData[5].density = 0.03;
        elementsRenderingData[5].name = "Smoke";
        color = SDL_Color();
        color.r = 70;
        color.g = 72;
        color.b = 98;
        color.a = 255;
        elementsRenderingData[5].color = color;
    }


    private: void ClearElements()
    {
        delete [] elementsParticleData;
        delete [] elementsRenderingData;
        elementsCount = 0;
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
};

#endif