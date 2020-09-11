#include <mrender/manager.hh>
#include <mrender/render.hh>


mrender::manager::manager(const std::string& template_path) : _template_path{template_path} {}

std::shared_ptr<mrender::basic_render> mrender::manager::get_render(const std::string& render_name){
    auto render_path = _template_path / render_name;
    if(render_path.extension() == ".json") {
        return std::make_shared<mrender::JsonRender>(render_path);
    } else {
        return std::make_shared<mrender::Render>(render_path);
    }
}
