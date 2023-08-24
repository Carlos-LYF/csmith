// -*- mode: C++ -*-
// Copyright (c) 2023 Huawei Technology Co.Ltd
// All rights reserved.
//
// This file is part of `gpsmith', a random generator of GaussDB procedures.

// 
// This file is a modification of `csmith'.
// `csmith' is originally used to generate C programs.
//

#if HAVE_CONFIG_H
#	include <config.h>
#endif

#include <cassert>

#include "Common.h"

#include "DefaultOutputMgrProcedure.h"
#include "VariableSelector.h"
#include "Function.h"

#include "platform.h"

using namespace std;

DefaultOutputMgrProcedure* DefaultOutputMgrProcedure::instance_ = NULL;

DefaultOutputMgrProcedure* DefaultOutputMgrProcedure::CreateInstance() {
	if (DefaultOutputMgrProcedure::instance_)
		return DefaultOutputMgrProcedure::instance_;

	DefaultOutputMgrProcedure::instance_ = new DefaultOutputMgrProcedure();
	assert(DefaultOutputMgrProcedure::instance_);
	return DefaultOutputMgrProcedure::instance_;
}

void DefaultOutputMgrProcedure::OutputHeader(unsigned long seed) {
	OutputMgrProcedure::OutputHeader(seed);
}

void DefaultOutputMgrProcedure::Output() {
	std::ostream& out = get_main_out();

	OutputStructUnionDeclarations(out);
	OutputGlobalVariables(out);
	OutputForwardDeclarations(out);
	OutputFunctions(out);

	OutputMain(out);

	OutputTail(out);
}

void DefaultOutputMgrProcedure::outputln(ostream& out) {
	out << endl;
}

std::ostream& DefaultOutputMgrProcedure::get_main_out() {
	return std::cout;
}

DefaultOutputMgrProcedure::DefaultOutputMgrProcedure() {}

DefaultOutputMgrProcedure::~DefaultOutputMgrProcedure() {}