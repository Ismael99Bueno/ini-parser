#ifndef SAVEABLE_HPP
#define SAVEABLE_HPP

#include "ini/input.hpp"
#include "ini/output.hpp"

namespace ini
{
    class saveable
    {
    public:
        saveable() = default;
        virtual ~saveable() = default;

        virtual void write(output &out) const = 0;
        virtual void read(input &in) = 0;
    };
}

#endif