function env()
    TextLoad()
    addRegex("@realDonaldTrump")
end

local count = 0

function q(s,e)
    for i=s,e do
       if match(0,textCol[i]) == true then
        count = count + 1
       end
    end
end

function e()
    return count
end

