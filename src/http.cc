#include <mrender/http.hh>

#include <fmt/core.h>
#include <curlpp/Options.hpp>
#include <utility>

const mrender::http::header_type mrender::http::build_header(const mrender::http::header_segment_type& header_segments) {
    std::list<std::string> header;
    for(auto& [header_name, value]: header_segments) {
        header.push_back(fmt::format("%s: %s"));
    }
    return header;
}

std::shared_ptr<curlpp::Easy> mrender::http::build_request(const std::string& url, const std::string& body, const header_type& headers, const request_method_type type){
    auto request = std::make_shared<curlpp::Easy>();
    request->setOpt(new curlpp::options::Url(url));
    if(!headers.empty()){
        request->setOpt(new curlpp::options::HttpHeader(headers));
    }
    if(type == mrender::http::request_method_type::POST || !body.empty()){
        request->setOpt(new curlpp::options::PostFields(body));
        request->setOpt(new curlpp::options::PostFieldSize(body.size()));
    }
    return std::move(request);
}
