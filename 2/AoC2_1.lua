function isSafe(list)
    local a = list[1]
    local b = list[2]
    if a-b < 0 then isOk = isInBoundsNegative
    elseif a-b > 0 then isOk = isInBoundsPositive
    else return false end
    local i = 2
    while not (list[i] == nil) do
        local diff = list[i-1]-list[i]
        if not isOk(diff) then return false end
        i = i + 1
    end
    return true
end
    
function isInBoundsPositive(n)
    if  0 < n and n <=3 then return true end
    return false
end

function isInBoundsNegative(n)
    if -3 <= n and n < 0 then return true end
    return false
end

function splitByWhites(text)
    return string.gmatch(text, "%S+")
end

function poorMansMap(fun, list)
    local result = {}
    for i in list do
        table.insert(result,fun(i))
    end
    return result
end

local file =io.open("input.txt", "r")
safeCount = 0
for line in file:lines() do 
    if isSafe(poorMansMap(tonumber, splitByWhites(line))) then safeCount = safeCount + 1 end
end
print(safeCount)