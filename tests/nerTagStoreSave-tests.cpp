#include <fstream>
#include <iostream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/include/nerTagStore.hpp"

TEST_CASE("Should make paths","")
{
    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","California") == "tests/rt/nerTagStoreSave/Cal.json");
    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","CAlifornia") == "tests/rt/nerTagStoreSave/CAl.json");

    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","@ab") == "tests/rt/nerTagStoreSave/@ab.json");

    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","#1") == "tests/rt/nerTagStoreSave/#1.json");

    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","C") == "tests/rt/nerTagStoreSave/C.json");
    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","c") == "tests/rt/nerTagStoreSave/c.json");

    
}