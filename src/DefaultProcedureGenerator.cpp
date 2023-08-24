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

#include "DefaultProcedureGenerator.h"
#include "Finalization.h"
#include "RandomNumber.h"
#include "DefaultOutputMgrProcedure.h"
#include "ExtensionMgr.h"
#include "Type.h"
#include "Function.h"

DefaultProcedureGenerator::DefaultProcedureGenerator(int argc, char* argv[], unsigned long seed)
	:argc_(argc), argv_(argv), seed_(seed), output_mgr_(NULL) {}

DefaultProcedureGenerator::~DefaultProcedureGenerator() {
	Finalization::doFinalization();
	delete output_mgr_;
}

void DefaultProcedureGenerator::initialize() {
	RandomNumber::CreateInstance(rDefaultRndNumGenerator, seed_);
	output_mgr_ = DefaultOutputMgrProcedure::CreateInstance();
	assert(output_mgr_);

	ExtensionMgr::CreateExtension();
}

std::string DefaultProcedureGenerator::get_count_prefix(const std::string&) {
	// I don't know what's the meaning of this
	assert(0);
	return "";
}

void DefaultProcedureGenerator::goGenerator() {
	output_mgr_->OutputHeader(argc_, argv_, seed_);

	GenerateAllTypes();
	GenerateFunctions();
	output_mgr_->Output();
	// Remove currently unused wrapper function
}