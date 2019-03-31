function env()
    TextLoad()
    SentimentScoreLoad()
    addRegex("@realDonaldTrump")
end

local count = 0
local totalSentiment = 0

function q(s,e)
    for i=s,e do
       if match(0,textCol[i]) == true then
        count = count + 1
        totalSentiment = totalSentiment + sentimentScoreCol[i]
       end
    end
end
