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

static const char runtime_include[] = "\
#include \"csmith.h\"\n\
";

void OutputMgrProcedure::OutputHeader(int argc, char* argv[], unsigned long seed) {
	std::ostream& out = get_main_out();

	out << "/*" << endl;
	out << " * This is a RANDOMLY GENERATED PL\/SQL PROCEDURE." << endl;
	out << " *" << endl;
	out << " * Generator: " << PACKAGE_STRING << endl;
	out << " * Git version: " << git_version << endl;
	out << " * Options:  ";
	if (argc <= 1) {
		out << " (none)";
	}
	else {
		for (int i = 1; i < argc; ++i) {
			out << " " << argv[i];
		}
	}
	out << endl;
	out << " * Seed: " << seed << endl;
	out << " */" << endl;
	out << endl;

	ExtensionMgr::OutputHeader(out);

	out << runtime_include << endl;

	out << endl;

	out << "static long __undefined;" << endl;
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

	out << "    int print_hash_value = 0;" << endl;
	out << "    if (argc == 2 && strcmp(argv[1], \"1\") == 0) print_hash_value = 1;" << endl;
	out << "    platform_main_begin();" << endl;
	out << "    crc32_gentab();" << endl;
	ExtensionMgr::OutputFirstFunInvocation(out, invoke);
	HashGlobalVariables(out);
	out << "    platform_main_end(crc32_context ^ 0xFFFFFFFFUL, print_hash_value);" << endl;

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
	out << "/* " << comment << "*/";
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