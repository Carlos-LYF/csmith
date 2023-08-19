// -*- mode: C++ -*-
// Copyright (c) 2023 Huawei Technology Co.Ltd
// All rights reserved.
//
// This file is part of `gpsmith', a random generator of GaussDB procedures.

// 
// This file is a modification of `csmith'.
// `csmith' is originally used to generate C programs.
//

#ifndef DEFAULT_PROGRAM_GENERATOR_H
#define DEFAULT_PROGRAM_GENERATOR_H

#include "AbsProcedureGenerator.h"

class OutputMgr;

class DefaultProcedureGenerator :public AbsProcedureGenerator {
public:
	DefaultProcedureGenerator(int argc, char* argv[], unsigned long seed);

	virtual ~DefaultProcedureGenerator();

	virtual OutputMgr* getOutputMgr() { return output_mgr_; }

	virtual void goGenerator();

	virtual void initialize();

	virtual std::string get_count_prefix(const std::string& name);

private:
	int argc_;

	char** argv_;

	unsigned long seed_;

	OutputMgr* output_mgr_;
};

#endif