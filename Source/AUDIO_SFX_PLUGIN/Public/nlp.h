#pragma once

#include <unordered_map>
#include <complex>
#include <vector>

namespace ToneLibrary
{
	enum class TONE_ENUM
	{ 		defaultEnum = 0, afortioriEnum, abackEnum, abjectlyEnum, ablyEnum, abortivelyEnum, aboveboardEnum, abruptlyEnum, absentlyEnum,		absentmindedlyEnum, absolutelyEnum, abstemiouslyEnum, abstruselyEnum, academicallyEnum, accusinglyEnum, ad_hocEnum, ad_libEnum,
		ad_valoremEnum, adagioEnum, adamantlyEnum, additionallyEnum, adjectivallyEnum, adjectivelyEnum, admirablyEnum, admiringlyEnum,
		admittedlyEnum, adorablyEnum, adoringlyEnum, adroitlyEnum, advisedlyEnum, affablyEnum, affectedlyEnum, affectinglyEnum, affectionatelyEnum,
		affirmativelyEnum, after_allEnum, again_and_againEnum, against_the_clockEnum, against_the_windEnum, against_timeEnum, aggravatinglyEnum,
		aggressivelyEnum, agilelyEnum, agonizinglyEnum, agreeablyEnum, ahead_of_the_gameEnum, ahead_of_timeEnum, aimlesslyEnum, airilyEnum, akimboEnum,
		alarminglyEnum, alasEnum, aleeEnum, alertlyEnum, alfrescoEnum, all_fireEnum, all_alongEnum, all_at_onceEnum, all_day_longEnum, all_in_allEnum,
		all_of_a_suddenEnum, all_the_sameEnum, all_the_wayEnum, all_togetherEnum, allegedlyEnum, allegrettoEnum, allegroEnum, alliterativelyEnum, allowablyEnum,
		aloftEnum, aloofEnum, aloudEnum, alphabeticallyEnum, alternatelyEnum, alternativelyEnum, altogetherEnum, altruisticallyEnum, alwaysEnum, amateurishlyEnum,
		ambitiouslyEnum, amiablyEnum, amidshipEnum, amissEnum, amorallyEnum, amorouslyEnum, amplyEnum, amuckEnum, amusinglyEnum, anachronisticallyEnum,
		analyticallyEnum, anarchicallyEnum, ancientlyEnum, and_soEnum, and_so_forthEnum, and_so_onEnum, and_then_someEnum, andanteEnum, angelicallyEnum,
		angrilyEnum, animatedlyEnum, annoyinglyEnum, anomalouslyEnum, anonEnum, anonymouslyEnum, antagonisticallyEnum, antitheticallyEnum, anxiouslyEnum,
		any_longerEnum, anywayEnum, anywhereEnum, apaceEnum, apatheticallyEnum, apologeticallyEnum, appallinglyEnum, appealinglyEnum, appreciablyEnum, appreciativelyEnum,
		appropriatelyEnum, approvinglyEnum, approximatelyEnum, aproposEnum, aptlyEnum, arbitrarilyEnum, ardentlyEnum, arduouslyEnum, arguablyEnum, argumentativelyEnum, 
		arightEnum, aristocraticallyEnum, arrogantlyEnum, artfullyEnum, articulatelyEnum, artificiallyEnum, artisticallyEnum, artlesslyEnum, as_a_groupEnum,
		as_a_matter_of_factEnum, as_far_as_possibleEnum, as_if_by_magicEnum, as_it_isEnum, as_it_wereEnum, as_luck_would_have_itEnum, as_much_as_possibleEnum,
		as_neededEnum, as_requiredEnum, as_the_crow_fliesEnum, as_usualEnum, as_we_sayEnum, as_yetEnum, asapEnum, asceticallyEnum, asexuallyEnum, ashamedlyEnum,
		asideEnum, askanceEnum, askewEnum, aslantEnum, asleepEnum, assertivelyEnum, assiduouslyEnum, assuredlyEnum, asternEnum, astonishinglyEnum, astraddleEnum,
		astronomicallyEnum, astutelyEnum, asunderEnum, at_a_lossEnum, at_all_costsEnum, at_any_costEnum, at_any_expenseEnum, at_first_blushEnum, at_first_glanceEnum,
		at_first_sightEnum, at_heart, at_homeEnum, at_lastEnum, at_long_lastEnum, at_onceEnum, at_presentEnum, at_randomEnum, at_stakeEnum, at_the_leastEnum,
		at_the_mostEnum, at_the_same_timeEnum, at_the_worstEnum, at_timesEnum, at_willEnum, at_worstEnum, athwartEnum, atonallyEnum, atrociouslyEnum, attentivelyEnum,
		attractivelyEnum, attributivelyEnum, atypicallyEnum, audaciouslyEnum, audiblyEnum, aurallyEnum, auspiciouslyEnum, austerelyEnum, authenticallyEnum, authoritativelyEnum,
		autocraticallyEnum, automaticallyEnum, avariciouslyEnum, avidlyEnum, avowedlyEnum, awkwardlyEnum, awryEnum, axiomaticallyEnum,

		CynicalEnum,
		DubiousEnum,
	};

	template<typename T, typename U>
	struct PHONEME_STRUCT
	{
		U InFrom;
		U OutTo;
		TONE_ENUM ToneDeliveryEnum;
		Vector2DT<T> BufferVector2DT;
		ComplexVector2DT<T> BufferComplexVector2DT;
	};

	template<typename T, typename U>
	class nlp_phoneme
	{
	public:
		nlp_phoneme();
		void tts_generate(PHONEME_STRUCT<T, U>&);
	};

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
		void nlp_ParallelHiddenMarkov_tts();
		void nlp_SerialHiddenMarkov_tts();

		template<typename T>
		static std::unordered_map<std::string, class nlp_phoneme<T, U>&> nlp_phoneme_hash;
	};

}
