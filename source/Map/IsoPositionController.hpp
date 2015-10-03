#ifndef ISOPOSITIONCONTROLLER_HPP
#define ISOPOSITIONCONTROLLER_HPP

#include <SFML/System/Vector2.hpp>

template<typename T>
class IsoPositionController
{
private:
    sf::Vector2i m_gridPosition;
    sf::Vector2<T> m_gridSize;
    sf::Vector2<T> m_screenPosition;

    void calculateScreenPosition()
    {
        m_screenPosition.x = static_cast<T>(m_gridPosition.x * m_gridSize.x / 2 - m_gridPosition.y * m_gridSize.x / 2);
        m_screenPosition.y = static_cast<T>(m_gridPosition.y * m_gridSize.y / 2 + m_gridPosition.x * m_gridSize.y / 2);
    }

public:
    IsoPositionController(const sf::Vector2i& gridPosition,
                          const sf::Vector2<T>& gridSize) :
        m_gridPosition(gridPosition),
        m_gridSize(gridSize)
    {
        calculateScreenPosition();
    }

    /*bool operator<(const IsoPositionController& rhs);
    bool operator<=(const IsoPositionController& rhs);
    bool operator>(const IsoPositionController& rhs);
    bool operator>=(const IsoPositionController& rhs);

    void rotateClockWise(const sf::Vector2i& pivot);
    void rotateCounterClockWise(const sf::Vector2i& pivot);*/

    const sf::Vector2<T> getScreenPosition() const
    {
        return m_screenPosition;
    }

    const sf::Vector2i getGridPosition() const
    {
        return m_gridPosition;
    }

    void setGridPosition(const sf::Vector2i& gridPosition)
    {
        m_gridPosition = gridPosition;
        calculateScreenPosition();
    }
};

typedef IsoPositionController<float> IsoPositionController2f;
typedef IsoPositionController<int> IsoPositionController2i;

#endif