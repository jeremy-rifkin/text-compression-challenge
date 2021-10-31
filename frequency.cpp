#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>

// frequency table generator from ngram data

const auto source = "data/ngrams.txt";

static std::vector<std::string> split(std::string_view s, std::string_view delims) {
	std::vector<std::string> vec;
	size_t old_pos = 0;
	size_t pos = 0;
	std::string token;
	while((pos = s.find_first_of(delims, old_pos)) != std::string::npos) {
			token = s.substr(old_pos, pos - old_pos);
			vec.push_back(token);
			old_pos = pos + 1;
	}
	vec.push_back(std::string(s.substr(old_pos)));
	return vec;
}

int char_to_i(char c) {
	if(c == ' ') {
		return 26;
	} else {
		c = c - 'a';
		assert(c >= 0);
		assert(c <= 25);
		return c;
	}
}

int main() {
	// conditional probability table
	// indices 0-25 are letters, 26 is null terminator / space
	double tables[27][27] = {};
	std::ifstream file(source);
	while(true) {
		std::string word;
		double f;
		int a;
		unsigned long long b;
		if(!(file>>word)) break;
		file>>f>>a>>b;
		int last = 26;
		for(char c : word) {
			if(!isalpha(c)) continue;
			int i = char_to_i(tolower(c));
			tables[last][i] += f;
			last = i;
		}
		tables[last][26] += f;
	}
	std::cout<<"{"<<std::endl;
	for(auto& table : tables) {
		std::cout<<"    { ";
		for(auto f : table) {
			std::cout<<f<<", ";
		}
		std::cout<<"},"<<std::endl;
	}
	std::cout<<"};"<<std::endl;
}
