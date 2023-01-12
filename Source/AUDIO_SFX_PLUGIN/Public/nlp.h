#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{

	template<typename T, typename U>
	class nlp
	{
	public:
		nlp();

		template<typename T>
		std::unordered_map<std::string, ComplexVector2DT<T>> nlp_has();
	};
}
