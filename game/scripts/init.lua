local greeter = require("scripts.greet-world")
local controller = require("scripts.controller")
local aabb = require("scripts.aabb")
local move_enemy = require("scripts.move_enemy")

local initialized = false

function update(dt)

    if not initialized then
        local entities = world.active():getEntities()
        local player = nil
        local camera = nil
        for _, entity in ipairs(entities) do
            local name = entity:get("Name")
            if not name then goto continue end

            if name.name == "player" then player = entity end
            if name.name == "camera" then camera = entity end

            ::continue::
        end

        assert(player, "no player entity!")
        assert(camera, "no camera entity!")

        place_player(camera, player)

        initialized = true
    end

    controller(dt)
    move_enemy()
    aabb(dt)
    greeter()
end
