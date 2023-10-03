#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Universe.hpp"
#include "CelestialBody.hpp"

int main(int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(500, 500), "ps2a");
    Universe uni;
    std::cin >> uni;
    double time, deltaT;
    sscanf(argv[1],"%lf",&time);
    sscanf(argv[2],"%lf",&deltaT);
    bool loopDone = false;
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
        //after every event, window is cleared and everything is redrawn and displayed. 
        //now make a for loop for passage of time on each body then drawing?
            if(!loopDone){
                for(double i = 0.0; i < time; i += deltaT){
                    std::cout << "Time elapsed is " << i << std::endl; 
                    uni.step(deltaT);
                    window.clear();
                    uni.drawBodies(window);
                    window.display();
                }
                loopDone = true;
                uni.outputUniverse();
            }
            window.display();
        }
    }
    return 0;
}