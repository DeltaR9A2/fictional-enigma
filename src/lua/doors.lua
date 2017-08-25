local links = {
--name = {map_name, target_name}
}


function door_func(config)
	print("Door: " .. config)
	print(table.unpack(links[config]))
	move_player_to_map(links[config][1])
	move_player_to_target(links[config][2])
end

local door_number = 1;

function add_door(map_a, xa, ya, map_b, xb, yb)
--	door_name = map_a .. "_" .. xa .. "_" .. ya .. "_" .. map_b .. "_" .. xb .. "_" .. yb
--	door_name = map_a .. "_" .. map_b .. "_door"

	door_number = door_number + 1;

	door_name = "door_" .. door_number
	event_name = door_name .. "_event"
	target_name = door_name .. "_target"
	link_name = door_name .. "_link"

	print("Adding door " .. door_name);

	edit_map(map_a)
	add_event(event_name .. "_a", "door_func", link_name .. "_a");
	add_target(target_name .. "_a", xa,  ya, "npc_door", event_name .. "_a");
	links[link_name .. "_a"] = {map_b, target_name .. "_b"}

	edit_map(map_b)
	add_event(event_name .. "_b", "door_func", link_name .. "_b");
	add_target(target_name .. "_b", xb,  yb, "npc_door", event_name .. "_b");
	links[link_name .. "_b"] = {map_a, target_name .. "_a"}
end


