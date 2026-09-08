local controller = require("scripts.controller")
local greeter = require("scripts.greet-world")
local rotater = require("scripts.rotate")

function update(dt)
    controller(dt)
    greeter(dt)
    rotater(dt)
end
