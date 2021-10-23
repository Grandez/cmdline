#include "pch.h"
#include <stdexcept>
#include <regex>
#include <any>

#include "../cmdline/parmitem.hpp"
#include "../cmdline/hashmap.hpp"

using namespace cmdline;
TEST(Mapping, init) {
//	HashMap<std::string> hmap;
	ParmItem item1 = ParmItem("pepe");
	
//	hmap.insert(item1.name, &item1);
	// map->insert(item1->name, &item1);
	// EXPECT_NO_THROW(validateTime("1 1 1"));
}

