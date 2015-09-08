#pragma once

#ifndef STATICPROVIDER_HPP
#define STATICPROVIDER_HPP

#include "Provider.hpp"

class StaticProvider : public Provider
{
private:
    float m_value;

public:
    StaticProvider(const float value) : m_value(value)
    { }

    virtual float getValue() override
    {
        return m_value;
    }
};

#endif
