function env()
    UserLoad()
end

function q()
    local count = 0
    local chunkEnd = #userCol
    for i=1,chunkEnd do
        if userCol[i] == "toad_spotted" then
            count = count + 1
        end
    end
    userCol:clear()
    return count
end