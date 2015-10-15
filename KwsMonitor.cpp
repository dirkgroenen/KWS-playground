#include "KwsMonitor.h"

#include <iostream>
#include <unistd.h>

using namespace std;

KwsMonitor::KwsMonitor(size_t bufferSize, KeywordSpotter* spotter, AudioSource* audioSource): _buffer(bufferSize), _spotter(spotter), _audioSource(audioSource) {}

KwsMonitor::~KwsMonitor() {}

void KwsMonitor::update() {
	// Grab a buffer of audio
	if(_audioSource->record(_buffer)) {
		// Look for the keyword
		string keyword = _spotter->process(_buffer);

		if(keyword != "") {
			// Keyword was spotted, notify
			cout << "Keyword spotted: " << keyword << endl;
		}
	}
	else {
		// There's a problem gettin data from the microphone
		// Raise error and try again
		cerr << "Failed to get audio from the microphone" << endl;
	}
}