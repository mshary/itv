#ifndef ITV_UTILS_H
#define ITV_UTILS_H

#include <iostream>
#include <algorithm> 
#include "itv.h"

// trim string from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
};

// trim string from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
};

// trim string from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
};

// random number between min and max values
static inline unsigned int get_random(unsigned int min, unsigned int max) {
	int base_random = rand();
	if (RAND_MAX == base_random) { return get_random(min, max); };
	int range = max - min, remainder = RAND_MAX % range, bucket = RAND_MAX / range;
	if (base_random < RAND_MAX - remainder) {
			return min + base_random/bucket;
	} else {
			return get_random(min, max);
	};
};

static inline bool compare_ids(ITV &first, ITV &second) {
	return (first.get_id() <  second.get_id());
};

static inline bool compare_tags(ITV &first, ITV &second) {
	return (first.get_tag() <  second.get_tag());
};

static inline bool is_symbol(char c) {
	return ((c < 48 || c > 57) && (c < 65 || c > 90) && (c < 97 || c > 122));
};

#endif
