local greeted = false

return function() 
    if not greeted then 
        print("Hello, World!")
        greeted = true
    end
end
