#include <iostream>
#include <fstream>
#include <string>

#include "vendor/cxxopts/include/cxxopts.hpp"

#include "include/columnIR/IRGenerator.hpp"

int main(int argc,char*argv[])
{
    cxxopts::Options options("genColumnIR", "");

    options.add_options()
    ("d,dir","Storage directory path",cxxopts::value<std::string>())
    ("o,outDir","Output directory path",cxxopts::value<std::string>())
    ("y,year","Year",cxxopts::value<std::string>())
    ("m,month","Month",cxxopts::value<std::string>())
    ("D,day","Day",cxxopts::value<std::string>())
    ("c,chunkSize","Chunk Size",cxxopts::value<int>());

    auto result = options.parse(argc,argv);

    std::string storageDir = result["dir"].as<std::string>();
    std::string outDir = result["outDir"].as<std::string>();
    std::string year = result["year"].as<std::string>();
    std::string month = result["month"].as<std::string>();
    std::string day = result["day"].as<std::string>();
    int chunkSize = result["chunkSize"].as<int>();

    PanCake::TweetDate date;
    date.year = year;
    date.month = month;
    date.day = day;

    if(!PanCake::generateChunkedIR(storageDir.c_str(),date,chunkSize,outDir.c_str()))
        return 1;

    return 0;
}
