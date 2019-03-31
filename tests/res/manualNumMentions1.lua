function env()
    TextLoad()
    addRegex("@realDonaldTrump")
end

function q(s,e)
    local count = 0
    for i=s,e do
       if match(0,textCol[i]) == true then
        count = count + 1
       end
    end
    return count
end
