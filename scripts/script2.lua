local obj = getObjects()[1]
local time = 0
local startX = obj.posX
local startY = obj.posY

function update(dt)
    time = time + dt
    print(time)
    obj.posX = startX + math.sin(time) * 100
    obj.posY = startY + math.cos(time) * 100
end
