obj = getCurrDIM():addObject(50, 50, 20, 20, "movable", 0, 0, 0)

function initialize()
    local moveX, moveY = 1, 0

    if obj.posX == 50 and obj.posY == 50 then
        moveX = 1; moveY = 0
    elseif obj.posX == 130 and obj.posY == 50 then
        moveX = 0; moveY = 1
    elseif obj.posX == 130 and obj.posY == 130 then
        moveX = -1; moveY = 0
    elseif obj.posX == 50 and obj.posY == 130 then
        moveX = 0; moveY = -1
    end

    obj.posX = obj.posX + moveX
    obj.posY = obj.posY + moveY
end
