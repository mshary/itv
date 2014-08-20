/*
 * Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted per Mozilla Public License v2.0.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef ITV_TABLE_H
#define ITV_TABLE_H

#include "itv_config.h"

using namespace std;

class ITV_Table {
	friend ostream &operator << (ostream &, const ITV_Table &);

	protected:
		size_t min_id;
		list<ITV> *table;

	public:
		ITV_Table();
		ITV_Table(list<ITV> &);
		virtual ~ITV_Table();

		ITV_Table &operator = (const ITV_Table &);
		bool operator == (const ITV_Table &) const;
		bool operator != (const ITV_Table &) const;
		bool operator <= (const ITV_Table &) const;
		bool operator >= (const ITV_Table &) const;
		bool operator  < (const ITV_Table &) const;
		bool operator  > (const ITV_Table &) const;

		const list<ITV>* get_table();
		void set_table(const list<ITV>&);

		bool add(const ITV&);
		bool remove(const ITV&);
		bool exists(const ITV&);

		ITV* find_by_id(size_t, bool);
		ITV* find_by_tag(size_t, bool);
		ITV* find_by_value(const std::string&, bool);

		size_t* convert(const std::string&, size_t);
		const std::string revert(size_t, size_t);

		void clear();
		void restore();

		size_t get_random_id();
		size_t get_random(size_t, size_t);

		virtual size_t read(const std::string&) = 0;
		virtual size_t write(const std::string&) = 0;

		virtual const std::string& encode(std::string&) = 0;
		virtual const std::string& decode(std::string&) = 0;
		virtual const std::string to_string() = 0;
};

#endif
