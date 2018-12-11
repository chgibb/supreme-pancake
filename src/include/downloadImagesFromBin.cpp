#include <algorithm>
#include <vector>
#include <iostream>
#include <experimental/filesystem>

#include "downloadImagesFromBin.hpp"
#include "downloadImage.hpp"
#include "directoryExists.hpp"
#include "fileExists.hpp"
#include "makeTweetTimePointPaths.hpp"
#include "tweet.hpp"

[[nodiscard]] PanCake::BulkImageDownloadStatus PanCake::downloadImagesFromBin(
    const char*dataDir,
    PanCake::TweetBin&bin,
    void(*afterDownload)(std::vector<PanCake::Tweet>&,const std::string&) = nullptr
    ) {
    PanCake::BulkImageDownloadStatus res;

    PanCake::forEachBucket(bin,[&dataDir,&res](std::vector<PanCake::Tweet>&bucket) -> void {
        std::for_each(bucket.begin(),bucket.end(),[&dataDir,&res](PanCake::Tweet&tweet) -> void {
            std::string folderPath = PanCake::makeTweetImagePath(dataDir,tweet);

            if(!PanCake::directoryExists(folderPath.c_str()))
                std::experimental::filesystem::create_directories(folderPath);

            std::vector<std::string> imgPaths = PanCake::makeTweetImageFilePaths(dataDir,tweet);

            for(std::size_t i = 0; i != imgPaths.size(); ++i)
            {
                if(PanCake::fileExists(imgPaths.at(i).c_str()))
                    continue;
                    
                bool downloadResult = PanCake::downloadImage(tweet.images.at(i),imgPaths.at(i));

                res.attempted++;

                if(downloadResult)
                    res.succeeded++;
                else
                    res.failed++;
            }
        });
    });

    return res;
}
