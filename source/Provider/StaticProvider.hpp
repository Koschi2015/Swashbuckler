#pragma once

#ifndef STATICPROVIDER_HPP
#define STATICPROVIDER_HPP

#include "Provider.hpp"

class StaticProvider : public Provider
{
private:
    float m_value;

public:
    StaticProvider(const float value) :
        m_value(value)
    { }

    virtual float getValue() override
    {
        return m_value;
    }

    virtual std::unique_ptr<Provider> clone() const override
    {
        return std::unique_ptr<StaticProvider>(new StaticProvider(m_value));
    }

    virtual void update(float elapsedTime) override
    { }
};

#endif
