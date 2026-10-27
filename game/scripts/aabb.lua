local camera = nil
local player = nil
local player_hitbox = nil
local enemies = {}
local initialized = false

return function()
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
            print("intersecting!")
            intersecting = true
            break
        end
    end

    if intersecting then
        for _, enemy in ipairs(enemies) do
            place_enemy(enemy.self)
        end
        place_player(camera, player)
    end

end
