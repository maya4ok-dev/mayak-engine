local controller = nil
local transform = nil
local aabb = nil
local camera = nil

local initialized = false

return function(dt)
    if not initialized then
        local entities = world.active():getEntities()
        for _, entity in ipairs(entities) do
            local name = entity:get("Name")
            if not name then goto continue end

            if name.name == "player" then
                controller = entity:get("Controller")
                transform = entity:get("Transform")
                aabb = entity:get("AABB")
            elseif name.name == "camera" then
                camera = entity:get("Camera")
            end

            ::continue::
        end
        initialized = true
    end

    assert(controller, "player's controller componenet not found")
    assert(transform, "player's transform componenet not found")
    assert(aabb, "player's hitbox componenet not found")

    local offset_x = 0
    local offset_y = 0

    if isKeyPressed("UP")    then offset_y = offset_y - controller.speed * dt end
    if isKeyPressed("DOWN")  then offset_y = offset_y + controller.speed * dt end
    if isKeyPressed("LEFT")  then offset_x = offset_x - controller.speed * dt end
    if isKeyPressed("RIGHT") then offset_x = offset_x + controller.speed * dt end

    if transform.y + offset_y >= 0 and transform.y + transform.h + offset_y <= camera.h then
        transform.y = transform.y + offset_y
    end

    if transform.x + offset_x >= 0 and transform.x + transform.w + offset_x <= camera.w then
        transform.x = transform.x + offset_x
    end

    aabb.x = transform.x
    aabb.y = transform.y
    aabb.w = transform.w
    aabb.h = transform.h
end
