#pragma once
#include "CelestialBody.hpp"
#include <vector>

class Universe{
    private:
        std::vector<Body*> bodyList;
        double bodyCount;
        double universeRadius;
    public:
        Universe();
        void drawBodies(sf::RenderWindow &win);
        void step(double timeUnit);
        friend std::istream &operator>>( std::istream &in, Universe &u);
        void outputUniverse();
};

   

