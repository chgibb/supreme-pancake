function env()
    IsRetweetLoad()
end

local count = 0

function q(s,e)
    for i=s,e do
        count = count + isRetweetCol[i]
    end
end

function e()
    return count
end
