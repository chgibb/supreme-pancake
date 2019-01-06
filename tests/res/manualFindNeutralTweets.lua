function env()
    SentimentScoreLoad()
end

function q()
    local count = 0
    local chunkEnd = #sentimentScoreCol
    for i=1,chunkEnd do
        if sentimentScoreCol[i] == 0 then
            count = count + 1
        end
    end
    sentimentScoreCol:clear()
    return count
end