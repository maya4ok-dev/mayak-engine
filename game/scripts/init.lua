local greeter = require("scripts.greet-world")
local controller = require("scripts.controller")
local aabb = require("scripts.aabb")

function update(dt)
    controller(dt)
    aabb()
    greeter()
end
