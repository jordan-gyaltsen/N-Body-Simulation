#include "Universe.hpp"

Universe::Universe(){}

void Universe::drawBodies(sf::RenderWindow &win){
    for(int i = 0; i < bodyCount; i++){
        win.draw(*bodyList[i]);
    }
}
/*  step function notes.
    1) loop through the universe's celestial body list. CB denotes a body from this primary loop.
        1.1) for each CB, iterate through body list except skip the same celestial body that CB is.
        1.2) calculate and sum the x and y forces all other bodies exert on CB.
        1.3) Set CB's x and y forces. 
    2) Loop through universe's celestial body list.
        2.1) for each body calculate acceleration in the x and y direction
        2.2) for each body calculate velocity in the x and y direction
        2.3) for each body calculate position (x,y)
        2.4) spriteSet converts the position to sfml coordinates and updates sprite with them.

*/
void Universe::step(double deltaT){
        //for(each planet A)
        for(unsigned i = 0; i < bodyList.size(); i++){
            //for(all other planets, B)
            double xForce = 0;
            double yForce = 0;
            for(unsigned j = 0; j < bodyList.size(); j++){
                if(j != i){
                    //Calculates planet I's acceleration from the the force planet J exerts on it.
                    xForce += bodyList[i]->xForceCalc(bodyList[j]);
                    yForce += bodyList[i]->yForceCalc(bodyList[j]);
                }
            }
            //now have sum of all forces acting on planet I. Set Planet I's force
            bodyList[i]->setForces(xForce,yForce); 
        }

        for (unsigned i = 0; i < bodyList.size(); i++){
            bodyList[i]->accelCalc();
            bodyList[i]->velCalc(deltaT); //calculate new velocity from acceleration.
            bodyList[i]->calcPosition(deltaT); //calculate new position at next time position using current velocity calculated
            bodyList[i]->spriteSet();
        }
}

std::istream &operator>>( std::istream &in, Universe &u){
    //read and store first int as number of bodies and second int as radius of universe.
    std::cin >> u.bodyCount;
    std::cin >> u.universeRadius;
    //loop "bodyCount" number of times, instantiating celestial body pointer and adding it at end of universe's 
    //vector of celestial body pointers.
    for(int i = 0; i < u.bodyCount; i++){
        Body* cb = new Body();
        cb->setRad(u.universeRadius);
        std::cin >> *cb;
        u.bodyList.push_back(cb);
    } 
    return in;
}

void Universe::outputUniverse(){
    std::cout << bodyCount << std::endl;
    std::cout << universeRadius << std::endl;
    for(int i = 0; i < bodyCount; i++){
        bodyList[i]->outputBody();
    } 
}