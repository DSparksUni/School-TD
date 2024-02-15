#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>

#include "rapidjson/document.h"

#include "uni_util.hpp"

namespace uni {
    class Json {  
    private:
        static std::unique_ptr<
            std::unordered_map<const char*, rapidjson::Document>
        > json_data;

        static bool has_data;
    public:
        nodiscard static rapidjson::Document* get(
            const char* data_name
        ) noexcept;
    };
}