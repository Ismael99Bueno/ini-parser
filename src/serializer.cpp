#include "ini/pch.hpp"
#include "ini/serializer.hpp"

namespace ini
{
    serializer::serializer(const char *filepath) : m_stream(filepath)
    {
        DBG_ASSERT(m_stream.is_open(), "Failed to open file at %s\n", filepath)
        m_current_section.reserve(256);
    }

    serializer::~serializer() { close(); }

    void serializer::begin_section(const std::string &section)
    {
        section_builder::begin_section(section);
        static bool first_time = true;
        if (first_time)
        {
            m_stream << "[" << m_current_section << "]\n";
            first_time = false;
        }
        else
            m_stream << "\n[" << m_current_section << "]\n";
        m_reiterate_last_section = false;
    }

    void serializer::end_section()
    {
        section_builder::end_section();
        m_reiterate_last_section = !m_current_section.empty();
    }

    void serializer::close()
    {
        DBG_ASSERT(m_current_section.empty(), "A section is still open!")
        m_stream.close();
    }
}