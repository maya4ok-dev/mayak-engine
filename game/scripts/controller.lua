local controller = nil
local transform = nil
local aabb = nil

local initialized = false

return function(dt)
    if not initialized then
        local entities = world.active():getEntities()
        for _, entity in ipairs(entities) do
            local name = entity:get("Name")
            if not name or name.name ~= "player" then goto continue end

            controller = entity:get("Controller")
            transform = entity:get("Transform")
            aabb = entity:get("AABB")

            ::continue::
        end
        initialized = true
    end

    assert(controller, "player's controller componenet not found")
    assert(transform, "player's transform componenet not found")
    assert(aabb, "player's hitbox componenet not found")

    if isKeyPressed("UP") then
        transform.y = transform.y - controller.speed * dt
    end
    if isKeyPressed("DOWN") then
        transform.y = transform.y + controller.speed * dt
    end
    if isKeyPressed("LEFT") then
        transform.x = transform.x - controller.speed * dt
    end
    if isKeyPressed("RIGHT") then
        transform.x = transform.x + controller.speed * dt
    end

    aabb.x = transform.x
    aabb.y = transform.y
    aabb.w = transform.w
    aabb.h = transform.h
end
