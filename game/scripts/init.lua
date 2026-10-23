local greeter = require("scripts.greet-world")
local controller = require("scripts.controller")
local follow = require("scripts.follow")
local aabb = require("scripts.aabb")

function update(dt)
    controller(dt)
    aabb()
    follow()
    greeter()
end
