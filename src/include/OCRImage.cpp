#include <iostream>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "OCRImage.hpp"

namespace
{
    tesseract::TessBaseAPI*api = nullptr;
}

void PanCake::OCRImage(std::vector<PanCake::Tweet>&bucket,const PanCake::Tweet&tweet,const int index,const std::string&imgPath)
{
    if(!api)
    {
        api = new tesseract::TessBaseAPI();
        api->Init(NULL,"eng");
    }

    ::Pix*image = ::pixRead(imgPath.c_str());
    api->SetImage(image);

    auto end = bucket.end();
    for(auto it = bucket.begin(); it != end; ++it)
    {
        if(it->id == tweet.id)
        {
            it->images.at(index).OCRText = api->GetUTF8Text();
            break;
        }
    }

    ::pixDestroy(&image);
}
