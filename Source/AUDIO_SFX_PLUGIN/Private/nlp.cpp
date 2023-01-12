#include "nlp.h"

using namespace ToneLibrary;

template<typename T, typename U>
nlp<T, U>::nlp()
{
	// 1. CONSONANTS
	nlp_has["p"] = nlpVector2DTPat;	// as in "pat"
	nlp_has["b"] = nlpVector2DTBat;	// as in "bat"	
	nlp_has["t"] = nlpVector2DTap;	// as in "tap"
	nlp_has["d"] = nlpVector2DTDog;	// as in "dog"		
	nlp_has["k"] = nlpVector2DTCat;	// as in "cat"
	nlp_has["g"] = nlpVector2DTGo;	// as in "go"
	nlp_has["f"] = nlpVector2DTFish;	// as in "fish"
	nlp_has["v"] = nlpVector2DTVat;	// as in "vat"
	nlp_has["θ"] = nlpVector2DTTHink;// as in "think"
	nlp_has["ð"] = nlpVector2DTTHis; // as in "this"
	nlp_has["s"] = nlpVector2DTSip;	// as in "sip"
	nlp_has["z"] = nlpVector2DTZip;	// as in "zip"
	nlp_has["ʃ"] = nlpVector2DTSHeep;	// as in "sheep"
	nlp_has["ʒ"] = nlpVector2DTMeasure;	// as in "measure"
	nlp_has["h"] = nlpVector2DTHat;	// as in "hat"
	nlp_has["m"] = nlpVector2DTMat;	// as in "mat"
	nlp_has["n"] = nlpVector2DTNap;	// as in "nap"
	nlp_has["ŋ"] = nlpVector2DTsINg; // as in "sing"
	nlp_has["l"] = nlpVector2DTLip;	// as in "lip"
	nlp_has["r"] = nlpVector2DTRip;	// as in "rip"
	nlp_has["j"] = nlpVector2DTYacht;// as in "yacht"
	nlp_has["w"] = nlpVector2DTWet;	// as in "wet"

	// 2. VOWELS
	nlp_has["i"] = nlpVector2DTbEEt; // as in "beet"
	nlp_has["ɪ"] = nlpVector2DTbIt;	// as in "bit"
	nlp_has["e"] = nlpVector2DTbAIt; // as in "bait"
	nlp_has["ɛ"] = nlpVector2DTbEt;	// as in "bet"
	nlp_has["æ"] = nlpVector2DTbAt;	// as in "bat"
	nlp_has["a"] = nlpVector2DTfAther;	// as in "father"
	nlp_has["ɑ"] = nlpVector2DTbOUGHt;	// as in "bought"
	nlp_has["ɔ"] = nlpVector2DTbAWl; // as in "bawl"
	nlp_has["o"] = nlpVector2DTOAt;	// as in "oat"
	nlp_has["ʊ"] = nlpVector2DTfOOt; // as in "foot"
	nlp_has["u"] = nlpVector2DTbOOt; // as in "boot"
}
