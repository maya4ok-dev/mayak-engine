local greeter = require("scripts.greet-world")
local controller = require("scripts.controller")
local aabb = require("scripts.aabb")
local move_enemy = require("scripts.move_enemy")

function update(dt)
    controller(dt)
    move_enemy()
    aabb()
    greeter()
end
