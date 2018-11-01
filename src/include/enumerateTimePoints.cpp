#include "enumerateTimePoints.hpp"

std::vector<std::string> PanCake::enumerateTimePointPathString(PanCake::TweetDate date)
{
    std::vector<std::string> res;
    
    if(date.year == "")
        return res;
    else if(date.month == "")
        return res;
    else if(date.day == "")
        return res;
    
    PanCake::EnumerateTimePoints::Hour hour;
    PanCake::EnumerateTimePoints::Minute minute;
    PanCake::EnumerateTimePoints::Minute second;

    res.reserve(86400);

    for(int i = 0; i != 86400; ++i)
    {
        if(second.hasOverFlowed())
            minute.increment();
        if(minute.hasOverFlowed())
            hour.increment();

        res.push_back(std::string(date.year)+"/"+std::string(date.month)+"/"+std::string(date.day)+"/"+hour.get()+"/"+minute.get()+"/"+second.get());

        second.increment();
    }

    return res;
}

void PanCake::EnumerateTimePoints::Hour::increment()
{
    this->numHour++;
    if(this->numHour >= 24)
    {
        this->numHour = 0;
        this->overFlowed = true;
    }
}

bool PanCake::EnumerateTimePoints::Hour::hasOverFlowed()
{
    if(this->overFlowed)
    {
        this->overFlowed = false;
        return true;
    }
    return false;
}

std::string PanCake::EnumerateTimePoints::Hour::get()
{
    std::string res = std::to_string(this->numHour);
    if(res.length() == 1)
        return "0"+res;
    return res;
}

void PanCake::EnumerateTimePoints::Minute::increment()
{
    this->numMinute++;
    if(this->numMinute >= 60)
    {
        this->numMinute = 0;
        this->overFlowed = true;
    }
}

bool PanCake::EnumerateTimePoints::Minute::hasOverFlowed()
{
    if(this->overFlowed)
    {
        this->overFlowed = false;
        return true;
    }
    return false;
}

std::string PanCake::EnumerateTimePoints::Minute::get()
{
    std::string res = std::to_string(this->numMinute);
    if(res.length() == 1)
        return "0"+res;
    return res;
}
