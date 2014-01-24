#ifndef ITV_ASCII_H
#define ITV_ASCII_H

#include "itv_table.h"

#define WORD_SEPARATOR 32

using namespace std;

class ITV_ASCII : public ITV_Table {
	public:
		enum type {
			ASCII_PRINTABLE,
			ASCII_ALPHANUMERIC,
			ASCII_ALPHABET,
			ASCII_NUMERIC,
			ASCII_OTHER
		} t;

		ITV_ASCII();
		ITV_ASCII(enum type);
		ITV_ASCII(std::ifstream &);
		~ITV_ASCII();

		void load(std::ifstream &);
		void save(std::ofstream &);
		void load_ascii_table(enum type);

		virtual std::string encode(std::string);
		virtual std::string decode(std::string);
		virtual std::string to_string();
};

#endif
