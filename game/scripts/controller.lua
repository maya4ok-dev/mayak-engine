local objects = world.active():getObjects()
local speed = 250

function update(dt)
    for _, object in ipairs(objects) do
        for _, tag in ipairs(object.tags) do

            if tag ~= "player" then goto continue end
                
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

            ::continue::
        end
    end
end
