#include "../catch/catch.hpp"
#include "../dict.h"
#include "../pattern.h"
#include <string>

Pattern *p = new Pattern("data/rt_sm_test.txt");
TEST_CASE("CGO to CGO") {
    std::string str = p->findShorestPath("CGO", "CGO");
    REQUIRE(str == "CGO->CGO");
}

TEST_CASE("CTU to PEK") {
    std::string str = p->findShorestPath("CTU", "PEK");
    REQUIRE(str == "CTU->PEK");
}

TEST_CASE("CTU to CGO") {
    std::string str = p->findShorestPath("CTU", "CGO");
    REQUIRE(str == "CTU->TPE, TPE->CGO");
}

TEST_CASE("CGO to HKG") {
    std::string str = p->findShorestPath("CGO", "HKG");
    REQUIRE(str == "CGO->HKG");
}

TEST_CASE("TXL to CTU") {
    std::string str = p->findShorestPath("TXL", "CTU");
    REQUIRE(str == "TXL->PEK, PEK->CTU");
}

TEST_CASE("SIN to TPE") {
    std::string str = p->findShorestPath("SIN", "TPE");
    REQUIRE(str == "SIN->TPE");
}

TEST_CASE("SIN to HKG") {
    std::string str = p->findShorestPath("SIN", "HKG");
    REQUIRE(str == "SIN->HKG");
}

TEST_CASE("PEK to CGO") {
    std::string str = p->findShorestPath("PEK", "CGO");
    REQUIRE(str == "PEK->CTU, CTU->TPE, TPE->CGO");
}

TEST_CASE("PEK to TPE") {
    std::string str = p->findShorestPath("PEK", "TPE");
    REQUIRE(str == "PEK->CTU, CTU->TPE");
}

TEST_CASE("CTU to TPE") {
    std::string str = p->findShorestPath("CTU", "TPE");
    REQUIRE(str == "CTU->TPE");
}

TEST_CASE("CTU to SIN") {
    std::string str = p->findShorestPath("CTU", "SIN");
    REQUIRE(str == "There is no path from CTU to SIN");
}

TEST_CASE("CTU to CGQ, via PEK") {
    std::string str = p->findShorestPathWithMidpoint("CTU", "PEK", "CGQ");
    REQUIRE(str == "CTU->PEK, PEK->CTU, CTU->TPE, TPE->CGQ");
}
