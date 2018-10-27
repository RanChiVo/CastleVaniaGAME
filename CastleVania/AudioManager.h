#pragma once
#include <Windows.h>
#include <map>
#include <string>

#include "Library/DSUtil.h"

class AudioManager
{
private:
	static AudioManager* _instance;
	std::map<std::string, CSound*> audioList;
	CSoundManager soundManager;
	HWND hWnd;
	AudioManager();

public:

	void initialize(HWND hWnd);

	void loadAudio(std::map<std::string, LPTSTR>);
	
	void playAudio(std::string name);
	void playAudioLoop(std::string name);
	void stopAudio(std::string name);
	
	static AudioManager* getInstance();
	~AudioManager();
};

