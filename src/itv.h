#ifndef ITV_H
#define ITV_H

#include <iostream>
#include <sstream>
#include <string>

#define ITV_SEPARATOR "\t"
#define ITV_TERMINATOR "\n"

using namespace std;

class ITV {
	friend ostream &operator << (ostream &, const ITV &);
	friend istream &operator >> (istream &, ITV &);

	protected:
		unsigned int id;
		unsigned int tag;
		std::string value;

	public:
		ITV();
		ITV(const ITV &);
		ITV(unsigned int, std::string);
		ITV(unsigned int, unsigned int, std::string);
		~ITV();

		ITV &operator = (const ITV &);
		int operator == (const ITV &) const;
		int operator != (const ITV &) const;
		int operator <= (const ITV &) const;
		int operator >= (const ITV &) const;
		int operator  < (const ITV &) const;
		int operator  > (const ITV &) const;

		unsigned int replace(unsigned int);

		unsigned int get_id();
		void set_id(unsigned int);

		unsigned int get_tag();
		void set_tag(unsigned int);

		std::string get_value();
		void set_value(std::string);

		void clear();
		void restore();

		std::string to_string();
};

#endif
