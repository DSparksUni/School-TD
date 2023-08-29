#include "uni_util.hpp"

namespace uni {
    nodiscard std::string&& read_file(std::string_view file_path) noexcept {
        std::ifstream fstream(file_path.data());

        std::string file_content;
        fstream >> file_content;

        return std::move(file_content);
    }
}