local transform = nil
local camera = nil
local dead_width = nil
local dead_height = nil
local initialized = false
local failed = false

local DEAD_SCALE = 0.6

return function()
    if not initialized and not failed then
        local entities = world.active():getEntities()

        for _, entity in ipairs(entities) do
            local name = entity:get("Name")

            if not name then goto continue end

            if name.name == "player" then
                transform = entity:get("Transform")
                if not transform then
                    print("[follow.lua] transform is nil!")
                end
            elseif name.name == "camera" then
                camera = entity:get("Camera")
                if not camera then
                    print("[follow.lua] no camera on entity camera!")
                end
            end

            ::continue::
        end

        if not camera or not transform then
            print("[follow.lua] no camera or transform, initialization failed!")
            failed = true
            return
        end

        dead_width = camera.w * DEAD_SCALE
        dead_height = camera.h * DEAD_SCALE

        initialized = true
        print("[follow.lua] initialized")
    end

    if failed then return end
    if not dead_width or not dead_height then return end
    if not camera or not transform then return end

    local left = camera.x + (camera.w - dead_width) / 2
    local right = camera.x + (camera.w + dead_width) / 2
    local top = camera.y + (camera.h - dead_height) / 2
    local bottom = camera.y + (camera.h + dead_height) / 2

    if transform.x < left then
        camera.x = math.floor(camera.x - (left - transform.x))
    end
    if (transform.x + transform.w) > right then
        camera.x = math.floor(camera.x + ((transform.x + transform.w) - right))
    end
    if transform.y < top then
        camera.y = math.floor(camera.y - (top - transform.y))
    end
    if (transform.y + transform.h) > bottom then
        camera.y = math.floor(camera.y + ((transform.y + transform.h) - bottom))
    end

end
