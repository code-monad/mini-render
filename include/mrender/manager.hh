#ifndef __MRENDER_MANAGER_HH__
#define __MRENDER_MANAGER_HH__

#include <filesystem>
#include <memory>

namespace mrender {

    class basic_render;
    
    class manager {
    public:
        manager(const std::string& template_path = "templates");
        std::shared_ptr<basic_render> get_render(const std::string& render_name);

    private:
        std::filesystem::path _template_path;
    };
}

#endif
