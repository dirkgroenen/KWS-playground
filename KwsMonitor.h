#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "AudioSource.h"
#include "KeywordSpotter.h"

class KwsMonitor {
public:
	KwsMonitor(size_t bufferSize, KeywordSpotter* spotter, AudioSource* audioSource);
	~KwsMonitor();

	void update();

private:
	std::vector<uint8_t> _buffer;
	KeywordSpotter* _spotter;
	AudioSource* _audioSource;
};