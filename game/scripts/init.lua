local greeter = require("scripts.greet-world")
local controller = require("scripts.controller")
local follow = require("scripts.follow")

function update(dt)
    controller(dt)
    follow()
    greeter()
end
