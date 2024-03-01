#include "uni_json.hpp"

namespace uni {
    bool Json::has_data = false;
    std::unique_ptr<
        std::unordered_map<const char*, std::string>
    > Json::raw_json_data = nullptr;

    nodiscard std::string Json::get(const char* data_name) {
        if(!has_data) {
            raw_json_data = std::make_unique<
                std::unordered_map<const char*, std::string>
            >();
            has_data = true;
        }

        if(raw_json_data->find(data_name) == raw_json_data->end())
            raw_json_data->insert(
                std::make_pair(data_name, read_entire_file(data_name))
            );

        return raw_json_data->at(data_name);
    }
}
