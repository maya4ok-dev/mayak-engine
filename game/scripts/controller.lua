local objects = world.active():getObjects()
local speed = 250

return function(dt)
    for _, object in ipairs(objects) do
        for _, tag in ipairs(object.tags) do

            if tag ~= "player" then goto continue end
                
            if isKeyPressed("UP") then
                object.posY = object.posY - speed * dt
            end
            if isKeyPressed("DOWN") then
                object.posY = object.posY + speed * dt
            end
            if isKeyPressed("LEFT") then
                object.posX = object.posX - speed * dt
            end
            if isKeyPressed("RIGHT") then
                object.posX = object.posX + speed * dt
            end

            ::continue::
        end
    end
end
