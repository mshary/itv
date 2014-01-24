#ifndef ITV_TABLE_H
#define ITV_TABLE_H

#include <iostream>
#include <fstream>
#include <list>

#include "itv.h"
#include "itv_utils.h"

using namespace std;

class ITV_Table {
	friend ostream &operator << (ostream &, const ITV_Table &);

	protected:
		unsigned int min_id;
		list<ITV> *table;

	public:
		ITV_Table();
		ITV_Table(list<ITV>*);
		ITV_Table(std::ifstream &, unsigned int);
		~ITV_Table();

		ITV_Table &operator = (const ITV_Table &);
		int operator == (const ITV_Table &) const;
		int operator != (const ITV_Table &) const;
		int operator <= (const ITV_Table &) const;
		int operator >= (const ITV_Table &) const;
		int operator  < (const ITV_Table &) const;
		int operator  > (const ITV_Table &) const;

		list<ITV>* get_table();
		void set_table(list<ITV>*);

		void add(ITV*);
		int remove(ITV*);
		int exists(ITV*);

		ITV* find_by_id(unsigned int, bool);
		ITV* find_by_tag(unsigned int, bool);
		ITV* find_by_value(std::string, bool);

		unsigned int* convert(std::string, unsigned int);
		std::string revert(unsigned int, unsigned int);

		void clear();
		void restore();

		unsigned int get_random_id();

		void load(std::ifstream &);
		void save(std::ofstream &);

		virtual std::string encode(std::string) = 0;
		virtual std::string decode(std::string) = 0;
		virtual std::string to_string() = 0;
};

#endif
