#include "IsoPositionController.hpp"

IsoPositionController::IsoPositionController(int x, int y) :
    Vector2<int>(x, y)
{ }

bool IsoPositionController::operator<(const IsoPositionController& rhs)
{
    if(x < rhs.x)
        return true;

    if(x == rhs.x && y < rhs.y)
        return true;

    return false;
}

bool IsoPositionController::operator<=(const IsoPositionController& rhs)
{
    if(x < rhs.x)
        return true;

    if(x == rhs.x && y <= rhs.y)
        return true;

    return false;
}

bool IsoPositionController::operator>(const IsoPositionController& rhs)
{
    if(x > rhs.x)
        return true;

    if(x == rhs.x && y > rhs.y)
        return true;

    return false;
}

bool IsoPositionController::operator>=(const IsoPositionController& rhs)
{
    if(x > rhs.x)
        return true;

    if(x == rhs.x && y >= rhs.y)
        return true;

    return false;
}

void IsoPositionController::rotateClockWise(const sf::Vector2i& pivot)
{
    // X' = x*cos(phi) + y*sin(phi)
    // Y' = -x*sin(phi) + y*cos(phi)
    // cos(90) = 0 / sin(90) = 1
    // X' = x*0 + y*1
    // Y' = -x*1 + y*0

    sf::Vector2i localPosition;
    localPosition.x = x - pivot.x;
    localPosition.y = y - pivot.y;

    int temp = localPosition.x;
    localPosition.x = localPosition.y;
    localPosition.y = - temp;

    y = localPosition.x + pivot.x;
    x = localPosition.y + pivot.y;
}

void IsoPositionController::rotateCounterClockWise(const sf::Vector2i& pivot)
{
    // X' = x*cos(phi) + y*sin(phi)
    // Y' = -x*sin(phi) + y*cos(phi)
    // cos(-90) = 0 / sin(-90) = -1
    // X' = x*0 + y*-1
    // Y' = -x*-1 + y*0

    sf::Vector2i localPosition;
    localPosition.x = x - pivot.x;
    localPosition.y = y - pivot.y;

    int temp = localPosition.x;
    localPosition.x = -localPosition.y;
    localPosition.y = temp;

    y = localPosition.x + pivot.x;
    x = localPosition.y + pivot.y;
}