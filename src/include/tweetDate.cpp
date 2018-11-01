#include "tweetDate.hpp"

std::string PanCake::tweetDateToTimePointPathString(PanCake::TweetDate&date)
{
    return std::string(date.year)+"/"+std::string(date.month)+"/"+std::string(date.day)+"/"+std::string(date.hour)+"/"+std::string(date.minute)+"/"+std::string(date.second);
}