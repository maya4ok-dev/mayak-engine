local hello = require("scripts.world-greeter")

local greeted = false

function update(dt) 
    if not greeted then 
        hello()
        greeted = true
    end
end
