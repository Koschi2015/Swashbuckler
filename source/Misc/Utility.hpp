#pragma once

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <sstream>
#include <string>

namespace utility
{
    template<typename T>
    std::string toString(const T& value)
    {
        std::ostringstream out;

        out << value;

        return out.str();
    }

    template<typename T>
    T stringTo(const std::string& str)
    {
        std::stringstream stringstream(str);

        T value;
        stringstream >> value;
        return value;
    }

    template<>
    std::string stringTo(const std::string& str);
} // namespace utility

#endif // UTILITY_HPP
