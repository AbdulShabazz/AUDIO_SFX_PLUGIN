#include "nlp.h"

using namespace ToneLibrary;

template<typename T, typename U>
nlp<T, U>::nlp()
{
	// 1. CONSONANTS
	nlp_has_phoneme["p"] = nlpVector2DTPat;	// as in "pat"
	nlp_has_phoneme["b"] = nlpVector2DTBat;	// as in "bat"	
	nlp_has_phoneme["t"] = nlpVector2DTap;	// as in "tap"
	nlp_has_phoneme["d"] = nlpVector2DTDog;	// as in "dog"		
	nlp_has_phoneme["k"] = nlpVector2DTCat;	// as in "cat"
	nlp_has_phoneme["g"] = nlpVector2DTGo;	// as in "go"
	nlp_has_phoneme["f"] = nlpVector2DTFish;	// as in "fish"
	nlp_has_phoneme["v"] = nlpVector2DTVat;	// as in "vat"
	nlp_has_phoneme["θ"] = nlpVector2DTTHink;// as in "think"
	nlp_has_phoneme["ð"] = nlpVector2DTTHis; // as in "this"
	nlp_has_phoneme["s"] = nlpVector2DTSip;	// as in "sip"
	nlp_has_phoneme["z"] = nlpVector2DTZip;	// as in "zip"
	nlp_has_phoneme["ʃ"] = nlpVector2DTSHeep;	// as in "sheep"
	nlp_has_phoneme["ʒ"] = nlpVector2DTMeasure;	// as in "measure"
	nlp_has_phoneme["h"] = nlpVector2DTHat;	// as in "hat"
	nlp_has_phoneme["m"] = nlpVector2DTMat;	// as in "mat"
	nlp_has_phoneme["n"] = nlpVector2DTNap;	// as in "nap"
	nlp_has_phoneme["ŋ"] = nlpVector2DTsINg; // as in "sing"
	nlp_has_phoneme["l"] = nlpVector2DTLip;	// as in "lip"
	nlp_has_phoneme["r"] = nlpVector2DTRip;	// as in "rip"
	nlp_has_phoneme["j"] = nlpVector2DTYacht;// as in "yacht"
	nlp_has_phoneme["w"] = nlpVector2DTWet;	// as in "wet"

	// 2. VOWELS
	nlp_has_phoneme["i"] = nlpVector2DTbEEt; // as in "beet"
	nlp_has_phoneme["ɪ"] = nlpVector2DTbIt;	// as in "bit"
	nlp_has_phoneme["e"] = nlpVector2DTbAIt; // as in "bait"
	nlp_has_phoneme["ɛ"] = nlpVector2DTbEt;	// as in "bet"
	nlp_has_phoneme["æ"] = nlpVector2DTbAt;	// as in "bat"
	nlp_has_phoneme["a"] = nlpVector2DTfAther;	// as in "father"
	nlp_has_phoneme["ɑ"] = nlpVector2DTbOUGHt;	// as in "bought"
	nlp_has_phoneme["ɔ"] = nlpVector2DTbAWl; // as in "bawl"
	nlp_has_phoneme["o"] = nlpVector2DTOAt;	// as in "oat"
	nlp_has_phoneme["ʊ"] = nlpVector2DTfOOt; // as in "foot"
	nlp_has_phoneme["u"] = nlpVector2DTbOOt; // as in "boot"
}
