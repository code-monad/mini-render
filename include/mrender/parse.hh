#ifndef __MRENDER_PARSE_HH__
#define __MRENDER_PARSE_HH__

#include <string>
#include <unordered_map>

namespace mrender {
    class parse { // command line argument parser
    public:
        parse(int argc, char** argv);
        const std::string& get_endpoint() const noexcept { return _endpoint; }
        const std::string& get_template_base_path() const noexcept { return _template_base_path; };
        const std::string& get_template_name() const noexcept { return _template_name; };
        const unsigned get_retry_time() const noexcept { return _retry_time; }
        const std::string& help() const noexcept { return _help;}
        std::unordered_map<std::string, std::string>& get_formats() noexcept { return _formats; }
    private:
        unsigned _retry_time;
        std::string _endpoint;
        std::string _template_base_path;
        std::string _template_name;
        std::string _help;
        std::unordered_map<std::string, std::string> _formats;
    };
}

#endif
