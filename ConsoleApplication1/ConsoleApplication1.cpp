// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
#include <vector>

char* split(std::vector<char*> toks, char *str, char *pat) {
    char* next_token1 = NULL;
    char* pch;
    pch = strtok_s(str, pat, &next_token1);
    if (pch) {
        toks.push_back(pch);
    }
    return pch;
}
int main()
{
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
