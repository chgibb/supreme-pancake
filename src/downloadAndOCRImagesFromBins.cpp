#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#include "vendor/cxxopts/include/cxxopts.hpp"

#include "include/loadJSON.hpp"
#include "include/tweetBin.hpp"
#include "include/loadTweetBin.hpp"

int main(int argc,char*argv[])
{
    cxxopts::Options options("downloadAndOCRImagesFromBins", "Download images from tweets in the given list of bins");

    options.add_options()("d,dir","Storage directory path",cxxopts::value<std::string>());

    auto result = options.parse(argc,argv);

    std::string storageDir = result["dir"].as<std::string>();

    std::string raw;
    
    std::getline(std::cin,raw);
    
    auto json = PanCake::loadJSONFromString(raw);

    std::ofstream file("out.txt");
    file<<raw<<"\n";
    file<<storageDir<<"\n";

    for(auto&binPath : json.GetArray())
    {
        std::cout<<binPath.GetString()<<std::endl;
        PanCake::TweetBin*bin = PanCake::loadTweetBin(binPath.GetString());

        delete bin;
    }
    
    std::cout.flush();

    return 0;
}