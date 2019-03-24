function env()
    IsRetweetLoad()
end

function q(s,e)
    local count = 0
    for i=s,e do
        count = count + isRetweetCol[i]
    end
    return count
end