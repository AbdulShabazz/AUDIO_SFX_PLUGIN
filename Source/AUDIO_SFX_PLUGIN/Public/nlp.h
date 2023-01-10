#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{

	template<typename T, typename U>
	class nlp
	{
	public:
		nlp();
	};
	
	template<typename T>
	std::unordered_map<std::string, ComplexVector2DT<T>> GetNLPMap()
	{
		// LIST THE 44 (MOST COMMON) ENGLISH PHONEMES
		std::unordered_map<std::string, ComplexVector2DT<T>> NLPMap;
		
		// 1. VOWELS
		NLPMap["p"] = nlpVector2DTPat;	// as in "pat"
		NLPMap["b"] = nlpVector2DTBat;	// as in "bat"	
		NLPMap["t"] = nlpVector2DTap;	// as in "tap"
		NLPMap["d"] = nlpVector2DTDog;	// as in "dog"		
		NLPMap["k"] = nlpVector2DTCat;	// as in "cat"
        NLPMap["g"] = nlpVector2DTGo;	// as in "go"
		NLPMap["f"] = nlpVector2DTFish;	// as in "fish"
		NLPMap["v"] = nlpVector2DTVat;	// as in "vat"
		NLPMap["θ"] = nlpVector2DTTHink;// as in "think"
		NLPMap["ð"] = nlpVector2DTTHis; // as in "this"
		NLPMap["s"] = nlpVector2DTSip;	// as in "sip"
		NLPMap["z"] = nlpVector2DTZip;	// as in "zip"
		NLPMap["ʃ"] = nlpVector2DTSHeep;	// as in "sheep"
		NLPMap["ʒ"] = nlpVector2DTMeasure;	// as in "measure"
		NLPMap["h"] = nlpVector2DTHat;	// as in "hat"
		NLPMap["m"] = nlpVector2DTMat;	// as in "mat"
		NLPMap["n"] = nlpVector2DTNap;	// as in "nap"
		NLPMap["ŋ"] = nlpVector2DTsINg; // as in "sing"
		NLPMap["l"] = nlpVector2DTLip;	// as in "lip"
		NLPMap["r"] = nlpVector2DTRip;	// as in "rip"
		NLPMap["j"] = nlpVector2DTYacht;// as in "yacht"
		NLPMap["w"] = nlpVector2DTWet;	// as in "wet"

		// 2. CONSONANTS
		NLPMap["i"] = nlpVector2DTbEEt; // as in "beet"
		NLPMap["ɪ"] = nlpVector2DTbIt;	// as in "bit"
		NLPMap["e"] = nlpVector2DTbAIt; // as in "bait"
		NLPMap["ɛ"] = nlpVector2DTbEt;	// as in "bet"
		NLPMap["æ"] = nlpVector2DTbAt;	// as in "bat"
		NLPMap["a"] = nlpVector2DTfAther;	// as in "father"
		NLPMap["ɑ"] = nlpVector2DTbOUGHt;	// as in "bought"
		NLPMap["ɔ"] = nlpVector2DTbAWl; // as in "bawl"
		NLPMap["o"] = nlpVector2DTOAt;	// as in "oat"
		NLPMap["ʊ"] = nlpVector2DTfOOt; // as in "foot"
		NLPMap["u"] = nlpVector2DTbOOt; // as in "boot"
		return NLPMap;
	}	
}
