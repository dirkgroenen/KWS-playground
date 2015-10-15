#include "SphinxKeywordSpotter.h"
#include <iostream>

using namespace std;

SphinxKeywordSpotter::SphinxKeywordSpotter():
	_ps(nullptr)
{}

SphinxKeywordSpotter::~SphinxKeywordSpotter() {
	// Free PocketSphinx resources
	if(_ps != nullptr) {
		ps_free(_ps);
	}
}

void SphinxKeywordSpotter::initialize(cmd_ln_t* config, const std::string& keywordFileName) {
	// Init pocketsphinx
	_ps = ps_init(config);

	if(_ps == nullptr) {
		throw runtime_error("Call to ps_init returned null");
	}

	// Enable keyword spotting
	if(ps_set_kws(_ps, "keywords", keywordFileName.c_str()) != 0) {
		throw runtime_error("Call to ps_set_kws failed.");
	}

	if(ps_set_search(_ps, "keywords") != 0) {
		throw runtime_error("Call to ps_set_search failed.");
	}

	// Start expecting the first utterance
	ps_start_utt(_ps);
}

std::string SphinxKeywordSpotter::process(std::vector<uint8_t>& buffer) {
	if(_ps == nullptr) {
		throw runtime_error("Initialize must be called before process");
	}

	// Update speech recognition with data from the provided buffer
	ps_process_raw(_ps, (short*)buffer.data(), buffer.size()/2, FALSE, FALSE);

	// Check if a keyword was spotted
	int score = 0;
	const char* hyp = ps_get_hyp(_ps, &score);

	if(hyp != NULL) {
		// Found a keyword. Reset the utterance and return the keyword.
		// First copy the hypothesis to a string because it will be cleared 
		// when we start a new utterance
		string keyword(hyp);

 		// Restart utterance
		ps_end_utt(_ps);
		ps_start_utt(_ps);

		// Return found keyword
		return keyword;
	}

	// No keyword found
	return "";
}

cmd_ln_t* SphinxKeywordSpotter::parseConfig(int argc, char* argv[]) {
	arg_t extra[] = { POCKETSPHINX_OPTIONS, CMDLN_EMPTY_OPTION };
	return cmd_ln_parse_r(NULL, extra, argc, argv, TRUE);
}