#pragma once

#include <unordered_map>

namespace ToneLibrary
{
    template<typename T, typename U>
    class nlp_lib
    {
    public:
        nlp_lib();

        // Natural Language Processing Text for Synthesis (TFS)
        static std::unordered_map<std::string, U> nlp_tfs;

    };
}
