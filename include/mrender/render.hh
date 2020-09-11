#ifndef __MRENDER_RENDER_HH__
#define __MRENDER_RENDER_HH__

#include <mrender/template.hh>
#include <filesystem>
#include <fstream>

namespace mrender {

    enum RENDER_TYPE {
        RAW,
        JSON,
    };
    
    struct basic_render {
        basic_render() {}
        virtual const RENDER_TYPE get_type() { return RENDER_TYPE::RAW; }
        virtual bool is_valid() { return true; }
    };

    template<typename ContentType = std::string>
    struct render: public basic_render {
        typedef render<ContentType> render_type;
        render(const std::string& template_path) : basic_render(), _template_path{template_path}, _raw_template{}, _template{{}} {
            if(std::filesystem::is_regular_file(template_path)) {
                load_template(_template_path);
            }
            else {
                _valid = false;
            }
        }

        bool is_valid() override { return _valid; }

        std::string _raw_template;

        Template<ContentType> _template;
        
        virtual Template<ContentType>& get_template();

        const RENDER_TYPE get_type() override;
        
        inline void load_template(const std::filesystem::path& path){
            std::ifstream in(path);
            if(in.is_open()) {
                _raw_template = std::string(std::istreambuf_iterator<char>{in}, {});
                _valid = true;
            } else {
                _valid = false;
            }
        }

        const std::string produce(const std::unordered_map<std::string, std::string>& format_args = {}){
            detail::string_format(_raw_template, format_args);
            return get_template().format(format_args).content();
        }
        
        bool _valid = true;
        std::filesystem::path _template_path;
    };

    using Render = render<std::string>;
    using JsonRender = render<nlohmann::json>;
    
    template<> inline Template<std::string>& Render::get_template() {
        _template = Template<std::string>(_raw_template);
        return _template;
    }

    template<> inline const RENDER_TYPE Render::get_type() { return RENDER_TYPE::RAW;}
    
    template<> inline const RENDER_TYPE JsonRender::get_type() { return RENDER_TYPE::JSON;}
    
    template<> inline JsonTemplate& JsonRender::get_template() {
        _template =  JsonTemplate(nlohmann::json::parse(_raw_template));
        return _template;
    }
}

#endif
