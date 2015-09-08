#ifndef PROVIDER_HPP
#define PROVIDER_HPP

// Base class for all other Provider
class Provider
{
public:
    virtual ~Provider()
    { }

    virtual float getValue() = 0;
};

#endif