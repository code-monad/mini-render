#ifndef __MRENDER_HTTP_HH__
#define __MRENDER_HTTP_HH__

#include <curlpp/Easy.hpp>
#include <curlpp/Easy.hpp>

#include <list>
#include <unordered_map>
#include <string>
#include <memory>

namespace mrender {
    namespace http {
        enum request_method_type {
            GET = 0,
            POST = 1,
            PUT = 2,
        };

        typedef std::list<std::string> header_type;

        typedef std::unordered_map<std::string, std::string> header_segment_type;
        
        const header_type build_header(const header_segment_type& header_segments = {});

        std::shared_ptr<curlpp::Easy> build_request(const std::string& url,const std::string& body = {}, const header_type& headers= {}, const request_method_type type = request_method_type::GET);
    }
}

#endif
