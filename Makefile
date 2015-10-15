OUTPUT = KWS
CXX = g++
CXX_FLAGS = -std=c++11 -Wall -Werror
PROJECT_DIR = .
MODELS_DIR = /usr/local/share/pocketsphinx/model/en-us
SOURCES = KwsMonitor.cpp AlsaSource.cpp SphinxKeywordSpotter.cpp
LIBS = -lpocketsphinx -lsphinxbase -lasound -lsphinxad
INCLUDES = -I/usr/local/include/sphinxbase -I/usr/local/include/pocketsphinx

KWS: $(SOURCES) main.cpp
		$(CXX) $(CXX_FLAGS) $(INCLUDES) $(SOURCES) main.cpp -o $(OUTPUT) $(LIBS)

run: KWS
		./KWS -hmm $(MODELS_DIR)/en-us -dict $(MODELS_DIR)/cmudict-en-us.dict -lm $(MODELS_DIR)/en-us.lm.bin

clean: 
	rm -f *.o
	rm -r $(OUTPUT)