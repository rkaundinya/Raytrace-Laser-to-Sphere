#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

std::vector<float> normalize(std::vector<float> &toNormalize);

std::vector<float> CalculateSphereToRayOriginVector(const std::vector<float> &sphereCenter, 
    const std::vector<float> &rayOrigin);

bool CheckIfRayOriginatesWithinBalloon(const std::vector<float> &sphereToRayVec, 
    const float &sphereRadius);

float RayPointClosestToSphereCenter(const std::vector<float> &rayOriginToSphereOrigin, 
    const std::vector<float> &rayDirection); 

bool CheckIfIntersectionOccurs(const float &rayPointClosestToSphereCenter);

bool CheckIfLaserHitsBalloon (const std::vector<float> &sphereCenter, 
    const float &sphereRadius, const std::vector<float> &rayOrigin, 
    std::vector<float> &rayDirection);

int main() 
{
    std::vector<float> C {3, 0, 5};
    std::vector<float> L {2, 2, 6 }; 
    std::vector<float> D {1, 2, 4 };
    std::vector<float> O {1.0f, 2.0f, 4.0f};

    if (CheckIfLaserHitsBalloon(C, 3.0f, O, D))
        std::cout << "I hit the balloon" << std::endl; 
    else
        std::cout << "I did not hit the balloon" << std::endl;
}

std::vector<float> normalize(std::vector<float> &toNormalize)
{
    float magnitude; 
    for (float value : toNormalize)
    {
        magnitude += value * value; 
    }

    magnitude = std::sqrt(magnitude);

    for (int i = 0; i < toNormalize.size(); i++)
    {
        toNormalize[i] = toNormalize[i] / magnitude; 
    }

    return toNormalize;
}

std::vector<float> CalculateSphereToRayOriginVector(const std::vector<float> &sphereCenter, 
    const std::vector<float> &rayOrigin)
{
    std::vector<float> sphereToRayVec (sphereCenter.size(), 0.0f);

    std::transform(sphereCenter.begin(), sphereCenter.end(),rayOrigin.begin(), 
        sphereToRayVec.begin(), std::minus<float>()); 

    return sphereToRayVec;     
}

bool CheckIfRayOriginatesWithinBalloon(const std::vector<float> &sphereToRayVec, 
    const float &sphereRadius)
{
    float sphereToRayVecSquared = std::inner_product(std::begin(sphereToRayVec), 
        std::end(sphereToRayVec), std::begin(sphereToRayVec), 0.0f);

    if (sphereToRayVecSquared > sphereRadius)
        return false;
    else
        return true;
}

float RayPointClosestToSphereCenter(const std::vector<float> &rayOriginToSphereOrigin, 
    const std::vector<float> &rayDirection)
{
        return std::inner_product(std::begin(rayOriginToSphereOrigin), 
            std::end(rayOriginToSphereOrigin), std::begin(rayDirection), 0.0f);
}

bool CheckIfIntersectionOccurs(const float &rayPointClosestToSphereCenter)
{
    if (rayPointClosestToSphereCenter > 0)
        return true; 
    else
        return false;
}

bool CheckIfLaserHitsBalloon (const std::vector<float> &sphereCenter, 
    const float &sphereRadius, const std::vector<float> &rayOrigin, 
    std::vector<float> &rayDirection)
{
    std::vector<float> sphereOriginToRayOriginVector = 
        CalculateSphereToRayOriginVector(sphereCenter, rayOrigin);

    normalize(rayDirection);

    if (CheckIfRayOriginatesWithinBalloon(sphereOriginToRayOriginVector, sphereRadius))
        return true; 
    else
    {
        float rayPointClosestToSphere = RayPointClosestToSphereCenter(sphereOriginToRayOriginVector, 
            rayDirection);
        return CheckIfIntersectionOccurs(rayPointClosestToSphere);
    }
}