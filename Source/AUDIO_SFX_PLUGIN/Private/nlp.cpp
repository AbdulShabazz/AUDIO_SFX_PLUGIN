#include "nlp.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

template<typename T, typename U>
nlp<T, U>::nlp()
{
	// 1. CONSONANTS
	nlp_phoneme["p"] = nlpVector2DTPat;	// as in "pat"
	nlp_phoneme["b"] = nlpVector2DTBat;	// as in "bat"	
	nlp_phoneme["t"] = nlpVector2DTap;	// as in "tap"
	nlp_phoneme["d"] = nlpVector2DTDog;	// as in "dog"		
	nlp_phoneme["k"] = nlpVector2DTCat;	// as in "cat"
	nlp_phoneme["g"] = nlpVector2DTGo;	// as in "go"
	nlp_phoneme["f"] = nlpVector2DTFish;	// as in "fish"
	nlp_phoneme["v"] = nlpVector2DTVat;	// as in "vat"
	nlp_phoneme["θ"] = nlpVector2DTTHink;// as in "think"
	nlp_phoneme["ð"] = nlpVector2DTTHis; // as in "this"
	nlp_phoneme["s"] = nlpVector2DTSip;	// as in "sip"
	nlp_phoneme["z"] = nlpVector2DTZip;	// as in "zip"
	nlp_phoneme["ʃ"] = nlpVector2DTSHeep;	// as in "sheep"
	nlp_phoneme["ʒ"] = nlpVector2DTMeasure;	// as in "measure"
	nlp_phoneme["h"] = nlpVector2DTHat;	// as in "hat"
	nlp_phoneme["m"] = nlpVector2DTMat;	// as in "mat"
	nlp_phoneme["n"] = nlpVector2DTNap;	// as in "nap"
	nlp_phoneme["ŋ"] = nlpVector2DTsINg; // as in "sing"
	nlp_phoneme["l"] = nlpVector2DTLip;	// as in "lip"
	nlp_phoneme["r"] = nlpVector2DTRip;	// as in "rip"
	nlp_phoneme["j"] = nlpVector2DTYacht;// as in "yacht"
	nlp_phoneme["w"] = nlpVector2DTWet;	// as in "wet"

	// 2. VOWELS
	nlp_phoneme["i"] = nlpVector2DTbEEt; // as in "beet"
	nlp_phoneme["ɪ"] = nlpVector2DTbIt;	// as in "bit"
	nlp_phoneme["e"] = nlpVector2DTbAIt; // as in "bait"
	nlp_phoneme["ɛ"] = nlpVector2DTbEt;	// as in "bet"
	nlp_phoneme["æ"] = nlpVector2DTbAt;	// as in "bat"
	nlp_phoneme["a"] = nlpVector2DTfAther;	// as in "father"
	nlp_phoneme["ɑ"] = nlpVector2DTbOUGHt;	// as in "bought"
	nlp_phoneme["ɔ"] = nlpVector2DTbAWl; // as in "bawl"
	nlp_phoneme["o"] = nlpVector2DTOAt;	// as in "oat"
	nlp_phoneme["ʊ"] = nlpVector2DTfOOt; // as in "foot"
	nlp_phoneme["u"] = nlpVector2DTbOOt; // as in "boot"
}

/**
* A parallel wave-shaping strategy around the fundamental frequency, F0.
* @param [] ---
* @returns [] ---
*/
template<typename T, typename U>
void nlp<T, U>::nlp_ParallelHiddenMarkov_tts()
{
}

/**
* A fourty-four state (44) phoneme cascading state-machine 
* with intra-state wave-shaping hand - off, for smoother 
* wave-shaping between ingress and egress.
* @param [] ---
* @returns [] ---
*/
template<typename T, typename U>
void nlp<T, U>::nlp_SerialHiddenMarkov_tts()
{
	U nSizeUInt64T = 100;
	U NumChannelsUInt64T = 2;

	Vector2DT<T> VecFloat64T = Vector2DT<T>(VectorT<T>(NumChannelsUInt64T), nSizeUInt64T);	// two-channel audio result 
	VectorT<T> TransitionProbabilityVectorFloat64T = VectorT<T>(nSizeUInt64T); // Where, Sum(TransitionProbabilityVectorFloat64T) == 1

	// TEMP Placeholders
	bool HiddenMarkovModelSingleModeGaussianDensityBool = true;
	T O_t = 2.0f; // t is the current place in the sample
	T Mu_j = 1.0f; // j is the current state of the model
	T Sigma_j(T valT)
	{
		return valT;
	};

	for (VectorT<T>& ChannelVectorFloat64T : VecFloat64T)
	{
		U nIdxUInt64T = 0;
		for (T& valFloat64T : ChannelVectorFloat64T)
		{
			if (HiddenMarkovModelSingleModeGaussianDensityBool)
			{
				valFloat64T = (1.0 / std::sqrt(2 * UE_FLOAT64_PI * TransitionProbabilityVectorFloat64T[nIdxUInt64T++])) *
					std::exp(-0.5f * std::pow((O_t - Mu_j)) * Sigma_j(O_t - Mu_j));
			}
			else // The Gaussian Mixture Model (GMM) provides richer modeling qualities
			{
				valFloat64T;// = Cmj
			}
		}
	}
}
