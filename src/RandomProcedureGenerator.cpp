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

#include <cstring>

#include "Common.h"

#include "CGOptions.h"
#include "AbsProcedureGenerator.h"

#include "git_version.h"
#include "platform.h"

#ifdef WIN32
#pragma warning(disable : 4786)	/* This warning is disabled in `csmith', so I do the same */
#endif

using namespace std;	/* Rickey Liang told me not to use std in real work, but I hate him */

// Program seed - seed can be manually set to reproduce the same procedure
static unsigned long g_Seed = 0;

static void print_version() {
	cout << PACKAGE_STRING << endl;
	cout << "Git version: " << git_version << endl;
}

void arg_check(int argc, int i) {
	if (i >= argc) {
		cerr << "expect arg at pos " << i << std::endl;
		exit(-1);
	}
}

static bool parse_int_arg(char* arg, unsigned long* ret) {
	int res;
	res = sscanf(arg, "%lu", ret);

	if (res == 0) {
		cerr << "expected integer at arg position " << endl;
		return false;
	}
	return true;
}

int main(int argc, char** argv) {
	g_Seed = platform_gen_seed();

	CGOptions::set_default_settings();

	cout << "// modified csmith for generating GaussDB procedures" << std::endl << std::endl;

	// Currently this program supports only '--version/-v' and '--seed/-s'
	for (int i = 1; i < argc; i++) {

		if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
			print_version();
			return 0;
		}

		if (strcmp(argv[i], "--seed") == 0 || strcmp(argv[i], "-s") == 0) {
			i++;
			arg_check(argc, i);

			if (!parse_int_arg(argv[i], &g_Seed))
				exit(-1);
			continue;
		}

		cerr << "invalid option " << argv[i] << " at: " << i << endl;
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