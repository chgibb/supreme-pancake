#include <curl/curl.h>
#include <iostream>
#include "downloadImage.hpp"

[[nodiscard]] bool PanCake::downloadImage(const std::string&url,std::string&filePath)
{
    FILE*file = ::fopen(filePath.c_str(),"wb");
    if(!file)
        return false;
    
    CURL*easyHandle = ::curl_easy_init();
    ::curl_easy_setopt(easyHandle,CURLOPT_URL,url.c_str());

    ::curl_easy_setopt(easyHandle,CURLOPT_WRITEDATA,file);

    bool res = true;

    ::CURLcode status = ::curl_easy_perform(easyHandle);
    long httpCode = 0;

    ::curl_easy_getinfo(easyHandle,CURLINFO_RESPONSE_CODE,&httpCode);

    if(httpCode == 404)
        res = false;

    ::curl_easy_cleanup(easyHandle);
    ::fclose(file);

    return res;
}