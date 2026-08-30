local objects = getObjects()
local speed = 150

function update(dt)
    for _, object in ipairs(objects) do
        if object.type == "player" then
            if isKeyPressed(KEY_UP) then
                object.posY = object.posY - speed * dt
            end
            if isKeyPressed(KEY_DOWN) then
                object.posY = object.posY + speed * dt
            end
            if isKeyPressed(KEY_LEFT) then
                object.posX = object.posX - speed * dt
            end
            if isKeyPressed(KEY_RIGHT) then
                object.posX = object.posX + speed * dt
            end
        end
    end
end