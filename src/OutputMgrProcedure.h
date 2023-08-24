// -*- mode: C++ -*-
// Copyright (c) 2023 Huawei Technology Co.Ltd
// All rights reserved.
//
// This file is part of `gpsmith', a random generator of GaussDB procedures.

// 
// This file is a modification of `csmith'.
// `csmith' is originally used to generate C programs.
//

#ifndef OUTPUT_MGR_PROCEDURE_H
#define OUTPUT_MGR_PROCEDURE_H

#include <ostream>
using namespace std;

#define TAB "    "	// Convert tabs to spaces so output is always beautiful

class OutputMgrProcedure {
public:
	OutputMgrProcedure();

	virtual ~OutputMgrProcedure() = 0;

	virtual void OutputHeader(int argc, char* argv[], unsigned long seed) = 0;

	virtual void Output() = 0;

	virtual void outputln(ostream& out) { out << std::endl; }

	virtual void output_comment_line(ostream& out, const std::string& comment);

	virtual void output_tab(ostream& out, int indent);

protected:
	virtual std::ostream& get_main_out() = 0;

	static void output_tab_(ostream& out, int indent);

	void OutputMain(std::ostream& out);

	void OutputTail(std::ostream& out);
};

#endif