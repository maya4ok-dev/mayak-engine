local entities = world.active():getEntities()
local greeter = require("scripts.greet-world")
local controller = require("scripts.controller")

local debug = false

function update(dt)
    controller(dt)
    if not debug then
        for _, entity in ipairs(entities) do
            local controller = entity:get("Controller")
            local name = entity:get("Name")

            if not controller or not name then
                print("entity is missing components!")

                if not name then print("no name!") end
                if not controller then print("no controller!") end

                goto continue
            end

            print("entity: " .. name.name .. "; speed: " .. controller.speed)

            ::continue::
        end

        debug = true
    end

    greeter(dt)
end
