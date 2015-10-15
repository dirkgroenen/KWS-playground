#pragma once

#include <stdexcept>
#include <pocketsphinx.h>

#include "KeywordSpotter.h"

class SphinxKeywordSpotter: public KeywordSpotter {
public:
	SphinxKeywordSpotter();
	~SphinxKeywordSpotter();

	// Initialize the keyword spotter with a list of sphinx commands and keywords 
	void initialize(cmd_ln_t* config, const std::string& keywordFileName);

	// Process a buffer of audio to look for the keywords
	virtual std::string process(std::vector<uint8_t>& buffer);

	// Parse the command line params to PocketSphinx's config
	static cmd_ln_t* parseConfig(int argc, char* argv[]);

private:
	ps_decoder_t* _ps;
};