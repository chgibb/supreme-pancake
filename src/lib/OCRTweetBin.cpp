#include <vector>
#include <algorithm>
#include <fstream>

#include "OCRTweetBin.hpp"
#include "OCR.hpp"
#include "fileExists.hpp"
#include "tweetBin.hpp"
#include "loadTweetBin.hpp"
#include "makeTweetTimePointPaths.hpp"
#include "interfaces/serializeOCRResult.hpp"
#include "interfaces/OCRResult.hpp"
#include "interfaces/tweet.hpp"

PanCake::BulkOCRResult PanCake::OCRTweetBin(const char*dataDir,const std::string&path)
{
    PanCake::BulkOCRResult bulkRes;
    PanCake::TweetBin*bin = PanCake::loadTweetBin(path.c_str());

    PanCake::forEachBucket(
        *bin,
        [&dataDir,&bulkRes](const std::vector<PanCake::Tweet>&bucket) -> void {
            std::for_each(
                bucket.begin(),
                bucket.end(),
                [&dataDir,&bulkRes](const PanCake::Tweet&tweet) -> void {
                    int i = 0;
                    std::for_each(
                        tweet.images.begin(),
                        tweet.images.end(),
                        [&dataDir,&bulkRes,&tweet,&i](const std::string&url) -> void {
                            std::string resultPath = PanCake::makeTweetImageOCRResultFilePath(dataDir,tweet,i);

                            if(PanCake::fileExists(resultPath.c_str()))
                                return;

                            std::string imagePath = PanCake::makeTweetImageFilePath(dataDir,tweet,i);

                            PanCake::OCRResult res = PanCake::OCRImage(imagePath);

                            std::ofstream file(resultPath.c_str(),std::ios::out);
                            file<<PanCake::serializeOCRResult(res);
                            bulkRes.attempted++;

                            i++;
                        });
                });
        });
    
    return bulkRes;
}

