#include "pch.h"
#include <map>
#include <stdexcept>
#include <regex>

#include "../cmdline/tools.h"

using namespace cmdline;

TEST(TextInput, items_1) {
	std::vector<std::string> res2;
	res2 = splitParameter("test1");
	EXPECT_EQ(res2.size(), 1);
}

TEST(TextInput, items_2) {
	std::vector<std::string> res;
	res = splitParameter("test1,test2");
	EXPECT_EQ(res.size(), 2);
}

TEST(TextInput, item_quoted) {
	std::vector<std::string> res;
	res = splitParameter("\"test1\"");
	EXPECT_EQ(res.size(), 1);
}
TEST(TextInput, two_item_quoted) {
	std::vector<std::string> res;
	res = splitParameter("\"test1\",\"test2\"");
	EXPECT_EQ(res.size(), 2);
}
TEST(TextInput, item_with_comma) {
	std::vector<std::string> res;
	res = splitParameter("\"test1,test2\"");
	EXPECT_EQ(res.size(), 1);
}
TEST(TextInput, items_with_comma_inserted) {
	std::vector<std::string> res;
	res = splitParameter("\"test1,test2\",\"item3,item4\"");
	EXPECT_EQ(res.size(), 2);
}
TEST(TextInput, mixed_1) {
	std::vector<std::string> res;
	res = splitParameter("test1,\"item3,item4\"");
	EXPECT_EQ(res.size(), 2);
}
TEST(TextInput, mixed_2) {
	std::vector<std::string> res;
	res = splitParameter("\"item3,item4\",item5");
	EXPECT_EQ(res.size(), 2);
}
