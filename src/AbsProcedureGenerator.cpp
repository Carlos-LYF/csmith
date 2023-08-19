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

#include "AbsProcedureGenerator.h"
#include "DefaultProcedureGenerator.h"
#include "CGOptions.h"
#include "Probabilities.h"

using namespace std;

AbsProcedureGenerator* AbsProcedureGenerator::current_generator_ = NULL;

OutputMgr* AbsProcedureGenerator::GetOutputMgr() {
	assert(current_generator_);
	return current_generator_->getOutputMgr();
}

AbsProcedureGenerator* AbsProcedureGenerator::CreateInstance(int argc, char* argv[], unsigned long seed) {
	// Remove some currently not supported config
	AbsProcedureGenerator::current_generator_ = new DefaultProcedureGenerator(argc, argv, seed);

	AbsProcedureGenerator::current_generator_->initialize();

	return AbsProcedureGenerator::current_generator_;
}

AbsProcedureGenerator* AbsProcedureGenerator::GetInstance() {
	assert(AbsProcedureGenerator::current_generator_);
	return AbsProcedureGenerator::current_generator_;
}

AbsProcedureGenerator::AbsProcedureGenerator() {}

AbsProcedureGenerator::~AbsProcedureGenerator() {}