#include <fstream>
#include <iostream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/include/nerTagBin.hpp"

TEST_CASE("Should make paths","")
{
    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","California") == "tests/rt/nerTagStoreSave/Cal.json");
    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","CAlifornia") == "tests/rt/nerTagStoreSave/CAl.json");

    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","@ab") == "tests/rt/nerTagStoreSave/@ab.json");

    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","#1") == "tests/rt/nerTagStoreSave/#1.json");

    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","C") == "tests/rt/nerTagStoreSave/C.json");
    REQUIRE(PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","c") == "tests/rt/nerTagStoreSave/c.json");

    
}

TEST_CASE("Should load and save bins","")
{
    PanCake::NERTagBin bin("tests/rt/nerTagStoreSave",PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","#homecoming"));
    
    REQUIRE(bin.loadBin() == false);

    REQUIRE(bin.tagExists("#homecoming") == false);
    REQUIRE(bin.getTagType("#homecoming") == "");
    bin.addTag("#homecoming","hashtag");
    REQUIRE(bin.saveBin() == true);
    REQUIRE(bin.tagExists("#homecoming") == true);
    REQUIRE(bin.getTagType("#homecoming") == "hashtag");

    PanCake::NERTagBin bin2("tests/rt/nerTagStoreSave",PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","#homecoming"));

    REQUIRE(bin2.loadBin() == true);
    REQUIRE(bin2.tagExists("#homecoming") == true);
    REQUIRE(bin2.getTagType("#homecoming") == "hashtag");
    REQUIRE(bin2.tagExists("#hometime") == false);
    REQUIRE(bin2.getTagType("#hometime") == "");
    bin2.addTag("#hometime","hashtag");
    REQUIRE(bin2.tagExists("#hometime") == true);
    REQUIRE(bin2.getTagType("#hometime") == "hashtag");

    REQUIRE(bin2.saveBin() == true);

    PanCake::NERTagBin bin3("tests/rt/nerTagStoreSave",PanCake::makeNERStorageBinPath("tests/rt/nerTagStoreSave","#homecoming"));

    REQUIRE(bin2.tagExists("#hometime") == true);
    REQUIRE(bin2.getTagType("#hometime") == "hashtag");
    REQUIRE(bin.tagExists("#homecoming") == true);
    REQUIRE(bin.getTagType("#homecoming") == "hashtag");
}