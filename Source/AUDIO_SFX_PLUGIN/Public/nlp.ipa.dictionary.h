#pragma once

/** International Phonetic Alphabet (IPA) 

[
    // Consonant Sounds
    "b", // as in "bat"
    "d", // as in "dog"
    "f", // as in "fish"
    "g", // as in "go"
    "h", // as in "hat"
    "j", // as in "jump, budget"
    "k", // as in "cat"
    "l", // as in "lip"
    "m", // as in "mat"
    "n", // as in "nap"
    "p", // as in "pat"
    "r", // as in "rip"
    "s", // as in "sip"
    "s3", // as in "thousand"; "s3" == "z"
    "sh", // as in "sheep"
    "t", // as in "tap"
    "ch", // as in "church, witch"
    "th", // as in "think, math, nothing"
    "th2", // as in "this, breathe"
    "v", // as in "vat"
    "w", // as in "wet"
    "hw", // as in "where, somewhat"
    "y", // as in "yacht, yes, onion"
    "z", // as in "zoo, zip, easy"; "z" == "s3"
    "z2", // as in "measure, television, beige"

    // Vowel Sounds
    "a", // as in "apple, hat, bat"
    "a2", // as in "aid, bait, day"
    "a3", // as in "arm, father, aha"
    "e", // as in "bet, ever, head"
    "e2", // as in "beet, eat, seed, need"
    "i", // as in "it, finishes"
    "i2", // as in "I, ice, deny"  
    "i3", // as in first, thirst
    "o", // as in "odd, waffle"
    "o2", // as in "letter 'o', owe, road"
    "o3", // as in "good, book"
    "u", // as in "up, mother"
    "u2", // as in rude, brute  
    
    // Letter Sounds
    "a2", // Sounds like "a2",
    "b2", // Sounds like "b_e2",
    "c2", // Sounds like "s_e2",
    "d2", // Sounds like "d_e2",
    "e2", // Sounds like "e2",
    "f2", // Sounds like "e_f",
    "g2", // Sounds like "j_e2",
    "h2", // Sounds like "a2_ch",
    "i2", // Sounds like "i2",
    "j2", // Sounds like "j_a2",
    "k2", // Sounds like "k_a2",
    "l2", // Sounds like "e_l",
    "m2", // Sounds like "e_m",
    "n2", // Sounds like "e_n",
    "o2", // Sounds like "o2",
    "p2", // Sounds like "p_e2",
    "q2", // Sounds like "k_y_o3",
    "r2", // Sounds like "a3_r",
    "s2", // Sounds like "e_s",
    "t2", // Sounds like "t_e2",
    "u2", // Sounds like "y_o3",
    "v2", // Sounds like "v_e2",
    "w2", // Sounds like "d_u3_b_e_l_y_u2",
    "x2", // Sounds like "e_k_s",
    "y2", // Sounds like "w_i2",
    "z2", // Sounds like "z_e2",

    // Number Sounds
    "#", // (optional) Sounds like "a_n_d"
    "0", // Sounds like "z2_e2_r_o2" or silent when used in ordinals
    "1", // Sounds like "w_o_n" or "f_i3_r_" when used in ordinals
    "2", // Sounds like "t_o3" or "s_e_k_o_" when used in ordinals
    "3", // Sounds like "th_r_e2" or "th_i3_r_" when used in ordinals
    "4", // Sounds like "f_o2_r" 
    "5", // Sounds like "f_i2_v",
    "6", // Sounds like "s_i_k_s",
    "7", // Sounds like "s_e_v_e_n2",
    "8", // Sounds like "a2_t",
    "9", // Sounds like "n_i2_n", 
    "00", // Sounds like "h_u_n_d_r_e_d"
    "000", // Sounds like "th_o_w_s3_a_n_d" or "th_o_w_z_a_n_d"
    "000_000", // Sounds like "m_i_l_y_o_n"
    "000_000_000", // Sounds like "b_i_l_y_o_n"
    "000_000_000_000", // Sounds like "t_r_i_l_y_o_n"
    
    //Ordinal Sounds
    "_st", // Sounds like "i3_r_s_t", Used exclusively with ordinals that end in 1: 1st, 101st 1001st
    "_nd", // Sounds like "e_k_o_n_d", Used exclusively with ordinals that end in 2: 2nd (2_nd), 102nd (100_2_nd), 1002nd (1_000_2_nd or (1_000_#_2_nd)
    "_rd", // Sounds like "i3_r_d", Used exclusively with ordinals that end in 3: 3rd (3_rd), 103rd (100_3_rd), 1003rd (1_000_3_rd)
    "_th", // Sounds like "e_n_th" in D_N_th, Where D is zero or more digits; and N, is zero or greater than 4, as D_N_th: 100th (100_th), 104th (100_4_th), 4th (4_th), 1004th (1_000_4_th), 106th (100_6_th).
]

// Ex. "oceanographer" >> "o_c_e_a_n_o_g_r_a_p_h_e_r" >> "o2_s_h_e2_a_n_o_g_r_a_f_e_r" >> (IPA phonemes are synthesized in parallel)
*/

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    template<typename T, typename U>
	class nlp_ipa_Dictionary
	{
    public:
        nlp_ipa_Dictionary();
        void GenerateSound(
            FILEINFO_Obj<T, U>& FileInfoObjRefT, 
            const PhoneStruct<U> PhonemeStructReadOnly
            );
        void RepackStream(
            FILEINFO_Obj<T, U>& FileInfoObjRefT
            );
	};
}

