local objects = getObjects()
local time = 0
local startposes = {}

for i, object in ipairs(objects) do
    startposes[i] = {
        startX = object.posX,
        startY = object.posY
    }
end

function update(dt)
    time = time + dt

    for obj_i, object in ipairs(objects) do
        for _, tag in ipairs(object.tags) do
            if tag ~= "rotatable" then goto continue end

            start = startposes[obj_i]

            object.posX = start.startX + math.sin(time) * 100
            object.posY = start.startY + math.cos(time) * 100

            ::continue::
        end
    end
end
