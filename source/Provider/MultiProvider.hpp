#ifndef MULTIPROVIDER_HPP
#define MULTIPROVIDER_HPP

#include "Provider.hpp"

#include <memory>
#include <vector>

class MultiProvider : public Provider
{
private:

    std::vector<std::unique_ptr<Provider>> m_providers;

public:

    MultiProvider(std::vector<std::unique_ptr<ValueProvider>> providers) :
        m_providers(std::move(providers))
    {
       for(auto it = begin(m_providers); it != end(m_providers); ++it)
           if((*it) == nullptr)
                throw std::runtime_error("One of the provider is null.");
    }

    virtual float getValue() = 0;

    virtual void reset() override
    {
        for(auto it = begin(m_providers); it != end(m_providers); ++it)
            (*it)->reset();
    }

protected:

    const std::vector<std::unique_ptr<ValueProvider>>& getProvider() const
    {
        return m_providers;
    }
};

#endif
