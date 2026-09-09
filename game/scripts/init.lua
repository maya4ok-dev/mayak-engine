local controller = require("scripts.controller")
local greeter = require("scripts.greet-world")
local rotater = require("scripts.rotate")

local controller_component = nil
local speed_was_printed = false

function update(dt)
    if not controller_component then
        controller_component = Controller.new()
        controller_component.speed = 300
    end

    if not speed_was_printed then
        print("speed is " .. controller_component.speed)
        speed_was_printed = true
    end

    controller(dt)
    greeter(dt)
    rotater(dt)
end
