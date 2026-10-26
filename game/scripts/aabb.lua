local player_hitbox = nil
local enemy_hitboxes = {}
local initialized = false
local intersected_once = false

return function()
    if not initialized then
        local entities = world.active():getEntities()
        for _, entity in ipairs(entities) do
            local name = entity:get("Name")
            if not name then goto continue end

            if name.name == "player" then
                player_hitbox = entity:get("AABB")
            elseif name.name == "enemy" then
                table.insert(enemy_hitboxes, entity:get("AABB"))
            end

            ::continue::
        end

        initialized = true
    end

    assert(player_hitbox, "player AABB not found")
    assert(#enemy_hitboxes > 0, "no enemies")

    local intersecting = false

    for _, enemy_hitbox in ipairs(enemy_hitboxes) do
        if player_hitbox:intersects(enemy_hitbox) then
            intersecting = true
            break
        end
    end

    if intersecting ~= intersected_once then
        print(intersecting and "intersecting!" or "not intersecting!")
        intersected_once = intersecting
    end
end
