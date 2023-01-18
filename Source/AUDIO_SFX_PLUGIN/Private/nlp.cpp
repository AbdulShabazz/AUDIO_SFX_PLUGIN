#include "nlp.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

template<typename T, typename U>
nlp_phoneme<T, U>::nlp_phoneme()
{

}

template<typename T, typename U>
void nlp_phoneme<T, U>::tts_generate(PHONEME_STRUCT<T, U>&)
{

}

template<typename T, typename U>
nlp<T, U>::nlp()
{
	// USAGE: information >> [in-fer-mey-shuhn] >> [i][n]-[f][er]-[m][e][y]-[sh][uh][n]
	
	// 1. CONSONANTS
	nlp_phoneme_hash["b"] = nlp_phoneme();	// as in "bat"	
	nlp_phoneme_hash["d"] = nlp_phoneme();	// as in "dog"
	nlp_phoneme_hash["f"] = nlp_phoneme();// as in "fish"
	nlp_phoneme_hash["g"] = nlp_phoneme();	// as in "go"
	nlp_phoneme_hash["h"] = nlp_phoneme();	// as in "hat"
	nlp_phoneme_hash["j"] = nlp_phoneme();	// as in "jump, budget"	
	nlp_phoneme_hash["k"] = nlp_phoneme();	// as in "cat"
	nlp_phoneme_hash["l"] = nlp_phoneme();	// as in "lip"
	nlp_phoneme_hash["m"] = nlp_phoneme();	// as in "mat"
	nlp_phoneme_hash["n"] = nlp_phoneme();	// as in "nap"
	nlp_phoneme_hash["ng"] = nlp_phoneme(); // as in "sing"
	nlp_phoneme_hash["p"] = nlp_phoneme();	// as in "pat"
	nlp_phoneme_hash["r"] = nlp_phoneme();	// as in "rip"
	nlp_phoneme_hash["s"] = nlp_phoneme();	// as in "sip"
	nlp_phoneme_hash["sh"] = nlp_phoneme();	// as in "sheep"
	nlp_phoneme_hash["t"] = nlp_phoneme();	// as in "tap"	
	nlp_phoneme_hash["ch"] = nlp_phoneme();	// as in "church, witch"
	nlp_phoneme_hash["th"] = nlp_phoneme();// as in "think, math, nothing"
	nlp_phoneme_hash["th2"] = nlp_phoneme(); // as in "this, breathe"
	nlp_phoneme_hash["v"] = nlp_phoneme();	// as in "vat"
	nlp_phoneme_hash["w"] = nlp_phoneme();	// as in "wet"
	nlp_phoneme_hash["hw"] = nlp_phoneme();	// as in "where, somewhat"
	nlp_phoneme_hash["y"] = nlp_phoneme();// as in "yacht, yes, onion"
	nlp_phoneme_hash["z"] = nlp_phoneme();	// as in "zoo, zip, easy"
	nlp_phoneme_hash["zh"] = nlp_phoneme();	// as in "measure, television, beige"

	// 2. VOWELS
	nlp_phoneme_hash["a"] = nlp_phoneme();	// as in "apple, hat, bat"
	nlp_phoneme_hash["ey"] = nlp_phoneme(); // as in "aid, bait, day"
	nlp_phoneme_hash["ah"] = nlp_phoneme();	// as in "arm, father, aha"
	nlp_phoneme_hash["air"] = nlp_phoneme();	// as in "air, careful, wear"
	nlp_phoneme_hash["aw"] = nlp_phoneme();	// as in "bought"
	nlp_phoneme_hash["e"] = nlp_phoneme();	// as in "bet, ever, head"
	nlp_phoneme_hash["ee"] = nlp_phoneme(); // as in "beet, eat, seed, need"
	nlp_phoneme_hash["eer"] = nlp_phoneme(); // as in "teacher, murderer"
	nlp_phoneme_hash["i"] = nlp_phoneme(); // as in "it, finishes"
	nlp_phoneme_hash["ahy"] = nlp_phoneme(); // as in "I, ice, deny"
	nlp_phoneme_hash["o"] = nlp_phoneme(); // as in "odd, waffle"
	nlp_phoneme_hash["oh"] = nlp_phoneme(); // as in "owe, road"
	nlp_phoneme_hash["oo"] = nlp_phoneme(); // as in "good, soup"
	nlp_phoneme_hash["oo2"] = nlp_phoneme(); // as in "put, book"
	nlp_phoneme_hash["ou"] = nlp_phoneme(); // as in "out, how, loud"
	nlp_phoneme_hash["uh"] = nlp_phoneme(); // as in "up, mother"
	nlp_phoneme_hash["uh2"] = nlp_phoneme(); // as in "about, problem, circus"
	nlp_phoneme_hash["ur"] = nlp_phoneme(); // as in "early, stirring"

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
