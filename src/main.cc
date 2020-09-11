#include <mrender/http.hh>
#include <mrender/template.hh>
#include <mrender/render.hh>
#include <mrender/parse.hh>
#include <mrender/manager.hh>
#include <fmt/core.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

bool perform(const std::string& endpoint, const std::string& content = {}, const std::list<std::string>& header = {}, const mrender::http::request_method_type method = mrender::http::GET) {
    try {
        fmt::print("Posting {} to {}\n", content, endpoint);
        auto request = mrender::http::build_request(endpoint, content, header, method);
        request->perform();
        if(curlpp::infos::ResponseCode::get(*request) != 200) {
            fmt::print("Response code not 200: [{}]\n", curlpp::infos::ResponseCode::get(*request));
            return false;
        }
        return true;
    } catch (curlpp::LogicError& ex) {
        fmt::print("curlpp::LogicError | {}\n", ex.what());
    } catch (curlpp::RuntimeError& ex) {
        fmt::print("curlpp::RuntimeError | {}\n", ex.what());
    }
    return false;   
}

bool post_render(const std::string& endpoint, std::shared_ptr<mrender::basic_render> render, const std::unordered_map<std::string, std::string>& formats = {}) {
    switch (render->get_type()) {
    default:
    case mrender::RENDER_TYPE::RAW:
    {
        auto real_render = std::static_pointer_cast<mrender::Render>(render);
        fmt::print("normal render\n");
        return perform(endpoint, real_render->produce(formats), {}, mrender::http::POST);
    }
    break;
    case mrender::RENDER_TYPE::JSON:
    {
        auto real_render = std::static_pointer_cast<mrender::JsonRender>(render);
        fmt::print("json render\n");
        return perform(endpoint, real_render->produce(formats), {"Content-Type: " "application/json"}, mrender::http::POST);
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::shared_ptr<mrender::parse> p;
    std::shared_ptr<mrender::manager> manager;
    try {
        p = std::make_shared<mrender::parse>(argc, argv);
        if(argc < 2) {
            fmt::print("{}", p->help());
            return 0;
        }
        
        manager = std::make_shared<mrender::manager>(p->get_template_base_path());
        
    } catch (std::exception& ex) {
        fmt::print("Error while reading args:{}\n", ex.what());
        return -1;
    }
    try {
        auto render = manager->get_render(p->get_template_name());
        if(!render->is_valid()) {
            fmt::print("template {} is not valid! please check!\n", p->get_template_name());
            return -1;
        }
        curlpp::initialize();
        int retry = p->get_retry_time();
        bool success = false;
        
        for(int i = 0; i < retry; i++) {
            success = post_render(p->get_endpoint(),render, p->get_formats());
            if(success) {
                break;
            }
            else {
                fmt::print("Retrying...({}/{})\n", i+1, retry);
            }
        }

        if(!success) {
            fmt::print("Failed after {} tries!!\nBOOM!\n", retry);
            return -1;
        }
    } catch (const nlohmann::json::exception& ex) {
        fmt::print("Error while post rendering json template {}\n", p->get_template_name());
        return -1;
    } catch (std::exception& ex) {
        fmt::print("Error:{}\n", ex.what());
        curlpp::terminate();
        return -1;
    }
    curlpp::terminate();
    return 0;
}
