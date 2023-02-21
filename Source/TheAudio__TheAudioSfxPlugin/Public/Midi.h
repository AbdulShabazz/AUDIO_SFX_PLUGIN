#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
	template <typename T, typename U>
	class Midi
	{
	public:
		Midi();
	   ~Midi();
		void MidiInPort(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void MidiInPortOpen(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void MidiInPortClose(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void MidiInPortReset(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void MidiInPortStart(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void MidiInPortStop(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void SetMidiInPort(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void MidiOutPort(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void MidiOutPortOpen(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void MidiOutPortClose(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void SetMidiOutPort(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void MidiMessage(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void NoteOn(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void NoteOff(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void ChannelPressure(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void PitchBend(FILEINFO_Obj<T, U>& FileInfo_ObjRef); 
		void PitchBendChange(FILEINFO_Obj<T, U>& FileInfo_ObjRef); 
		void PolyphonicKeyPressure(FILEINFO_Obj<T, U>& FileInfo_ObjRef); 
		void ControlChange(FILEINFO_Obj<T, U>& FileInfo_ObjRef); 
		void ProgramChange(FILEINFO_Obj<T, U>& FileInfo_ObjRef); 
		void SystemExclusive(FILEINFO_Obj<T, U>& FileInfo_ObjRef); 
		void SystemCommon(FILEINFO_Obj<T, U>& FileInfo_ObjRef); 
		void SystemRealTime(FILEINFO_Obj<T, U>& FileInfo_ObjRef); 
		void StartSession(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void StopSession(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
		void EndSession(FILEINFO_Obj<T, U>& FileInfo_ObjRef);
	};
}