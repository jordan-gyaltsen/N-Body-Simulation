#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Body : public sf::Drawable {

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    double UniRad,xPos,yPos,xVel,yVel,mass;
    double fx,fy,ax,ay;
    std::string file;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {   
        target.draw(m_sprite);
    }

public:
    Body();
	Body(double UniverseRadius,double x, double y, double xVelocity, double yVelocity, double BodyMass,std::string fileName);
    
    void spriteSet(); //only to be used for step;
    void setRad(double radius);
    void setForces(double xForce, double yForce);

    double getMass();
    double getXPos();
    double getYPos();
    void printForces();
    std::string getName();

    double forceCalc(Body* planet);
    double xForceCalc(Body* planet);
    double yForceCalc(Body* planet);
    void accelCalc();
    void velCalc(double deltaT);
    void calcPosition(double deltaT);
    void outputBody();
   
    friend std::istream &operator>>( std::istream &in, Body &b);
};