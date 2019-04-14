#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "OCR.hpp"

namespace
{
    tesseract::TessBaseAPI*api = nullptr;
}

std::string PanCake::Internal::OCR(const std::string&path)
{
    if(!api)
    {
        api = new tesseract::TessBaseAPI();
        api->Init(NULL,"eng");
    }

    ::Pix*image = ::pixRead(path.c_str());
    api->SetImage(image);

    ::pixDestroy(&image);

    return api->GetUTF8Text();
}

PanCake::OCRResult PanCake::OCRImage(const std::string&path)
{
    PanCake::OCRResult res;
    
    res.text = PanCake::Internal::OCR(path);

    return res;
}

