function env()
    UserLoad()
end

local count = 0

function q(s,e)
    for i=s,e do
        if userCol[i] == "toad_spotted" then
            count = count + 1
        end
    end
end

function e()
    return count
end

