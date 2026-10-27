local camera = nil
local player = nil
local player_hitbox = nil
local enemies = {}

local survived = 0
local record = 0

local initialized = false

return function(dt)
    if not initialized then
        local entities = world.active():getEntities()
        for _, entity in ipairs(entities) do
            local name = entity:get("Name")
            if not name then goto continue end

            if name.name == "player" then
                player_hitbox = entity:get("AABB")
                player = entity
            elseif name.name == "enemy" then
                local enemy = {
                    self = entity,
                    hitbox = entity:get("AABB")
                }
                table.insert(enemies, enemy)
            elseif name.name == "camera" then
                camera = entity
            end

            ::continue::
        end

        initialized = true
    end

    assert(player_hitbox, "player AABB not found")
    assert(#enemies > 0, "no enemies")
    assert(camera, "no camera entity")

    local intersecting = false

    for _, enemy in ipairs(enemies) do
        if player_hitbox:intersects(enemy.hitbox) then
            intersecting = true
            break
        end
    end

    if intersecting then
        if survived > record then
            if record ~= 0 then print("you beat the record!") end
            record = survived
        end
        print(string.format("you survived for %.2f seconds", survived))

        survived = 0

        for _, enemy in ipairs(enemies) do
            place_enemy(enemy.self)
        end
        place_player(camera, player)
    else 
        survived = survived + dt
    end

end
