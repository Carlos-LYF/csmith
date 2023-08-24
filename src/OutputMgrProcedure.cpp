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

#include <sstream>

#include "OutputMgrProcedure.h"
#include "Bookkeeper.h"
#include "CGContext.h"
#include "Function.h"
#include "FunctionInvocation.h"
#include "ExtensionMgr.h"
#include "VariableSelector.h"

#include "git_version.h"

void OutputMgrProcedure::OutputHeader(unsigned long seed) {
	std::ostream& out = get_main_out();

	out << "/*" << endl;
	out << " * This is a RANDOMLY GENERATED PL\\SQL PROCEDURE." << endl;
	out << " *" << endl;
	out << " * Generator: " << PACKAGE_STRING << endl;
	out << " * Git version: " << git_version << endl;
	out << " * Seed: " << seed << endl;
	out << " */" << endl;
	out << endl;
}

void OutputMgrProcedure::OutputMain(std::ostream& out) {
	CGContext cg_context(GetFirstFunction(), Effect::get_empty_effect(), 0);

	FunctionInvocation* invoke = NULL;
	invoke = ExtensionMgr::MakeFuncInvocation(GetFirstFunction(), cg_context);
	out << endl << endl;
	output_comment_line(out, "----------------------------------------");

	ExtensionMgr::OutputInit(out);

	OutputArrayInitializers(*VariableSelector::GetGlobalVariables(), out, 1);

	ExtensionMgr::OutputFirstFunInvocation(out, invoke);
	std::vector<Variable*>& vars = *VariableSelector::GetGlobalVariables();
	for (size_t i = 0; i < vars.size(); i++) {
		vars[i]->output_value_dump(out, "checksum ", 1);
	}

	ExtensionMgr::OutputTail(out);
	out << "}" << endl;
	delete invoke;
}

void OutputMgrProcedure::OutputTail(std::ostream& out) {
	out << endl << "/************************ statistics *************************" << endl;
	Bookkeeper::output_statistics(out);
	out << "********************* end of statistics **********************/" << endl;
	out << endl;
}

void OutputMgrProcedure::output_comment_line(ostream& out, const std::string& comment) {
	out << "-- " << comment;
	outputln(out);
}

void OutputMgrProcedure::output_tab_(ostream& out, int indent) {
	while (indent--) {
		out << TAB;
	}
}

void OutputMgrProcedure::output_tab(ostream& out, int indent) {
	OutputMgrProcedure::output_tab_(out, indent);
}

OutputMgrProcedure::OutputMgrProcedure() {}

OutputMgrProcedure::~OutputMgrProcedure() {}