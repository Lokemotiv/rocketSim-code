#include "rocketsimObj.hpp"

std::list<rocketStage> rocketStageList;
std::list<planet> planetList;
std::list<fixedPlanet> fixedPlanetList;
int runID = 0;

void startup(bool planetTypeFlaseIsPlanetTrueIsFixedPlanet, int startPlanetID)
{
    asigneListsFixedPlanet(fixedPlanetList);
    asigneListsPlanet(planetList);
    asigneListsRocket(rocketStageList);
    for (std::list<rocketStage>::iterator it = rocketStageList.begin(); it != rocketStageList.end(); it++)
    {
        if (it->active == true)
            it->startupRocket(planetTypeFlaseIsPlanetTrueIsFixedPlanet, startPlanetID);
    }
    databaseWriteFile* startupFile = new databaseWriteFile("InfoRun:" + toS(runID));
    startupFile->
}

void end(){
    for(std::list<rocketStage>::iterator it = rocketStageList.begin(); it != rocketStageList.end(); it++) it->closeFile();
    for(std::list<fixedPlanet>::iterator it = fixedPlanetList.begin(); it != fixedPlanetList.end(); it++) it->closeFile();
    for(std::list<planet>::iterator it = planetList.begin(); it != planetList.end(); it++) it->closeFile();
}

void rocketInstructions(){
    
}

void Update()
{
    for (std::list<planet>::iterator it = planetList.begin(); it != planetList.end(); it++)
    {
        it->gravity = {0, 0, 0};
        it->gravity = it->generateGravityPlanet();
    }
    for (std::list<rocketStage>::iterator it = rocketStageList.begin(); it != rocketStageList.end(); it++)
    {
        if (it->active == true)
        {
            it->gravity = {0, 0, 0};
            it->drag = {0, 0, 0};
            it->generateGravityRocket();
            //it->generateDragRocket();
        }
    }
    for (std::list<planet>::iterator it = planetList.begin(); it != planetList.end(); it++)
    {
        rocketInstructions();
        it->checkColisionPlanet();
        it->vel.x += generateVelosity(it->mass, it->gravity.x);
        it->vel.x += generateVelosity(it->mass, it->gravity.y);
        it->vel.x += generateVelosity(it->mass, it->gravity.z);
        plussEqualVector3d(it->pos, it->vel);
        it->update();
    }
    for (std::list<fixedPlanet>::iterator it = fixedPlanetList.begin(); it != fixedPlanetList.end(); it++)
    {
        it->checkColisionFixedPlanet();
        it->update();
    }
    for (std::list<rocketStage>::iterator it = rocketStageList.begin(); it != rocketStageList.end(); it++)
    {
        it->update();
    }
}

int main()
{
    std::cout << std::fixed;

    runID = 0;

    long double
        wetMass = 1,
        dryMass = 0,
        fuleUsePerMiliSecond = 0.1,
        exitVelosityOfPropelent = 3000;

    vector3d
        pos = {0, 0, 0},
        vel = {0, 0, 0},
        engineGimblePoint = {0, 0, 0},
        centeOfGravityPoint = {0, 0, 0},
        centerOfPresurePoint = {0, 0, 0};

    rocketStage stage1(3, wetMass, dryMass, vel, pos, fuleUsePerMiliSecond, exitVelosityOfPropelent, 0, engineGimblePoint, centeOfGravityPoint, centerOfPresurePoint);

    planet planet1(1, 1E+14, 1, {0, 0, 0}, {0, 0, 0});
    planet planet2(1, 1000, 1, {100, 0, 0}, {0, sqrt((G * 1E+14) / 100), 0});

    rocketStageList = {stage1};
    planetList = {planet1, planet2};
    fixedPlanetList = {};
    
    int startPlanetID = ;
    bool planetTypeFlaseIsPlanetTrueIsFixedPlanet
    startup(planetTypeFlaseIsPlanetTrueIsFixedPlanet, startPlanetID);

    while (true)
    {
        update();
        i++;
    }
    end();

    return 0;
}