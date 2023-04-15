#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <fstream>
#include <iomanip>
#include <limits>
#include "section_builder.hpp"
#include "debug.hpp"

namespace ini
{
    class output : public section_builder
    {
    public:
        output(const char *filepath);
        ~output();

        void begin_section(const std::string &section) override;

        template <typename T>
        void write(const std::string &key, const T &value)
        {
            DBG_ASSERT(!m_current_section.empty(), "A section must be started to begin writing!\n")
            if (m_reiterate_last_section)
            {
                m_stream << "\n[" << m_current_section << "]\n";
                m_reiterate_last_section = false;
            }
            m_stream << key << "=" << std::setprecision(std::numeric_limits<T>::max_digits10) << value << "\n";
        }

        void end_section() override;
        void close();

    private:
        std::ofstream m_stream;
        bool m_reiterate_last_section = false;
    };
}

#endif