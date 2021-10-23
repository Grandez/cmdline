#pragma once
namespace cmdline {
	enum class Type { FLAG, STRING, NUMBER, DECIMAL, DATE, TIME, DIR, DIR_EXISTS, FILE, FILE_EXISTS };
	enum class Source { DEFAULT, ENV, CMDLINE };
}
