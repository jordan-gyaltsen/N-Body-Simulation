#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include "CelestialBody.hpp"

Body::Body(){}
Body::Body(double UniverseRadius, double x, double y, double xVelocity, double yVelocity, double BodyMass,std::string fileName){
    this->UniRad = UniverseRadius;
    this->xPos = x;
    this->yPos = y;
    this->xVel = xVelocity;
    this->yVel = yVelocity;
    this->mass = BodyMass;
    this->file = fileName;
    //Window is 500x500. sfml origin is at (250,250)
    double sfmlRadius = 250;
    /*x or y *(sfmlRadius/UniRad) converts to proportional x or y coordinate based on our 
    /sfml window radius. Window origin is set to (window radius, window radius)
    For x add this value to window origin. For y add subtract this value from window origin.*/
    double sfmlX = ((x*sfmlRadius)/UniRad) + sfmlRadius;
    double sfmlY = sfmlRadius - ((y*sfmlRadius)/UniRad);
    m_texture.loadFromFile(file);
	m_sprite.setTexture(m_texture);
    m_sprite.setPosition(sfmlX,sfmlY);
}

//only to be used by step function
void Body::spriteSet(){
    double sfmlRadius = 250;
    double sfmlX = ((xPos*sfmlRadius)/UniRad) + sfmlRadius;
    double sfmlY = sfmlRadius - ((yPos*sfmlRadius)/UniRad);
    m_texture.loadFromFile(file);
	m_sprite.setTexture(m_texture);
    m_sprite.setPosition(sfmlX,sfmlY);
    //std::cout << file << "'s position is (" << sfmlX << "," << sfmlY << ")" << std::endl;
}

void Body::setRad(double radius){
    UniRad = radius;
}
void Body::setForces(double xForce, double yForce){
    fx = xForce; 
    fy = yForce;
}

double Body::getMass(){
    return(mass);
}
double Body::getXPos(){
    return(xPos);
}
double Body::getYPos(){
    return(yPos);
}
std::string Body::getName(){
    return(file);
}
void Body::printForces(){
    std::cout << "(" << fx << "," << fy << ")" << std::endl;
}


double Body::xForceCalc(Body* planet){
    double G = -(6.67*pow(10,-11));
    double distX = (xPos - planet->getXPos()); //ΔX = x1 - x2
    double distY = (yPos - planet->getYPos()); //Δy = y1 - y2
    double r = sqrt((pow(distX,2) + pow(distY,2))); //R = sqrt(ΔX^2 + ΔY^2)
    double f = G*mass*planet->getMass()/(pow(r,2)); //F = G(m1)(m2)/(r^2)
    double xForce = f*distX/r;  //Fx = F(ΔX/r)
    //std::cout << "in xForceCalc function, " << file << "'s X Force is (" << xForce << ")" << std::endl;
    return xForce;  
}

double Body::yForceCalc(Body* planet){
    double G = -(6.67*pow(10,-11));
    double distX = (xPos - planet->getXPos()); //Δx = x1 - x2
    double distY = (yPos - planet->getYPos()); //Δy = y1 - y2
    double r = sqrt((pow(distX,2) + pow(distY,2))); //R = sqrt(ΔX^2 + ΔY^2)
    double f = G*mass*planet->getMass()/(pow(r,2)); //F = G(m1)(m2)/(r^2)
    double yForce = f*distY/r;  //Fy = F(ΔY/r)
    //std::cout << "in yForceCalc function, " << file << "'s Y Force is (" << yForce << ")" << std::endl;
    return yForce;  
}

void Body::accelCalc(){
    ax = fx/mass;   //Ax = Fx/M
    ay = fy/mass;   //Ay = Fy/M
    //std::cout << file << "'s Forces are (" << fx << "," << fy << ")" << std::endl;
    //std::cout << file << "'s Accelerations are (" << ax << "," << ay << ")" << std::endl;
}
void Body::velCalc(double deltaT){
    xVel += deltaT*ax;    //xVel + (Δt*ax)
    yVel += deltaT*ay;    //yVel + (Δt*ay)
    //std::cout << file << "'s Velocities are (" << xVel << "," << yVel << ")" << std::endl;
}
void Body::calcPosition(double deltaT){
    xPos += deltaT*xVel; //px += Δt*xVel
    yPos += deltaT*yVel;//py += Δt*yVel
    //std::cout << file << "'s position is (" << xPos << "," << yPos << ")" << std::endl;
}

std::istream &operator>>( std::istream &in, Body &b){
    in >> b.xPos;  
    in >> b.yPos;
    in >> b.xVel;
    in >> b.yVel;
    in >> b.mass;
    in >> b.file;
    b.fx = 0;
    b.fy = 0;
    b.ax = 0;
    b.ay = 0;
    b.spriteSet();
    return in;
}

void Body::outputBody(){
    std::cout << xPos << "  ";  
    std::cout << yPos << "  "; 
    std::cout << xVel << "  "; 
    std::cout << yVel << "  "; 
    std::cout << mass << "  "; 
    std::cout << file << "  " << std::endl;
}