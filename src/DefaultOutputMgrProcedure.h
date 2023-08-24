// -*- mode: C++ -*-
// Copyright (c) 2023 Huawei Technology Co.Ltd
// All rights reserved.
//
// This file is part of `gpsmith', a random generator of GaussDB procedures.

// 
// This file is a modification of `csmith'.
// `csmith' is originally used to generate C programs.
//

#ifndef DEFAULT_OUTPUT_MGR_PROCEDURE_H
#define DEFAULT_OUTPUT_MGR_PROCEDURE_H

#include "OutputMgrProcedure.h"

class DefaultOutputMgrProcedure :public OutputMgrProcedure {
public:
	static DefaultOutputMgrProcedure* CreateInstance();

	virtual ~DefaultOutputMgrProcedure();

	virtual void OutputHeader(unsigned long seed);

	virtual void Output();

	virtual void outputln(ostream& out);

private:
	explicit DefaultOutputMgrProcedure();

	static DefaultOutputMgrProcedure* instance_;

	virtual std::ostream& get_main_out();
};

#endif