#include "uni_util.hpp"

namespace uni {
    KeySwitch::KeySwitch() noexcept: m_on(false), m_switch(false) {}

    nodiscard bool KeySwitch::on() const noexcept {
        return this->m_on;
    }

    void KeySwitch::turn_on() noexcept {
        this->m_on = true;
    }

    void KeySwitch::turn_off() noexcept {
        this->m_on = false;
    }

    void KeySwitch::activate(bool key) noexcept {
        if(key && !this->m_switch) {
            this->m_on = !this->m_on;
            this->m_switch = true;
        } else if(!key && this->m_switch) this->m_switch = false;
    }

    nodiscard std::string read_entire_file(const char* file_path) {
        std::ifstream file_stream;
        std::stringstream file_content;

        file_stream.open(file_path);
        if((file_stream.rdstate() & std::ifstream::failbit) != 0)
            throw FILE_OPEN_ERROR;

        std::string line;
        while(std::getline(file_stream, line)) file_content << line << '\n';

        return file_content.str();
    }

    nodiscard rapidjson::Document read_json_data(const char* data_name) {
        std::stringstream data_path;
        data_path << "data/" << data_name << "_data.json";
        const std::string file_path = data_path.str();

        const std::string raw_json = read_entire_file(file_path.c_str());

        rapidjson::Document json_data;
        json_data.Parse(raw_json.c_str());

        return json_data;
    }

    double distance(double x1, double y1, double x2, double y2) noexcept {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }
    double distance(vec2d p1, vec2d p2) noexcept {
        return distance(p1.x, p1.y, p2.x, p2.y);
    }
    double distance(vec2d p1, double x2, double y2) noexcept {
        return distance(p1.x, p1.y, x2, y2);
    }
    double distance(double x1, double y1, vec2d p2) noexcept {
        return distance(p2, x1, y1);
    }

    void SDL_texture_deleter(SDL_Texture* texture) noexcept {
        SDL_DestroyTexture(texture);
    }
}