#pragma once

#include <stdexcept>
#include <string>

#include <alsa/asoundlib.h>

class AlsaError: public std::runtime_error {
public:
	AlsaError(const std::string& what, const int code): std::runtime_error(what), code(code) {
		message = snd_strerror(code);
	}

	const int code;
	const char* message;
};

#define ALSA_THROW(call) \
{ \
	int code = call; \
	if(code < 0) throw AlsaError(#call, code); \
}
