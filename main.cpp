#include <stdbool.h>
#include <csignal>
#include <stdio.h>
#include <stdexcept>
#include <iostream>

#include "SphinxKeywordSpotter.h"
#include "KwsMonitor.h"
#include "AlsaSource.h"

using namespace std;

#define KEYWORD_FILE	"keywords.txt"
#define RECORD_HW		"plughw:1,0"

bool should_run = true;

int main(int argc, char* argv[]){

	try{

		signal(SIGINT, [](int param){
			should_run = false;
		});

		printf("Listening... Press CTRL-C to stop me.\n");

		// Initialize audio source
		AlsaSource source;
		source.open(RECORD_HW, 16000, 1, SND_PCM_FORMAT_S16_LE);

		// Initialize the Sphinx keyword spotter
		SphinxKeywordSpotter spotter;
		spotter.initialize( SphinxKeywordSpotter::parseConfig(argc, argv), KEYWORD_FILE );

		// Initialize the monitor
		KwsMonitor monitor(8000, &spotter, &source);

		while(should_run){
			monitor.update();
		}
	}
	catch(AlsaError ex) {
		cerr << "ALSA Error: " << ex.message << " (" << ex.code << ") while calling: " << ex.what() << endl;
	}
	catch(exception ex) {
		cerr << "Exception: " << ex.what() << endl;
		return 1;
	}

	return 0;
}