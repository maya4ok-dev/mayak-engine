local player_hitbox = nil
local enemy_hitbox = nil
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
                enemy_hitbox = entity:get("AABB")
            end

            ::continue::
        end
        initialized = true
    end

    assert(player_hitbox, "player AABB not found")
    assert(enemy_hitbox, "enemy AABB not found")


    local intersecting = player_hitbox:intersects(enemy_hitbox)

    if intersecting ~= intersected_once then
        print(intersecting and "intersecting!" or "not intersecting!")
        intersected_once = intersecting
    end
end
