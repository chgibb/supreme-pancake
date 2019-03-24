function env()
    UserLoad()
end

function q(s,e)
    local count = 0
    for i=s,e do
        if userCol[i] == "toad_spotted" then
            count = count + 1
        end
    end
    return count
end