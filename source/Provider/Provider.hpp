#ifndef PROVIDER_HPP
#define PROVIDER_HPP

// Base class for all other Provider
class Provider
{
public:
    virtual ~Provider()
    { }

    virtual float getValue() = 0;

    virtual std::unique_ptr<Provider> clone() const = 0;

    virtual void update(float elapsedTime) = 0;
};

#endif