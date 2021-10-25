// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
 - string ok

*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include <vector>
#include <type_traits>
#include <ctime>
#include <sstream>
#include <locale>
#include <ctime>
#include <iostream>
#include <locale>
#include <sstream>
#include <time.h>
#include <errno.h>
#include <regex>

// time_get::get_date example
#include <iostream>       // std::cout, std::ios
#include <sstream>        // std::istringstream
#include <ctime>          // std::tm
#include <locale>         // std::locale, std::time_get, std::use_facet
#include <string>
#include <stdio.h>

using namespace std;

void show_date_order()
{
    std::time_base::dateorder d = std::use_facet<std::time_get<char>>(
        std::locale()
        ).date_order();
    switch (d)
    {
    case std::time_base::no_order: std::cout << "no_order\n"; break;
    case std::time_base::dmy: std::cout << "day, month, year\n"; break;
    case std::time_base::mdy: std::cout << "month, day, year\n"; break;
    case std::time_base::ymd: std::cout << "year, month, day\n"; break;
    case std::time_base::ydm: std::cout << "year, day, month\n"; break;
    }
}
std::vector<std::string> tokenize(char *src, char* pat) {
    std::string str(src);

    std::regex reg(pat);

    std::sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> vec(iter, end);
    return vec;
}
bool validateTime2(char* value) {
    cout << "validating " << value;
    std::regex pat{ "[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}" };
    std::tm t;
    memset(&t, 0, sizeof(tm));
    bool match = std::regex_search(value, pat);
    //    if (!match) throw CmdLineValueException(value, "expected time");
    if (!match) return true;
    std::vector<std::string> res = tokenize(value, (char *) ":");
    int number = stoi(res[0]);
    if (number < 0 || number > 23) return true;
    for (int i = 1; i < 3; i++) {
        number = stoi(res[i]);
        if (number < 0 || number > 59) return true;
    }
    return false;
}
bool validateTime(char* value) {
    std::regex pat{ "[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}" };
    std::tm t;
    memset(&t, 0, sizeof(tm));
    bool match = std::regex_search(value, pat);
//    if (!match) throw CmdLineValueException(value, "expected time");
    if (!match) return true;
    const std::string& ss = std::string(value);
    std::istringstream str(ss);
//    str >> std::get_time(&t, "%H:%M:%S");
//    if (str.fail()) throw CmdLineValueException(value, "expected time");
    if (str.fail()) return true;
    std::time_t time = mktime(&t);
    //return new std::time_t(time);
    //return new std::string(value);
    return false;
}

int main()
{
    std::locale loc;        // classic "C" locale
    show_date_order();
    std::locale::global(std::locale("en_US.utf8"));
    std::cout << "In U.S. locale, the default date order is: ";
    show_date_order();

    std::locale::global(std::locale("ja_JP.utf8"));
    std::cout << "In Japanese locale, the default date order is: ";
    show_date_order();

    std::locale::global(std::locale("de_DE.utf8"));
    std::cout << "In German locale, the default date order is: ";
    show_date_order();
    std::cout << (validateTime2((char*) "1:1:1")    ? "\tKO" : "\tOK") << std::endl;
    std::cout << (validateTime2((char*) "23:59:59") ? "\tKO" : "\tOK") << std::endl;
    std::cout << (validateTime2((char*) "23 59 59") ? "\tKO" : "\tOK") << std::endl;
    std::cout << (validateTime2((char*) "0:0:0") ? "\tKO" : "\tOK") << std::endl;
    std::cout << (validateTime2((char*) "24:0:0") ? "\tKO" : "\tOK") << std::endl;
    std::string str("The quick brown fox");

    std::regex reg("\\s+");

    std::sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> vec(iter, end);

    for (auto a : vec)
    {
        cout << a << endl;
    }


    // get time_get facet:
    const std::time_get<char>& tmget = std::use_facet <std::time_get<char> >(loc);

    std::ios::iostate state;
    std::istringstream iss("01/15/2123");
    std::tm when;

    tmget.get_date(iss, std::time_get<char>::iter_type(), iss, state, &when);

    std::cout << "year: " << when.tm_year << '\n';
    std::cout << "month: " << when.tm_mon << '\n';
    std::cout << "day: " << when.tm_mday << '\n';
    return 0;
}
void try_get_time_from_str(const std::string& s) {
    std::istringstream str(s);
    std::ios_base::iostate err = std::ios_base::goodbit;
    std::tm t;
    std::istreambuf_iterator<char> ret =
        std::use_facet<std::time_get<char> >(str.getloc()).get_time(
            std::istreambuf_iterator<char>(str),
            std::istreambuf_iterator<char>(),
            str, err, &t
        );
    str.setstate(err);
    if (str) {
        std::cout << "Hours: " << t.tm_hour << ' '
            << "Minutes: " << t.tm_min << ' '
            << "Seconds: " << t.tm_sec << '\n';
    }
    else {
        std::cout << "Parse failed. Unparsed string: ";
        std::copy(ret, std::istreambuf_iterator<char>(),
            std::ostreambuf_iterator<char>(std::cout));
        std::cout << '\n';
    }
}

