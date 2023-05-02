#ifndef DESERIALIZER_HPP
#define DESERIALIZER_HPP

#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "ini/section_builder.hpp"
#include "debug/debug.hpp"

namespace ini
{
    class deserializer : public ini::section_builder
    {
    public:
        deserializer(const char *filepath);
        ~deserializer();

        const std::string &readstr(const std::string &key) const;
        float readf32(const std::string &key) const;
        double readf64(const std::string &key) const;
        long double readf128(const std::string &key) const;

        std::int16_t readi16(const std::string &key) const;
        std::int32_t readi32(const std::string &key) const;
        std::int64_t readi64(const std::string &key) const;

        std::uint32_t readui32(const std::string &key) const;
        std::uint64_t readui64(const std::string &key) const;

        void close();
        bool contains_key(const std::string &key) const;
        bool contains_section(const std::string &section) const;
        bool contains_section() const;
        bool is_open() const;

    private:
        enum parse_state
        {
            READY,
            COMMENT,
            SECTION,
            KEY,
            VALUE,
        };

        std::ifstream m_stream;
        std::unordered_set<std::string> m_parsed_sections;
        std::unordered_map<std::string, std::string> m_kv_pairs;

        void parse_ini();
    };
}

#endif