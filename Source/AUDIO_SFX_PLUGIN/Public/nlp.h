#pragma once

#include <unordered_map>
#include <complex>
#include <vector>

namespace ToneLibrary
{

	template<typename T, typename U>
	class nlp
	{
	public:
		nlp();

		template<typename T>
		static std::unordered_map<std::string, 
		std::vector<std::vector<std::complex<T>>>> nlp_has_phoneme;
	};

}
