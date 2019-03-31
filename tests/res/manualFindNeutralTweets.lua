function env()
    SentimentScoreLoad()
end

local count = 0

function q(s,e)
    for i=s,e do
        if sentimentScoreCol[i] == 0 then
            count = count + 1
        end
    end
end

function e()
    return count
end