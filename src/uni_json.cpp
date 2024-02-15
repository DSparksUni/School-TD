#include "uni_json.hpp"

namespace uni {
    bool Json::has_data = false;
    std::unique_ptr<
        std::unordered_map<const char*, rapidjson::Document>
    > Json::json_data = nullptr;

    nodiscard rapidjson::Document* Json::get(const char* data_name) noexcept {
        if(!has_data) {
            json_data = std::make_unique<
                std::unordered_map<const char*, rapidjson::Document>
            >();
            has_data = true;
        }

        if(json_data->find(data_name) == json_data->end())
            json_data->insert(
                std::make_pair(data_name, read_json_data(data_name))
            );

        return &json_data->at(data_name);
    }
}