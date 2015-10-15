#pragma once

#include <stdexcept>
#include <alsa/asoundlib.h>

#include "AlsaError.h"
#include "AudioSource.h"

class AlsaSource : public AudioSource {
public:
	AlsaSource();
	~AlsaSource();

	void open(const std::string& hw, const int rate, const int channels, const snd_pcm_format_t format);
	virtual bool record(std::vector<uint8_t>& buffer);
	virtual void pause();
	virtual void resume();

private:
	snd_pcm_t* _device;
	size_t _formatSize;
};