#ifndef ISOPOSITIONCONTROLLER_HPP
#define ISOPOSITIONCONTROLLER_HPP

#include <SFML/System/Vector2.hpp>

class IsoPositionController : public sf::Vector2i
{
private:
public:
    IsoPositionController(int x = 0, int y = 0);
    bool operator<(const IsoPositionController& rhs);
    bool operator<=(const IsoPositionController& rhs);
    bool operator>(const IsoPositionController& rhs);
    bool operator>=(const IsoPositionController& rhs);

    void rotateClockWise(const sf::Vector2i& pivot);
    void rotateCounterClockWise(const sf::Vector2i& pivot);
};

#endif