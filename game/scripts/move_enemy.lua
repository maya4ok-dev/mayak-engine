local enemies = {}

local initialized = false

return function()
    if not initialized then
        local entities = world.active():getEntities()
        for _, entity in ipairs(entities) do
            local name = entity:get("Name")
            if not name then goto continue end

            if name.name == "enemy" then
                local enemy = {
                    speed = entity:get("EnemySpeed"),
                    transform = entity:get("Transform"),
                    hitbox = entity:get("AABB")
                }
                table.insert(enemies, enemy)
            end

            ::continue::
        end

        initialized = true
    end

    for _, enemy in ipairs(enemies) do
        enemy.transform.x = enemy.transform.x + enemy.speed.x
        enemy.transform.y = enemy.transform.y + enemy.speed.y
        enemy.hitbox.x = enemy.transform.x
        enemy.hitbox.y = enemy.transform.y
    end
end

