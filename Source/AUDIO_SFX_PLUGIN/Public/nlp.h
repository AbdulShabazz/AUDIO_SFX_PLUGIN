#pragma once

#include <unordered_map>
#include <complex>
#include <vector>

namespace ToneLibrary
{

	/**
	* Natural Language Processing (NLP) Text-to-Speech (TTS) pipeline for a Text-for-Synthesis (TFS) prompt : 
	* Prompt ---> [Phoneme CODEC] <---> [Neural Language Model CODEC] <---> [Audio Synthesis CODEC] ---> Personalized Speech. 
	* [Audio CODEC] is a 39 parallel concatenative additive voice synthesis engine with builtin breathe dynamics, Multisyn
	* via standard unit selection concatenative methods
	* @param [] ---
	* @returns [] ---
	*/
	template<typename T, typename U>
	class nlp
	{
	public:
		nlp();

		template<typename T>
		static std::unordered_map<std::string, 
		std::vector<std::vector<std::complex<T>>>> nlp_phoneme;
	};

}
