#ifndef ITV_WORDS_H
#define ITV_WORDS_H

#include <sstream>
#include <iterator>
#include "itv_table.h"

using namespace std;

class ITV_Words : public ITV_Table {
	public:
		ITV_Words();
		ITV_Words(std::ifstream &, unsigned int);
		~ITV_Words();

		list<string> get_words(std::string);

		virtual std::string encode(std::string);
		virtual std::string decode(std::string);
		virtual std::string to_string();
};

#endif
