#include "AudioManager.h"
#include "Direct3DManager.h"

AudioManager* AudioManager::_instance = nullptr;

void AudioManager::initialize(HWND hWnd)
{ 
	this->hWnd = hWnd;
}

void AudioManager::loadAudio(std::map<std::string, LPTSTR> pathList)
{
	CSound* sound = nullptr;
	soundManager.Initialize(hWnd, DSSCL_PRIORITY);
	for (auto path : pathList)
	{
		auto aaa =  soundManager.Create(&sound, path.second);
		audioList[path.first] = sound;
	}
}

void AudioManager::playAudio(std::string name)
{
	CSound* audio = audioList[name];

	if (audio != nullptr)
	{
		audio->Play();
	}
}

void AudioManager::playAudioLoop(std::string name)
{
	CSound* audio = audioList[name];

	if (audio != nullptr)
	{
		audio->Play(0, DSBPLAY_LOOPING);
	}
}

void AudioManager::stopAudio(std::string name)
{
	CSound* audio = audioList[name];

	if (audio != nullptr)
	{
		audio->Stop();
	}
}

AudioManager::AudioManager()
{
}

AudioManager * AudioManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new AudioManager();
	}

	return _instance;
}

AudioManager::~AudioManager()
{
	/*for (auto sound : audioList)
	{
		delete sound.second;
	}*/
}
