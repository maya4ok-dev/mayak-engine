---@meta

---@class Entity
local Entity = {}

---@return table
---@param name string
function Entity:get(name) end

---@class World
local World = {}

---@return Entity[]
function World:getEntities() end

world = {}

---@return World
function world.active() end
