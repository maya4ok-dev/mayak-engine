-- for now, it won't work because entity_get_component returns a table copy

local entities = world.active():getEntities()

local controller = nil
local transform = nil

for _, entity in ipairs(entities) do
    if name ~= "player" then goto continue end

    controller = entity_get_component(entity, "Controller")
    transform = entity_get_component(entity, "Transform")

    ::continue::
end

return function(dt)
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
end
