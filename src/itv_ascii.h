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
		virtual ~ITV_ASCII();

		void load(std::ifstream &);
		void save(std::ofstream &);
		void load_ascii_table(enum type);

		virtual std::string encode(std::string);
		virtual std::string decode(std::string);
		virtual std::string to_string();
};

#endif
