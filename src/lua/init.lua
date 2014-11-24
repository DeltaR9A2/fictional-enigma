
--[[

select_zone(name)
load_map(image)

add_fset(name, image, cols, rows, flip)
add_anim(fset, name, start, length, fps)

add_event(name, func_name, string)
add_target(name, x, y, sprite, event)
add_trigger(name, x, y, w, h, event)

--]]

print("Begin Lua Script: init.lua");

load_map("test_map.png");

dofile("frost.lua")
dofile("targets.lua")
