#include <vector>
#include <string>
#include <any>
#include "cmdline.hpp"

using namespace std;

/*		
template <typename T> const T         getOptionAs(const char* name) {
			const char* value = getOption(name);
			return castByNative<T>(value);
		
	bool            CmdLine::isOptionMultiple(string name) { return _commandLine->isOptionMultiple(name.c_str()); };
*/
/*
namespace cmdline {
template<> string CmdLine::getOptionAs<string>(const char* name) {
	const char* value = getOption(name);
		return string(value);
}
template<> const char* CmdLine::getOptionAs<const char*>(const char* name) {
		return getOption(name);
}
template<> int CmdLine::getOptionAs<int>(const char* name) {
	const char* value = getOption(name);
	return _cmdline::validateNumber(value);
}
template<> long CmdLine::getOptionAs<long>(const char* name) {
	const char* value = getOption(name);
	return _cmdline::validateNumber(value);
}
template<> any CmdLine::getOptionAs<>(const char* name) {
	const char* value = getOption(name);
	// gettype
	Type type  = getType(name);
	switch (type) {
	}
	throw CmdLineInvalidTypeException("Unknow"); // typeid(T).name());
}

}
*/
/*
template <typename T> T castByNative(const char* value) {
		if constexpr (is_same<T, const char*>::value)      return value;
		if constexpr (is_same<T, char*>::value)            return (char*)value;

		if constexpr (is_same<T, TYPE_STRING>::value)       return string(value);
		if constexpr (is_same<T, TYPE_LONG>::value)         return _cmdline::validateNumber(value);
		if constexpr (is_same<T, TYPE_INT>::value)          return _cmdline::makeInteger(value);
		if constexpr (is_same<T, TYPE_DECIMAL>::value)      return _cmdline::validateDecimal(value);
		if constexpr (is_same<T, TYPE_FLOAT>::value)        return _cmdline::makeFloat(value);
		if constexpr (is_same<T, TYPE_DOUBLE>::value)       return _cmdline::validateDecimal(value);
		if constexpr (is_same<T, TYPE_DATE>::value)         return _cmdline::makeTm(value);
		if constexpr (is_same<T, TYPE_TIME>::value)         return _cmdline::makeTm(value);
		if constexpr (is_same<T, TYPE_DATETIME>::value)     return _cmdline::makeTm(value);
		if constexpr (is_same<T, TYPE_TMS>::value)          return _cmdline::validateTimestamp(value);
		if constexpr (is_same<T, TYPE_LONGNUMBER>::value)   return _cmdline::validateLongNumber(value);
		if constexpr (is_same<T, TYPE_LONGDECIMAL>::value)  return _cmdline::validateLongDecimal(value);
		if constexpr (is_same<T, TYPE_DIR>::value)          return _cmdline::validateFile(value);
		if constexpr (is_same<T, TYPE_FILE>::value)         return _cmdline::validateDir(value);
		if constexpr (is_same<T, TYPE_BOOL>::value) {
			if (value == 0x0) return false;
			return _cmdline::valMakeBoolean(value);
		}
		throw CmdLineInvalidTypeException(typeid(T).name());
	}
	*/