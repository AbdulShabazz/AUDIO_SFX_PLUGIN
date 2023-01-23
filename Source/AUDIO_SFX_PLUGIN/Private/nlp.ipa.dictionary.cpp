#include "nlp.ipa.dictionary.h"

using namespace ToneLibrary;

template<typename T, typename U>
nlp_ipa_Dictionary<T, U>::nlp_ipa_Dictionary()
{

}

template<typename T, typename U>
void nlp_ipa_Dictionary<T, U>::RepackStream(
    FILEINFO_Obj<T, U>& FileInfoObjRefT
    )
{

}

/**
* GenerateSound based on International Phonetic Alphabet (IPA) standards.
* WARNING : Peeks surrounding letters, (read-only) to gather speech characteristics, in parallel.
* @param - [ nlp_ipa_WordVectorStdStrBuffRef ] --- Letter buffer
* @param - [ nlp_ipa_PhonesVector2DUInt64TBuffRef ] -- Phonemes buffer (Up to N-channel)
* @param - [ nIndexUInt64 ] --- Index
* @param - [ LetterStdStr ] --- Letter
* @returns - [ nlp_ipa_PhonesVector2DUInt64TBuffRef[nChannel][nIndexUInt64] ] --- 0.5 second N-channel phoneme in the desired audio format
*/
template<typename T, typename U>
void nlp_ipa_Dictionary<T, U>::GenerateSound(
    FILEINFO_Obj<T, U>& FileInfoObjRefT, 
    const PhoneStruct<U> PhonemeStructReadOnly
    )
{
    std::vector<std::string>& WordVectorStdStrBuffRef = FileInfoObjRefT.nlp_ipa_WordVectorStdStrBuffRef;
    Vector4DU<U>& nlp_ipa_PhonesVector2DUInt64TBuffRef = FileInfoObjRefT.nlp_ipa_PhonesVector2DUInt64TBuffRef;
	const U& nIndexConstUInt64 = PhonemeStructReadOnly.nIndexUInt64;
	const std::string& LetterStrConstRef = PhonemeStructReadOnly.LetterStdStr;
	switch (LetterStrConstRef)
	{
        // Consonant Sounds
        case "b": // as in "bat"
        case "d": // as in "dog"
        case "f": // as in "fish"
        case "g": // as in "go"
        case "h": // as in "hat"
        case "j": // as in "jump, budget"
        case "k": // as in "cat"
        case "l": // as in "lip"
        case "m": // as in "mat"
        case "n": // as in "nap"
        case "p": // as in "pat"
        case "r": // as in "rip"
        case "s": // as in "sip"
        case "s3": // as in "thousand"; "s3" == "z"
        case "sh": // as in "sheep"
        case "t": // as in "tap"
        case "ch": // as in "church, witch"
        case "th": // as in "think, math, nothing"
        case "th2": // as in "this, breathe"
        case "v": // as in "vat"
        case "w": // as in "wet"
        case "hw": // as in "where, somewhat"
        case "y": // as in "yacht, yes, onion"
        case "z": // as in "zoo, zip, easy"; "z" == "s3"
        case "z2": // as in "measure, television, beige"

        // Vowel Sounds
        case "a": // as in "apple, hat, bat"
        case "a2": // as in "aid, bait, day"
        case "a3": // as in "arm, father, aha"
        case "e": // as in "bet, ever, head"
        case "e2": // as in "beet, eat, seed, need"
        case "i": // as in "it, finishes"
        case "i2": // as in "I, ice, deny"  
        case "i3": // as in first, thirst
        case "o": // as in "odd, waffle"
        case "o2": // as in "letter 'o', owe, road"
        case "o3": // as in "good, book"
        case "u": // as in "up, mother"
        case "u2": // as in rude, brute  

        // Letter Sounds
        case "a2": // Sounds like "a2":
        case "b2": // Sounds like "b_e2":
        case "c2": // Sounds like "s_e2":
        case "d2": // Sounds like "d_e2":
        case "e2": // Sounds like "e2":
        case "f2": // Sounds like "e_f":
        case "g2": // Sounds like "j_e2":
        case "h2": // Sounds like "a2_ch":
        case "i2": // Sounds like "i2":
        case "j2": // Sounds like "j_a2":
        case "k2": // Sounds like "k_a2":
        case "l2": // Sounds like "e_l":
        case "m2": // Sounds like "e_m":
        case "n2": // Sounds like "e_n":
        case "o2": // Sounds like "o2":
        case "p2": // Sounds like "p_e2":
        case "q2": // Sounds like "k_y_o3":
        case "r2": // Sounds like "a3_r":
        case "s2": // Sounds like "e_s":
        case "t2": // Sounds like "t_e2":
        case "u2": // Sounds like "y_o3":
        case "v2": // Sounds like "v_e2":
        case "w2": // Sounds like "d_u3_b_e_l_y_u2":
        case "x2": // Sounds like "e_k_s":
        case "y2": // Sounds like "w_i2":
        case "z2": // Sounds like "z_e2":

        // Number Sounds
        case "#": // (optional) Sounds like "a_n_d"
        case "0": // Sounds like "z2_e2_r_o2" or silent when used in ordinals
        case "1": // Sounds like "w_o_n" or "f_i3_r_" when used in ordinals
        case "2": // Sounds like "t_o3" or "s_e_k_o_" when used in ordinals
        case "3": // Sounds like "th_r_e2" or "th_i3_r_" when used in ordinals
        case "4": // Sounds like "f_o2_r" 
        case "5": // Sounds like "f_i2_v":
        case "6": // Sounds like "s_i_k_s":
        case "7": // Sounds like "s_e_v_e_n2":
        case "8": // Sounds like "a2_t":
        case "9": // Sounds like "n_i2_n": 
        case "00": // Sounds like "h_u_n_d_r_e_d"
        case "000": // Sounds like "th_o_w_s3_a_n_d" or "th_o_w_z_a_n_d"
        case "000_000": // Sounds like "m_i_l_y_o_n"
        case "000_000_000": // Sounds like "b_i_l_y_o_n"
        case "000_000_000_000": // Sounds like "t_r_i_l_y_o_n"

        //Ordinal Sounds
        case "_st": // Sounds like "i3_r_s_t": Used exclusively with ordinals that end in 1: 1st, 101st 1001st
        case "_nd": // Sounds like "e_k_o_n_d": Used exclusively with ordinals that end in 2: 2nd (2_nd), 102nd (100_2_nd), 1002nd (1_000_2_nd or (1_000_#_2_nd)
        case "_rd": // Sounds like "i3_r_d": Used exclusively with ordinals that end in 3: 3rd (3_rd), 103rd (100_3_rd), 1003rd (1_000_3_rd)
        case "_th": // Sounds like "e_n_th" in D_N_th, Where D is zero or more digits; and N, is zero or greater than 4, as D_N_th: 100th (100_th), 104th (100_4_th), 4th (4_th), 1004th (1_000_4_th), 106th (100_6_th).

	default:
		break;
	}
}