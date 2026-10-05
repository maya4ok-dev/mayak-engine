local transform = nil
local dead_width = nil
local dead_height = nil
local initialized = false

local DEAD_SCALE = 0.6

return function()
    if not initialized then
        dead_width = camera.active.w * DEAD_SCALE
        dead_height = camera.active.h * DEAD_SCALE

        entities = world.active():getEntities()
        for _, entity in ipairs(entities) do
            name = entity:get("Name")
            if not name or name.name ~= "player" then goto continue end
            
            transform = entity:get("Transform")

            ::continue::
        end
        initialized = true
    end

    local left = camera.active.x + (camera.active.w - dead_width) / 2
    local right = camera.active.x + (camera.active.w + dead_width) / 2
    local top = camera.active.y + (camera.active.h - dead_height) / 2
    local bottom = camera.active.y + (camera.active.h + dead_height) / 2

    if transform.x < left then
        camera.active.x = math.floor(camera.active.x - (left - transform.x))
    end
    if (transform.x + transform.w) > right then
        camera.active.x = math.floor(camera.active.x + ((transform.x + transform.w) - right))
    end
    if transform.y < top then
        camera.active.y = math.floor(camera.active.y - (top - transform.y))
    end
    if (transform.y + transform.h) > bottom then
        camera.active.y = math.floor(camera.active.y + ((transform.y + transform.h) - bottom))
    end

end
