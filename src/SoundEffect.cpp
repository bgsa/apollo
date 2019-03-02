#include "SoundEffect.h"

/*
#ifdef WINDOWS

ALenum SoundEffect::getFormat(WavHeader header)
{
	bool isStereo = header.Channels == 2;
	bool has16bits = header.SizeFmt == 16;

	if (isStereo) 
	{
		if (has16bits)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_STEREO8;
	}
	else 
		if (has16bits)
			return AL_FORMAT_MONO16;
		else
			return AL_FORMAT_MONO8;
}

void SoundEffect::loadFile(string filename) 
{
	WavHeader fileHeader;

	IFileManager* fileManager = Factory::getFileManagerInstance();
	IFile* file = fileManager->open(filename);

	file->read(&fileHeader, sizeof(fileHeader), 1);

	dataSize = fileHeader.DataSize;
	frequence = fileHeader.SampleRate;
	format = getFormat(fileHeader);
	data = malloc(dataSize);

	file->read(data, dataSize, 1);

	delete fileManager;
	delete file;
}

void SoundEffect::init(string filename) 
{	
	loadFile(filename);
	
	alGenBuffers(1, &bufferID);  // generate buffer
	alBufferData(bufferID, format, data, dataSize, frequence); // set buffer content
	delete[] data;

	alGenSources(1, &sourceID);  // generate source
	alSourcei(sourceID, AL_BUFFER, bufferID); // assign the buffer to the source

	setVolume(DEFAULT_VOLUME);
}

float SoundEffect::getPitch()
{
	float pitch;
	alGetSourcef(sourceID, AL_PITCH, &pitch);

	return pitch;
}
void SoundEffect::setPitch(float pitch)
{
	alSourcef(sourceID, AL_PITCH, pitch);
}

bool SoundEffect::isLooping()
{
	int looping;
	alGetSourcei(sourceID, AL_GAIN, &looping);

	return looping == 1;
}
void SoundEffect::setLooping(bool inLooping)
{
	alSourcei(sourceID, AL_LOOPING, inLooping);
}

float SoundEffect::getVolume() 
{
	float volume;
	alGetSourcef(sourceID, AL_GAIN, &volume);

	return volume;
}
void SoundEffect::setVolume(float volume)
{
	alSourcef(sourceID, AL_GAIN, volume);
}

void SoundEffect::play() 
{	
	if (getState() == AL_INITIAL)
		alSourcePlay(sourceID);
}

void SoundEffect::stop()
{
	alSourceStop(sourceID);
}

void SoundEffect::pause()
{
	alSourcePause(sourceID);
}

int SoundEffect::getState()
{
	int currentState;
	alGetSourcei(sourceID, AL_SOURCE_STATE, &currentState);

	return currentState;
}

bool SoundEffect::isPlaying()
{
	return getState() == AL_PLAYING;
}

bool SoundEffect::isStopped()
{
	return getState() == AL_STOPPED;
}

bool SoundEffect::isPaused()
{
	return getState() == AL_PAUSED;
}

SoundEffect::~SoundEffect()
{
	if ( isPlaying() )
		stop();

	alDeleteSources(1, &sourceID);
	alDeleteBuffers(1, &bufferID);
}

#endif
*/