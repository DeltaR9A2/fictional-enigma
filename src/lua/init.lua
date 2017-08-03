
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

function dialogue_event_func(config)
	print(config);
	simple_dialogue(table.unpack(dialogue_event_data[config]));
end

function message_event_func(config)
	simple_message(config);
end

function goto_func(config)
	dofile("map_" .. config .. ".lua")
end

dofile("pcs.lua")
dofile("npcs.lua")

dofile("map_test.lua")
dofile("map_room_001.lua")
