[x] integrate mayak::logger instead of old one
[x] figure out why graphics don't work
    - because removing the old logger caused the whole texture loading block to become the `if` body
[ ] load only main.lua file, not all in the scripts/ directory
[ ] add setup() function to scripts
[ ] implement a mini ecs using polymorphism
[ ] look up if SDL_GetScancodeFromName can be used instad of keyMap
[x] replace old DIM with World, make it less cringy
[ ] wrap up every engine component into engine:: namespace
[ ] make a mega premium ultra production-ready sample which doesn't make me cry at least
[ ] implement camera
    - [ ] make the World endless or at least configurable
