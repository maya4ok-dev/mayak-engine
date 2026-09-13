local entities = world.active():getEntities()
local greeter = require("scripts.greet-world")

local debug = false

function update(dt)
    if not debug then
        for _, entity in ipairs(entities) do
            local controller = entity_get_component(entity, "Controller")
            local name = entity_get_component(entity, "Name")
            if not controller or not name then goto continue end
            print("speed of " .. name.name .. ": " .. controller.speed)
            ::continue::
        end

        debug = true
    end

    greeter(dt)
end
