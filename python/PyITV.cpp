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
#include <Python.h>
#include "itv_config.h"
#include "itv_ascii.h"

PyObject* ascii_encode(PyObject *self, PyObject *args) {
	const char *input, *key, sep = ':';
	unsigned char auto_learn = 0;

	if (!PyArg_ParseTuple(args, "scsb", &key, &sep, &input, &auto_learn)) {
		return NULL;
	};

	std::string result, orig_key, ret_key;
	std::string in = std::string(input);
	ITV_ASCII *itv;

	if (key == NULL || strlen(key) <= 1) {
		itv = new ITV_ASCII(32, 126);
		orig_key = itv->dump(sep);
	} else {
		orig_key = std::string(key);
		itv = new ITV_ASCII(orig_key);
	};

	result = itv->encode(in, auto_learn);
	ret_key = itv->dump(sep);

	return Py_BuildValue("sss", orig_key.c_str(), ret_key.c_str(), result.c_str());
};

PyObject* ascii_decode(PyObject *self, PyObject *args) {
	const char *input, *key, sep = ':';
	unsigned char auto_learn = 0;

	if (!PyArg_ParseTuple(args, "scsb", &key, &sep, &input, &auto_learn)) {
		return NULL;
	};

	std::string result, orig_key, ret_key;
	std::string in = std::string(input);
	ITV_ASCII *itv;

	if (key == NULL || strlen(key) <= 1) {
		itv = new ITV_ASCII(32, 126);
		orig_key = itv->dump(sep);
	} else {
		orig_key = std::string(key);
		itv = new ITV_ASCII(orig_key);
	};

	result = itv->decode(in, auto_learn);
	ret_key = itv->dump(sep);

	return Py_BuildValue("sss", orig_key.c_str(), ret_key.c_str(), result.c_str());
};

PyMethodDef ITV_methods[] = {
	{ "ascii_encode", ascii_encode, METH_VARARGS, "Encrypts string using ITV algorithm with given key" }, 
	{ "ascii_decode", ascii_decode, METH_VARARGS, "Decrypts string using ITV algorithm with given key" }, 
	{ NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC inititv(void) {
	(void) Py_InitModule("itv", ITV_methods);
};
