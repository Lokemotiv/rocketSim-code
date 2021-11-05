#ifndef rocketSimObj_hpp
#define rocketSimObj_hpp

#include "planetSimObj.hpp"

void asignelistOfPlanetsRocket(std::list<planet> listOfAllPlanets, std::list<fixedPlanet> listOfAllFixedPlanets){
    planetList.assign(listOfAllPlanets.begin(), listOfAllPlanets.end());
    fixedPlanetList.assign(listOfAllFixedPlanets.begin(), listOfAllFixedPlanets.end());
}

struct rocketDefine
{
    long double mass, drymass, fuleUsePerMiliSecond, exitVelosityOfPropelent, EGToCG; 
    vectot3d CGpos, CPpos, EGpos;
};

class rocketStage : collider
{
public:
    rocketDefine rocket;
    vector3d vel, gravity, drag, pos;
    rocketStage(long double wetMass, long double dryMass, vector3d Velosity, vector3d posision, long double fuleUsePerMiliSecond, long double exitVelosityOfPropelent, vector3d engineGimblePoint, vector3d centeOfGravityPoint, vector3d centerOfPresurePoint) : collider(sphereCollliderNum, sphereColliderDefinedList, boxColliderNum, boxColliderDefinedList, sylinderColliderNum, sylinderColliderDefinedList){
        rocket.mass = wetMass;
        rocket.dryMass = dryMass,
        rocket.fuleUsePerMiliSecond = fuleUsePerMiliSecond;
        rocket.exitVelosityOfPropelent = exitVelosityOfPropelent;
        rocket.EGToCG = sqrt(absVal(modPow(engineGimblePoint.x - centeOfGravityPoint.x, 2)) + absVal(pow(engineGimblePoint.y - centeOfGravityPoint.y, 2)) + absVal(pow(engineGimblePoint.z - centeOfGravityPoint.z, 2)))
        rocket.CGpos = centeOfGravityPoint;
        rocket.CPpos = centerOfPresurePoint;
        rocket.EGpos = engineGimblePoint;

        rocketStage::vel = Velosity;
        rocketStage::pos = posision;

    }

    update(){
        collider::pos = pos;
    }

    void startupRocket(bool planetTypeFlaseIsPlanetTrueIsFixedPlanet, int startPlanetID){
        if (planetTypeFlaseIsPlanetTrueIsFixedPlanet){
            for (std::list<fixedPlanet>::iterator it = fixedPlanetList.begin(); it != fixedPlanetList.end(); it++){
                if(startPlanetID == it->ID){
                vel = generateRocketStartVelFixedPlanet();
                pos = gnenerateRocketStartPosPlanet();
                return;
                }
            }
        }
        else{
            for (std::list<planet>::iterator it = planetList.begin(); it != planetList.end(); it++){
                if(startPlanetID == it->ID){
                vel = generateRocketStartVelFixedPlanet();
                pos = gnenerateRocketStartPosPlanet();
                return;
                }
            }
        }
    }
    void generateGravityRocket(){
        for (std::list<planet>::iterator it = planetList.begin(); it != planetList.end(); it++){
        long double latitude = findLatitude(pos, it->pos), longitude = findLongitude(pos, it->pos);
        long double distanse = generateDistanse(pos, it->pos);

        gravity += plussEqualVector3d(gravity,generateGravity(latitude, longitude, mass, it->mass, distanse))
        }

        for (std::list<fixedPlanet>::iterator it = fixedPlanetList.begin(); it != fixedPlanet.end(); it++){
        long double latitude = findLatitude(pos, it->pos), longitude = findLongitude(pos, it->pos);
        long double distanse = generateDistanse(pos, it->pos);

        gravity += plussEqualVector3d(gravity,generateGravity(latitude, longitude, mass, it->mass, distanse))
        }
    }

    rocketUpdate(int startTime, int i){
        if (startTime <= i){

        }
    }
    update(std::list<()){
        planetColliders = planetColliders
    }
};

#endif