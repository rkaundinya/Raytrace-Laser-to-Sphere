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
    // Sample values - should return I hit balloon
    std::vector<float> sphereCenter {3, 0, 5};
    std::vector<float> rayDirection {1, 2, 4 };
    std::vector<float> rayOrigin {1, 2, 4};
    float sphereRadius = 3;

    if (CheckIfLaserHitsBalloon(sphereCenter, sphereRadius, rayOrigin, rayDirection))
        std::cout << "I hit the balloon" << std::endl; 
    else
        std::cout << "I did not hit the balloon" << std::endl;
}

// Function to normalize a vector

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

// Function calculates the vector between a point of origin along the laser's path
// and the center of the sphere. It returns this vector. 
// @sphereCenter is the center of the sphere
// @rayOrigin is the point along the laser's path being compared to

std::vector<float> CalculateSphereToRayOriginVector(const std::vector<float> &sphereCenter, 
    const std::vector<float> &rayOrigin)
{
    std::vector<float> sphereToRayVec (sphereCenter.size(), 0.0f);

    std::transform(sphereCenter.begin(), sphereCenter.end(),rayOrigin.begin(), 
        sphereToRayVec.begin(), std::minus<float>()); 

    return sphereToRayVec;     
}

// This function checks if the ray has somehow been fired from within a balloon
// If this is true, then returns true
// @sphereToRayVec is the vector between the sphere center and the ray point
// @sphereRadius is the radius of the sphere

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

// This function finds the point along the rays path closest to the sphere's center
// @rayOriginToSphereOrigin is the vector between the sphere center and a point 
// along the rays path
// @rayDirection is the direction vector of the ray

float RayPointClosestToSphereCenter(const std::vector<float> &rayOriginToSphereOrigin, 
    const std::vector<float> &rayDirection)
{
        return std::inner_product(std::begin(rayOriginToSphereOrigin), 
            std::end(rayOriginToSphereOrigin), std::begin(rayDirection), 0.0f);
}

// This function checks if an intersection occurs between the ray and the sphere
// If the rayPointClosest to sphere value is below 0, the ray is traveling 
// away from the sphere and thus does not intersect
// @rayPointClosestToSphereCenter is the length between a point along the ray path
// and the point along the path closest to the sphere's center

bool CheckIfIntersectionOccurs(const float &rayPointClosestToSphereCenter)
{
    if (rayPointClosestToSphereCenter > 0)
        return true; 
    else
        return false;
}

// This function checks if the laser hits the balloon by pooling all 
// functions outlined above in the correct algorithmic order
// Returns true if the ray and sphere intersect

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