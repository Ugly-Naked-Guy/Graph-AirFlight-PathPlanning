#include "../catch/catch.hpp"
#include "../dict.h"
#include "../pattern.h"
#include <string>

TEST_CASE("traversal") {
    Pattern *p = new Pattern("data/rt_sm_test.txt");
    std::string str = "";
    std::vector<std::string> list = p->traversal("CTU");
    for (unsigned x = 0; x < list.size(); x++) {
        str = str + list[x] + " ";
    }
    REQUIRE(str == "CTU PEK TPE CGO HKG SIN TXL ");
}

TEST_CASE("traversal2") {
    Pattern *p = new Pattern("data/rt_sm_test.txt");
    std::string str = "";
    std::vector<std::string> list = p->traversal("SIN");
    for (unsigned x = 0; x < list.size(); x++) {
        str = str + list[x] + " ";
    }
    REQUIRE(str == "SIN HKG TPE CGO CTU PEK TXL ");
}