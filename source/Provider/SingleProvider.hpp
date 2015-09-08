#ifndef SINGLEPROVIDER_HPP
#define SINGLEPROVIDER_HPP

#include "Provider.hpp"
#include <memory>

class SingleProvider : public Provider
{
private:
    std::unique_ptr<Provider> m_provider;

protected:
    Provider* getProvider() const
    {
        return m_provider.get();
    }

public:
    SingleProvider(std::unique_ptr<Provider> provider) :
        m_provider(std::move(provider))
    {
        if(m_provider == nullptr)
            throw std::runtime_error("SingleProvider is null.");
    }

    float float getValue() = 0;
};

#endif