int main2() {
    std::time_t timestamp;
    std::time(&timestamp);
    std::tm* now = std::localtime(&timestamp);
    std::cout << "GB: ";
    {
        std::locale::global(std::locale("en_GB.utf8"));
        std::ostringstream out;
        std::use_facet< std::time_put<char> >(out.getloc()).put(
            out,
            out,
            ' ',
            now,
            'X');
        try_get_time_from_str(out.str());
    }
    std::cout << "US: ";
    {
        std::locale::global(std::locale("en_US.utf8"));
        std::ostringstream out;
        std::use_facet< std::time_put<char> >(out.getloc()).put(
            out,
            out,
            ' ',
            now,
            'X');
        try_get_time_from_str(out.str());
    }
    return 0;
}
/*
char* split(std::vector<char*> toks, char *str, char *pat) {
    char* next_token1 = NULL;
    char* pch;
    pch = strtok_s(str, pat, &next_token1);
    if (pch) {
        toks.push_back(pch);
    }
    return pch;
}

template <class T, class P>
void foo(T t, P p) {
    if constexpr (std::is_same_v<T, P>) {
        std::cout << "iguales" << std::endl;
    }
    else {
        std::cout << "distinto" << std::endl;
    }
}

bool validateDate(char* value) {
    std::cout << value << " - " << std::endl;
    const std::string& ss = std::string(value);
    std::istringstream str(ss);
    std::ios_base::iostate err = std::ios_base::goodbit;

    std::tm t;
    std::istreambuf_iterator<char> ret =
        std::use_facet<std::time_get<char>>(str.getloc()).get_time(
            { str }, {}, str, err, &t
        );
    str.setstate(err);
    if (!str) {
        return true;
        //std::cout << "iguales" << std::endl;
    }
    return false;
//    else {
//        std::cout << "distinto" << std::endl;
//    }

    //return new std::string(value);
}
int main()
{
    bool rc;
std::string spat = "juan";
    std::string p("pepe");

    foo(p, spat);
    
    std::cout << (validateDate((char*)"1/1/11") ? " OK" : "KO" ) << std::endl;
    std::cout << (validateDate((char*)"1/14/11") ? " OK" : "KO") << std::endl;
    std::cout << (validateDate((char*)"14/14/11") ? " OK" : "KO") << std::endl;
//    time_t now1 = time(0);
//    time_t now2 = time();

    // convert now to string form
//    char* dt = ctime(&now);

 //   cout << "The local date and time is: " << dt << endl;

    // convert now to tm struct for UTC
//    tm* gmtm = gmtime(&now);
 //   dt = asctime(gmtm);
    //if (typeid(obj1) == typeid(ob2))//or typeid(obj1)==classname
    //    cout << "obj1 is instance of yourclassname"

    char* next_token1 = NULL;
    std::vector<char*> toks;
    std::vector<std::string> toks2;
    std::cout << "Hello World!\n";
    char str[] = "\"otra, coma\",una,\"This a sample, string.";
    char* pch;
    printf("Splitting quotes \"%s\" into tokens:\n", str);
    // inicio
//    if (str[0] == '\"') split(toks, str, (char *) "\""); 
    pch = strtok_s(str, ",", &next_token1);
    while (pch != NULL) {
        toks.push_back(pch);
        printf("%s\n", pch);
        pch = strtok_s(NULL, ",", &next_token1);
    }
    bool quote = false;
    int idx = 0;
    for (char* t : toks) {
        if (t[0] == '"') {
            toks2.push_back(&(t[1]));
            quote = true;
        }
        else {
            if (quote) {
                toks2[idx].append(",");
                if (t[strlen(t) - 1] == '"') {
                    t[strlen(t) - 1] = 0x0;
                    quote = false;
                }
                toks2[toks2.size() - 1].append(t);
            }
            else {
                toks2.push_back(t);
            }
        }
    }
    if (quote) {
        printf("missing comma\n");
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
*/