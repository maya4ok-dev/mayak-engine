local enemies = {}
local camera = nil

local initialized = false

return function()
    if not initialized then
        local entities = world.active():getEntities()
        for _, entity in ipairs(entities) do
            local name = entity:get("Name")
            if not name then goto continue end

            if name.name == "enemy" then
                local enemy = {
                    self = entity,
                    speed = entity:get("EnemySpeed"),
                    transform = entity:get("Transform"),
                    hitbox = entity:get("AABB")
                }
                table.insert(enemies, enemy)
            elseif name.name == "camera" then
                camera = entity:get("Camera")
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

        if (enemy.transform.x + enemy.transform.w) < 0
            or enemy.transform.x > camera.w
            or (enemy.transform.y + enemy.transform.h) < 0
            or enemy.transform.y > camera.h
        then place_enemy(enemy.self) end
    end
end

