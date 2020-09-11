#ifndef __MRENDER_TEMPLATE_HH__
#define __MRENDER_TEMPLATE_HH__


#include <nlohmann/json.hpp>


namespace mrender {
    namespace detail{
        void string_format(std::string& raw, const std::string& arg, const std::string& val);
        void string_format(std::string& raw, const std::unordered_map<std::string, std::string>& format_args);
    }

    using json = nlohmann::json;
    
    template<typename ContentType = std::string>
    struct BasicTemplate {
        typedef ContentType content_type;
        content_type _content;
        BasicTemplate(const content_type& content = {}): _content{content} {}
        virtual inline BasicTemplate& format(const std::unordered_map<std::string, std::string>& format_args) = 0;
        virtual inline const std::string content() { return {}; }
    };

    template<typename ContentType = std::string>
    struct Template: public BasicTemplate<ContentType> {
        Template(const ContentType& content): BasicTemplate<ContentType>(content) {}
        inline const std::string content();
        inline Template& format(const std::unordered_map<std::string, std::string>& format_args);
    };

    template<> inline const std::string Template<std::string>::content() { return _content;}

    template<> inline Template<std::string>& Template<std::string>::format(const std::unordered_map<std::string, std::string>& format_args) {
        for(auto& [arg, val]: format_args) {
            detail::string_format(_content, arg, val);
        }
        return *this;
    }
    
    using JsonTemplate = Template<nlohmann::json>;
    
    template<> inline const std::string JsonTemplate::content() {
        return _content.dump();
    }

    template<> inline JsonTemplate& JsonTemplate::format(const std::unordered_map<std::string, std::string>& format_args){
        auto raw_template = _content.dump();
        

        for(auto& [arg, val]: format_args) {
            detail::string_format(raw_template, arg, val);
        }
        
        _content = json::parse(raw_template);
        
        return *this;
    }
    
}

#endif
