#include <mrender/parse.hh>

#include <argparse/argparse.hpp>

#include <fmt/core.h>

mrender::parse::parse(int argc, char** argv) {
    argparse::ArgumentParser program("poster");
    program.add_argument("-c")
        .help("template base path. default=templates/");

    program.add_argument("--retry")
        .help("retry time, default=3");

    program.add_argument("--endpoint")
        .required()
        .help("the endpoint, example: https://example.com/post");
    
    program.add_argument("-t")
        .required()
        .help("the template to use. example: example.json");

    program.add_argument("formats")
        .remaining()
        .default_value({})
        .help("format options. example: a=1 b=2");
    
    _help = program.help().str();

    if(argc > 1) {
        program.parse_args(argc, argv);
        if( auto config = program.present("-c")) {
            _template_base_path = *config;
        } else {
            _template_base_path = "templates";
        }

        if( auto config = program.present("--endpoint")) {
            _endpoint = *config;
        }

        if( auto config = program.present("--retry")) {
            _retry_time = std::stoi(*config);
        } else {
            _retry_time = 3;
        }
        
    
        _template_name = program.get<std::string>("-t");

        if( auto config = program.present("formats")) {
            auto format_options = program.get<std::vector<std::string>>("formats");
            for(auto& option : format_options) {
                auto delimiter_pos = option.find("=");
                if(delimiter_pos != std::string::npos && delimiter_pos != option.size() - 1) {
                    auto key =  option.substr(0, delimiter_pos);
                    auto value = option.substr(delimiter_pos+1);
                    _formats[key] = value;
                } else {
                    fmt::print("Warn: format option [{}] is invalid, ignored.\n", option);
                }
            }
        }
            
    }
}
