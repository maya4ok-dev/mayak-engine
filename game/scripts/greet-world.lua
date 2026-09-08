local greeted = false

return function(dt) 
    if not greeted then 
        print("Hello, World!")
        greeted = true
    end
end
