// -*- mode: C++ -*-
// Copyright (c) 2023 Huawei Technology Co.Ltd
// All rights reserved.
//
// This file is part of `gpsmith', a random generator of GaussDB procedures.

// 
// This file is a modification of `csmith'.
// `csmith' is originally used to generate C programs.
//

#ifndef ABS_PROCEDURE_GENERATOR_H
#define ABS_PROCEDURE_GENERATOR_H

#include <string>

class OutputMgr;

class AbsProcedureGenerator {
public:
	static AbsProcedureGenerator* CreateInstance(int argc, char* argv[], unsigned long seed);

	static AbsProcedureGenerator* GetInstance();

	AbsProcedureGenerator();

	virtual ~AbsProcedureGenerator();

	static OutputMgr* GetOutputMgr();

	virtual void goGenerator() = 0;

	virtual OutputMgr* getOutputMgr() = 0;

	virtual std::string get_count_prefix(const std::string& name) = 0;

protected:
	virtual void initialize() = 0;

private:
	static AbsProcedureGenerator* current_generator_;

	static OutputMgr* getmgr(AbsProcedureGenerator* gen);
};

#endif