#pragma once

#include <unordered_map>

namespace ToneLibrary
{
    template<typename T, typename U>
    class nlp_lib
    {
    public:
        nlp_lib();
        static std::unordered_map<std::string, U> nlp_has_glyphs;

    };
}
