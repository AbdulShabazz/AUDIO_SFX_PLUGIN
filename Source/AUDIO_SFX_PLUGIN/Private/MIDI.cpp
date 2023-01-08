#include "MIDI.h"

using namespace ToneLibrary;

template<typename T, typename U>
MIDI<T,U>::MIDI() 
{

}

template<typename T, typename U>
void MIDI<T, U>::MidiInPort(
	FILEINFO_Obj<T, U>& FileInfo_ObjRef
	)
{

}

template<typename T, typename U>
void MIDI<T, U>::MidiOutPort(
	FILEINFO_Obj<T, U>& FileInfo_ObjRef
	)
{

}

template<typename T, typename U>
void MIDI<T, U>::StartSession(
	FILEINFO_Obj<T, U>& FileInfo_ObjRef
	)
{

}

template<typename T, typename U>
void MIDI<T, U>::MidiMessage(
	FILEINFO_Obj<T, U>& FileInfo_ObjRef
	)
{

}

template<typename T, typename U>
void MIDI<T, U>::NoteOn(
	FILEINFO_Obj<T,U>& FileInfo_ObjRef
	)
{

	/*std::string NoteNameStr,
	T VelocityFloat64T,
	U ChannelPressureUInt64T = 1,
	U PolyphonicKeyPressure = 1*/


	/* or
	U ControlNumberUInt64T,
	T VelocityFloat64T,
	U ChannelPressureUInt64T = 1,
	U PolyphonicKeyPressure = 1*/
	
	/* or
	T FrequencyFloat64T,
	T VelocityFloat64T,
	U ChannelPressureUInt64T = 1,
	U PolyphonicKeyPressure = 1*/

}

template<typename T, typename U>
void MIDI<T, U>::ChannelPressure(
	FILEINFO_Obj<T, U>& FileInfo_ObjRef
	)
{
	//U ChannelPressureUInt64T
}

template<typename T, typename U>
void MIDI<T, U>::PitchBendChange(
	FILEINFO_Obj<T, U>& FileInfo_ObjRef
	)
{
	//T PitchBendChange
}

template<typename T, typename U>
void MIDI<T, U>::PolyphonicKeyPressure(
	FILEINFO_Obj<T, U>& FileInfo_ObjRef
	)
{
	//U PolyphonicKeyPressure
}

template<typename T, typename U>
void MIDI<T, U>::ControlChange(
FILEINFO_Obj<T, U>& FileInfo_ObjRef
	)
{
	//U ControlChangeUInt64
}

template<typename T, typename U>
void MIDI<T, U>::NoteOff(
	FILEINFO_Obj<T, U>& FileInfo_ObjRef
	)
{
	//std::string NoteNameStr, or
	//T FrequencyFloat64T +

	//U ControlNumberUInt64T

}

template<typename T, typename U>
void MIDI<T, U>::StopSession(
	FILEINFO_Obj<T, U>& FileInfo_ObjRef
	)
{

}