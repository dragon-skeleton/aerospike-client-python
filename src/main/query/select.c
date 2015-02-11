/*******************************************************************************
 * Copyright 2013-2014 Aerospike, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#include <Python.h>
#include <stdbool.h>

#include <aerospike/as_query.h>

#include "client.h"
#include "query.h"

#undef TRACE
#define TRACE()

AerospikeQuery * AerospikeQuery_Select(AerospikeQuery * self, PyObject * args, PyObject * kwds)
{
	TRACE();

	int nbins = (int) PyTuple_Size(args);
	char * bin = NULL;
	PyObject * py_ustr = NULL;

	as_query_select_init(&self->query, nbins);

	for ( int i = 0; i < nbins; i++ ) {
		PyObject * py_bin = PyTuple_GetItem(args, i);
		if (py_bin) {
			if (PyUnicode_Check(py_bin)) {
				py_ustr = PyUnicode_AsUTF8String(py_bin);
				bin = PyString_AsString(py_ustr);
			} else if (PyString_Check(py_bin)) {
				bin = PyString_AsString(py_bin);
			}
		} else {
			// TRACE();
		}
		as_query_select(&self->query, bin);
	}

	if (py_ustr) {
		Py_DECREF(py_ustr);
	}

	Py_INCREF(self);
	return self;
}
