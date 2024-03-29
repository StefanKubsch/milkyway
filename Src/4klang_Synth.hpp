#include "mmsystem.h"
#include "mmreg.h"

// Load 4klang-generated header file
#include "4klang/4klang.h"

WAVEFORMATEX WaveFMT
{
	#ifdef FLOAT_32BIT
		WAVE_FORMAT_IEEE_FLOAT,
	#else
		WAVE_FORMAT_PCM,
	#endif
	2,											// channels
	SAMPLE_RATE,								// samples per sec
	SAMPLE_RATE * sizeof(SAMPLE_TYPE) * 2,		// bytes per sec
	sizeof(SAMPLE_TYPE) * 2,					// block alignment
	sizeof(SAMPLE_TYPE) * 8,					// bits per sample
	0											// no extension
};

SAMPLE_TYPE AudioBuffer[MAX_SAMPLES * 2];
HWAVEOUT WaveOut{};
WAVEHDR WaveHDR{ reinterpret_cast<LPSTR>(AudioBuffer), MAX_SAMPLES * sizeof(SAMPLE_TYPE) * 2, 0, (DWORD_PTR)NULL, 0, 0, nullptr, (DWORD_PTR)NULL };
MMTIME MMTime{ TIME_SAMPLES, 0 };

void InitSynth()
{
	_4klang_render(AudioBuffer);
	waveOutOpen(&WaveOut, WAVE_MAPPER, &WaveFMT, (DWORD_PTR)NULL, 0, CALLBACK_NULL);
	waveOutPrepareHeader(WaveOut, &WaveHDR, sizeof(WaveHDR));
	waveOutWrite(WaveOut, &WaveHDR, sizeof(WaveHDR));
}