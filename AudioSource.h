#pragma once

#include <cstdint>
#include <memory>
#include <vector>

class AudioSource {
public:
	virtual ~AudioSource() {}

	// Fill the buffer with the audiostream data
	virtual bool record(std::vector<uint8_t>& buffer) = 0;

	// Pause recording audio
	virtual void pause() = 0;

	// Resume recording audio
	virtual void resume() = 0;
};