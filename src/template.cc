#include <mrender/template.hh>
#include <regex>


void mrender::detail::string_format(std::string& raw, const std::string& arg, const std::string& val) {
    std::regex re("%"+arg+"%");
    raw = std::regex_replace(raw, re, val);
}

void mrender::detail::string_format(std::string& raw, const std::unordered_map<std::string, std::string>& format_args) {
    for(auto& [arg, val]: format_args) {
        mrender::detail::string_format(raw, arg, val);
    }
}
