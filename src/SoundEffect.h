#pragma once

/*
#ifdef WINDOWS

#include <OPENAL/al.h>
#include <OPENAL/alc.h>

#include "IFileManager.h"
#include "Factory.h"

#pragma pack(push, 1)
struct WavHeader
{
	unsigned char RIFF[4];
	unsigned int Size;
	unsigned char WAVE[4];
	unsigned char FMT[4];
	unsigned int SizeFmt;
	unsigned short FormatTag;
	unsigned short Channels;
	unsigned int SampleRate;
	unsigned int AvgBytesPerSec;
	unsigned short nBlockAlign;
	unsigned short nBitsperSample;
	unsigned char Reserved[4];
	unsigned int DataSize;
};
#pragma pack(pop)

#define DEFAULT_VOLUME 1.0f

class SoundEffect
{
private:
	ALuint sourceID;
	ALuint bufferID;
		
	ALvoid* data;
	size_t dataSize;
	ALsizei frequence = 22050;
	ALenum format;

	void loadFile(string filename);
	ALenum getFormat(WavHeader header);

public:
	void init(string filename);
	
	int getState();

	float getVolume();
	void setVolume(float volume);

	float getPitch();
	void setPitch(float pitch);

	bool isLooping();
	void setLooping(bool inLooping);		

	bool isPlaying();
	bool isStopped();
	bool isPaused();

	void play();	
	void pause();
	void stop();

	~SoundEffect();
};

#endif
*/