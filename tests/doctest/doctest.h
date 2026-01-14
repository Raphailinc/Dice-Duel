// SPDX-License-Identifier: MIT
// Minimal doctest single-header subset for our small test needs.
#ifndef DOCTEST_LIBRARY_INCLUDED
#define DOCTEST_LIBRARY_INCLUDED

#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace doctest {

struct TestFailure : public std::exception {
    std::string msg;
    explicit TestFailure(std::string m) : msg(std::move(m)) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

struct TestCase {
    std::string name;
    std::function<void()> func;
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> r;
    return r;
}

struct Register {
    Register(const std::string& name, std::function<void()> f) { registry().push_back({name, std::move(f)}); }
};

inline void check(bool expr, const char* expr_str, const char* file, int line) {
    if (!expr) {
        throw TestFailure(std::string(file) + ":" + std::to_string(line) + " CHECK failed: " + expr_str);
    }
}

} // namespace doctest

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_TESTCASE(name)                                                                                          \
    static void name();                                                                                                 \
    static doctest::Register reg_##name(#name, name);                                                                   \
    static void name()

#define CHECK(expr) doctest::check((expr), #expr, __FILE__, __LINE__)

int main() {
    int failed = 0;
    for (auto& tc : doctest::registry()) {
        try {
            tc.func();
        } catch (const std::exception& e) {
            ++failed;
            std::cerr << "[FAILED] " << tc.name << " - " << e.what() << "\n";
        }
    }
    if (failed) {
        std::cerr << failed << " test(s) failed\n";
        return 1;
    }
    std::cout << "All tests passed (" << doctest::registry().size() << ")\n";
    return 0;
}

#endif
