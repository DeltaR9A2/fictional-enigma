
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



dofile("pcs.lua")
dofile("npcs.lua")

links = {
--name = {map_name, target_name}
	room_001_to_room_002 = {"room_002", "door_to_room_001"},
	room_002_to_room_001 = {"room_001", "door_to_room_002"}
}

function door_func(config)
	print("Door: " .. config)
	print(table.unpack(links[config]))
	move_player_to_map(links[config][1])
	move_player_to_target(links[config][2])
end

function add_door(map_a, xa, ya, map_b, xb, yb)
--	door_name = map_a .. "_" .. xa .. "_" .. ya .. "_" .. map_b .. "_" .. xb .. "_" .. yb
	door_name = map_a .. "_" .. map_b .. "_door"
	event_name = door_name .. "_event"
	target_name = door_name .. "_target"
	link_a_name = door_name .. "_forward"
	link_b_name = door_name .. "_reverse"

	print("Adding door " .. door_name);

	edit_map(map_a)
	add_event(event_name .. "_a", "door_func", link_a_name);
	add_target(target_name, xa,  ya, "npc_door", event_name .. "_a");
	links[link_a_name] = {map_b, door_name .. "_target"}

	edit_map(map_b)
	add_event(event_name .. "_b", "door_func", link_b_name);
	add_target(target_name, xb,  yb, "npc_door", event_name .. "_b");
	links[link_b_name] = {map_a, door_name .. "_target"}
end


add_map("room_001", "map_room_001.png", "map_room_001_image.png")
add_map("room_002", "map_room_002.png", "map_room_002_image.png")
add_map("test_map", "map_test.png", "map_test_image.png")

add_door("room_001", 64, 192, "room_002", 192, 192);
add_door("room_002", 64, 192, "test_map", 92, 92);
move_player_to_map("room_001")
--dofile("map_test.lua")
--dofile("map_room_001.lua")
