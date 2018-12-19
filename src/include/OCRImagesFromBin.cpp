#include <algorithm>
#include <vector>
#include <experimental/filesystem>

#include "OCRImagesFromBin.hpp"
#include "bulkOCRStatus.hpp"
#include "OCRImage.hpp"
#include "directoryExists.hpp"
#include "fileExists.hpp"
#include "makeTweetTimePointPaths.hpp"
#include "tweet.hpp"

[[nodiscard]] PanCake::BulkOCRStatus PanCake::OCRImagesFromBin(const char*dataDir,PanCake::TweetBin&bin)
{
    PanCake::BulkOCRStatus res;

    PanCake::forEachBucket(
        bin,
        [&dataDir,&res]
        (std::vector<PanCake::Tweet>&bucket) -> void {
            std::for_each(
                bucket.begin(),
                bucket.end(),
                [&dataDir,&res,&bucket]
                (PanCake::Tweet&tweet) -> void {
                    std::string folderPath = PanCake::makeTweetImagePath(dataDir,tweet);
                    
                    if(!PanCake::directoryExists(folderPath.c_str()))
                        return;

                    std::vector<std::string> imgPaths = PanCake::makeTweetImageFilePaths(dataDir,tweet);

                    for(std::size_t i = 0; i != imgPaths.size(); ++i)
                    {
                        if(!PanCake::fileExists(imgPaths.at(i).c_str()))
                            continue;
                        
                        res.attempted++;

                        std::string OCRResult = PanCake::OCRImage(imgPaths.at(i));

                        if(OCRResult != "")
                        {
                            res.succeeded++;

                            auto end = bucket.end();
                            for(auto it = bucket.begin(); it != end; ++it)
                            {
                                if(it->id == tweet.id)
                                {
                                    it->images.at(i).OCRText = OCRResult;
                                    break;
                                }
                            }
                        }

                        else
                            res.failed++;
                    }
                }
            );
        }
    );

    return res;
}
