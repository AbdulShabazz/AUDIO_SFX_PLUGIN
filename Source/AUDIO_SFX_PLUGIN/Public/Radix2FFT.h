#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
	template <typename T, typename U>
	class Radix2FFT
	{
	public:
		Radix2FFT();
		void GenerateRadix2FFT(
			FILEINFO_Obj<T,U>&
			);
	private:
		void ApplyRadix2FFTFilter(
			FILEINFO_Obj<T, U>&
			);
	};
}

