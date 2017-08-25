
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

function do_nothing(config) end

add_event("none", "do_nothing", "")

dofile("pcs.lua")
dofile("npcs.lua")

dofile("doors.lua")

--add_map("room_001", "map_room_001.png", "map_room_001_image.png")
--add_map("room_002", "map_room_002.png", "map_room_002_image.png")
add_map("test_map", "map_test.png", "map_test_image.png")
add_map("s2u", "map_shortcut_storage_to_utility.png", "map_shortcut_storage_to_utility_image.png");

--add_door("room_001", 64, 184, "room_002", 192, 184);
--add_door("room_002", 64, 184, "test_map", 96, 128);

add_door("test_map", 296, 1264, "s2u", 32, 128);
add_door("test_map", 1360, 136, "s2u", 208, 72);
add_door("test_map", 1840, 1184, "s2u",  208, 192);

--add_door("test_map", 256, 128, "test_map", 1500, 128);

dofile("map_test.lua")

move_player_to_map("test_map")
move_player_to_target("new_game_spawn");
--dofile("map_room_001.lua")
