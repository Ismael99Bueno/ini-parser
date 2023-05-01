#include "ini/pch.hpp"
#include "ini/input.hpp"

namespace ini
{
    input::input(const char *filepath) : m_stream(filepath)
    {
        DBG_LOG_IF(!m_stream.is_open(), "Failed to open file at %s\n", filepath)
        if (!m_stream.is_open())
            return;
        parse_ini();
        DBG_LOG("Successfully parsed '%s' session, with %zu sections and %zu total keys.\n", filepath, m_parsed_sections.size(), m_kv_pairs.size())
    }

    input::~input() { close(); }

    const std::string &input::readstr(const std::string &key) const
    {
        DBG_ASSERT(!m_current_section.empty(), "A section must be started before reading!\n")
        const std::string sec_key = build_key(key);
        DBG_ASSERT(m_kv_pairs.find(sec_key) != m_kv_pairs.end(), "Key '%s' not found in section '%s'!\n", key.c_str(), m_current_section.c_str())
        return m_kv_pairs.at(sec_key);
    }

    float input::readf32(const std::string &key) const
    {
        try
        {
            return std::stof(readstr(key));
        }
        catch (const std::out_of_range &e)
        {
            return (float)std::stod(readstr(key));
        }
    }
    double input::readf64(const std::string &key) const { return std::stod(readstr(key)); }
    long double input::readf128(const std::string &key) const { return std::stold(readstr(key)); }

    std::int16_t input::readi16(const std::string &key) const { return (std::int16_t)std::stoi(readstr(key)); }
    std::int32_t input::readi32(const std::string &key) const { return (std::int32_t)std::stol(readstr(key)); }
    std::int64_t input::readi64(const std::string &key) const { return std::stoll(readstr(key)); }

    std::uint32_t input::readui32(const std::string &key) const { return (std::uint32_t)std::stoul(readstr(key)); }
    std::uint64_t input::readui64(const std::string &key) const { return std::stoull(readstr(key)); }

    void input::close()
    {
        DBG_ASSERT(m_current_section.empty(), "A section is still open: '%s'\n", m_current_section.c_str())
        m_stream.close();
    }

    bool input::contains_key(const std::string &key) const { return m_kv_pairs.find(build_key(key)) != m_kv_pairs.end(); }
    bool input::contains_section(const std::string &section) const { return m_parsed_sections.find(section) != m_parsed_sections.end(); }
    bool input::contains_section() const { return contains_section(m_current_section); }
    bool input::is_open() const { return m_stream.is_open(); }

    void input::parse_ini()
    {
        parse_state state = READY;
        std::string section, key, value;
        section.reserve(256);
        key.reserve(256);
        value.reserve(256);

        while (m_stream)
        {
            const char c = (char)m_stream.get();
            if (c == '\r')
                continue;
            switch (state)
            {
            case READY:
                if (c == '[')
                {
                    section.clear();
                    state = SECTION;
                }
                else if (c == ';')
                    state = COMMENT;
                else if (c != ' ' && c != '\t' && c != '\n')
                {
                    key += c;
                    state = KEY;
                }
                break;

            case COMMENT:
                if (c == '\n')
                    state = READY;
                break;

            case SECTION:
                if (c == '\n')
                {
                    m_parsed_sections.insert(section);
                    state = KEY;
                    break;
                }
                if (c != ']')
                    section += c;
                break;

            case KEY:
                if (c == '\n')
                {
                    state = READY;
                    break;
                }
                if (c == '=')
                {
                    state = VALUE;
                    break;
                }
                if (c != ' ' && c != '\t')
                    key += c;
                break;

            case VALUE:
                if (c == '\n')
                {
                    state = READY;
                    m_kv_pairs[build_key(section, key)] = value;
                    key.clear();
                    value.clear();
                    break;
                }
                if (c != ' ' && c != '\t')
                    value += c;
                break;
            }
        }
    }
}