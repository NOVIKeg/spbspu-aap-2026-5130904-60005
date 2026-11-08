#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>

char* sharedSymbols(const char* src) {
    bool present[256] = { false };

    for (const char* p = src; *p; ++p) {
        unsigned char c = (unsigned char)*p;
        if (c >= 'A' && c <= 'Z') c = (unsigned char)tolower(c);
        present[c] = true;
    }

    size_t count = 0;
    for (int c = 'a'; c <= 'z'; ++c) {
        if (!present[c]) ++count;
    }

    char* result = (char*)malloc(count + 1);
    if (!result) return nullptr;

    size_t i = 0;
    for (int c = 'a'; c <= 'z'; ++c) {
        if (!present[c]) {
            result[i++] = (char)c;
        }
    }
    result[i] = '\0';
    return result;
}

char* excludeSecond(const char* s1, const char* s2) {
    bool inSecond[256] = { false };
    for (const char* p = s2; *p; ++p) {
        inSecond[(unsigned char)*p] = true;
    }
    size_t count = 0;
    for (const char* p = s1; *p; ++p) {
        if (!inSecond[(unsigned char)*p]) ++count;
    }

    char* result = (char*)malloc(count + 1);
    if (!result) return nullptr;

    size_t i = 0;
    for (const char* p = s1; *p; ++p) {
        if (!inSecond[(unsigned char)*p]) {
            result[i++] = *p;
        }
    }
    result[i] = '\0';
    return result;
}

int main() {
    {
        char first[256];
        std::cout << "Введите строку: ";
        std::cin >> first;

        char* res = sharedSymbols(first);
        if (!res) {
            std::cerr << "Ошибка выделения памяти" << std::endl;
            return 1;
        }
        std::cout << "Результат: " << res << std::endl;
        free(res);
    }

    {
        char first[256], second[256];

        std::cout << "Введите первую строку: ";
        std::cin >> first;
        std::cout << "Введите вторую строку: ";
        std::cin >> second;

        char* res = excludeSecond(first, second);
        if (!res) {
            std::cerr << "Ошибка выделения памяти" << std::endl;
            return 1;
        }
        std::cout << "Результат: " << res << std::endl;
        free(res);
    }

    return 0;
}
