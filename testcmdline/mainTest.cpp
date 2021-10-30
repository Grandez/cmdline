#include "pch.h"
#include "_global.hpp"

Tool tool;

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}