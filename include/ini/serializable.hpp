#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include "ini/deserializer.hpp"
#include "ini/serializer.hpp"

namespace ini
{
    class serializable
    {
    public:
        serializable() = default;
        virtual ~serializable() = default;

        virtual void serialize(serializer &out) const = 0;
        virtual void deserialize(deserializer &in) = 0;
    };
}

#endif