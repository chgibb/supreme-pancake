function env()
    SentimentScoreLoad()
end

function q(s,e)
    local count = 0
    for i=s,e do
        if sentimentScoreCol[i] == 0 then
            count = count + 1
        end
    end
    return count
end
