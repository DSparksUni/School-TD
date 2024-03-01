#include "uni_level.hpp"

namespace uni {
    Level::Level(
        SDL_Renderer* render, const char* image_path,
        std::vector<vec2i> path
    ): m_image(nullptr), m_path(path) {
        this->m_image = IMG_LoadTexture(render, image_path);
        if(!this->m_image)
            throw error::SDL_TEXTURE_CREATION_ERROR;
    }
    Level::~Level() {
        SDL_DestroyTexture(this->m_image);
    }

    nodiscard SDL_Texture* Level::image() const noexcept {
        return this->m_image;
    }
    nodiscard const std::vector<vec2i>& Level::path() const noexcept {
        return this->m_path;
    }

    nodiscard vec2i Level::get(size_t idx) const noexcept {
        return this->m_path[idx];
    }

    nodiscard vec2i Level::operator[](size_t idx) const noexcept {
        return this->get(idx);
    }

    nodiscard size_t Level::len() const noexcept {
        return this->m_path.size();
    }

    void Level::draw(SDL_Renderer* render) const noexcept {
        SDL_RenderCopy(render, this->m_image, NULL, NULL);
    }

    TestLevel::TestLevel(SDL_Renderer* render): super(
        render, "assets/test_map.png", {
            {6, 131},    {38, 128},   {73, 128},
            {120, 128},  {158, 128},  {205, 134},
            {249, 136},  {291, 132},  {343, 131},
            {405, 128},  {464, 127},  {515, 122},
            {560, 131},  {619, 132},  {682, 132},
            {712, 134},  {767, 131},  {827, 125},
            {868, 113},  {903, 122},  {945, 145},
            {982, 165},  {1001, 180}, {1014, 201},
            {1014, 222}, {1013, 256}, {1007, 308},
            {994, 342},  {985, 364},  {976, 412},
            {985, 457},  {1000, 474}, {1018, 494},
            {1025, 525}, {1028, 553}, {1028, 585},
            {1016, 606}, {975, 623},  {927, 626},
            {882, 622},  {840, 626},  {789, 625},
            {738, 625},  {713, 623},  {658, 620},
            {601, 615},  {533, 606},  {484, 602},
            {411, 598},  {352, 602},  {267, 602},
            {166, 587},  {96, 589},   {7, 584}
        }
    ) {}
}
