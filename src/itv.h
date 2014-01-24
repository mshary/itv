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
