function env()
    IsRetweetLoad()
end

function q()
    local count = 0
    local chunkEnd = #isRetweetCol
    for i=1,chunkEnd do
        count = count + isRetweetCol[i]
    end
    isRetweetCol:clear()
    return count
end