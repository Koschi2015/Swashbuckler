#ifndef ANIMATIONPROVIDER_HPP
#define ANIMATIONPROVIDER_HPP

#include "Provider.hpp"

class AnimationProvider : public Provider
{
private:
    unsigned int m_firstIndex;
    unsigned int m_lastIndex;
    float m_currentIndex;
    float m_frameTime;
    float m_nextFrameTime;
public:
    AnimationProvider(const unsigned int firstIndex,
                      const unsigned int lastIndex,
                      float frameTime) :
        m_firstIndex(firstIndex),
        m_lastIndex(lastIndex),
        m_frameTime(frameTime),
        m_nextFrameTime(0)
    {
        m_currentIndex = static_cast<float>(m_firstIndex);
    }

    virtual float getValue() override
    {
        return m_currentIndex;
    }

    virtual std::unique_ptr<Provider> clone() const override
    {
        return std::unique_ptr<AnimationProvider>(new AnimationProvider(m_firstIndex, m_lastIndex, m_frameTime));
    }

    virtual void update(float elapsedTime) override
    {
        if(m_nextFrameTime < elapsedTime)
        {
            m_currentIndex += 1.f;
            m_nextFrameTime += m_frameTime;

            if(m_currentIndex > m_lastIndex)
                m_currentIndex = static_cast<float>(m_firstIndex);
        }        
    }
};

#endif