#pragma once

#include <cstdint>
#include <string>
#include <vector>

class KeywordSpotter {
public:
	virtual ~KeywordSpotter() {}

	virtual std::string process(std::vector<uint8_t>& buffer) = 0;
};