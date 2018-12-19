#include <iostream>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "OCRImage.hpp"

namespace
{
    tesseract::TessBaseAPI*api = nullptr;
}

std::string PanCake::OCRImage(const std::string&imgPath)
{
    if(!api)
    {
        api = new tesseract::TessBaseAPI();
        api->Init(NULL,"eng");
    }

    ::Pix*image = ::pixRead(imgPath.c_str());
    api->SetImage(image);


    ::pixDestroy(&image);

    return api->GetUTF8Text();
}
