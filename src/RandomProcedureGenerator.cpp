// -*- mode: C++ -*-
// Copyright (c) 2023 Huawei Technology Co.Ltd
// All rights reserved.
//
// This file is part of `gpsmith', a random generator of GaussDB procedures.

// 
// This file is a modification of `csmith'.
// `csmith' is originally used to generate C programs.
//

/*
Random GaussDB Procedure Generator
----------------------------------
I don't know what to write here now.
Maybe I'll write something when stars align.
*/

#if HAVE_CONFIG_H
#	include <config.h>
#endif

#include "Common.h"

#include "CGOptions.h"
#include "AbsProcedureGenerator.h"

#include "platform.h"

#ifdef WIN32
#pragma warning(disable : 4786)	/* This warning is disabled in `csmith', so I do the same */
#endif

using namespace std;	/* Rickey Liang told me not to use std in real work, but I hate him */

// Program seed - not many use now because I remove the useless function of manually setting seed
static unsigned long g_Seed = 0;

int main(int argc, char** argv) {
	g_Seed = platform_gen_seed();

	CGOptions::set_default_settings();

	cout << "-- modified csmith for generating GaussDB procedures" << std::endl << std::endl;

	// Currently this program process no command line argument
	if (argc > 1) {
		cerr << "error: no argument supported!" << std::endl;
		exit(-1);
	}

	AbsProcedureGenerator* generator = AbsProcedureGenerator::CreateInstance(argc, argv, g_Seed);
	if (!generator) {
		cerr << "error: can't create generator!" << std::endl;
		exit(-1);
	}
	generator->goGenerator();
	delete generator;

	return 0;
}