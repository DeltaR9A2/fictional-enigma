
--[[

select_zone(name)
load_map(image)

add_fset(name, image, cols, rows, flip)
add_anim(fset, name, start, length, fps)

add_event(name, func_name, string)
add_target(name, x, y, sprite, event)
add_trigger(name, x, y, w, h, event)

--]]

function dialogue_event_func(config)
	print(config);
	simple_dialogue(table.unpack(dialogue_event_data[config]));
end

function message_event_func(config)
	simple_message(config);
end

function do_nothing(config) end

add_event("none", "do_nothing", "");

print("Begin Lua Script: pcs.lua");


add_fset("p_generic_r", "player_generic.png",  8,  8, false);
add_fset("p_generic_l", "player_generic.png",  8,  8, true );

add_anim("p_generic_r", "generic_idle_r",  0,  1,  5);
add_anim("p_generic_r", "generic_move_r",  8,  6, 10);
add_anim("p_generic_r", "generic_jump_r", 16,  1,  8);
add_anim("p_generic_r", "generic_hang_r", 18,  1,  8);
add_anim("p_generic_r", "generic_fall_r", 20,  1,  8);
add_anim("p_generic_r", "generic_skid_r", 22,  1,  8);

add_anim("p_generic_l", "generic_idle_l",  0,  1,  5);
add_anim("p_generic_l", "generic_move_l",  8,  6, 10);
add_anim("p_generic_l", "generic_jump_l", 16,  1,  8);
add_anim("p_generic_l", "generic_hang_l", 18,  1,  8);
add_anim("p_generic_l", "generic_fall_l", 20,  1,  8);
add_anim("p_generic_l", "generic_skid_l", 22,  1,  8);

add_fset("npc_sprites", "npc_sprites.png",  16,  8, false)

add_anim("npc_sprites", "npc_door",        64, 1, 1);
add_anim("npc_sprites", "npc_spawn_point", 65, 1, 1);

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

add_map("test_map", "map_test.png", "map_test_image.png")
add_map("s2u", "map_shortcut_storage_to_utility.png", "map_shortcut_storage_to_utility_image.png");

add_door("test_map", 296, 1264, "s2u", 32, 128);
add_door("test_map", 1360, 136, "s2u", 208, 72);
add_door("test_map", 1840, 1184, "s2u",  208, 192);

edit_map("test_map");

add_target("new_game_spawn", 200,  136, "npc_spawn_point", "none");

add_fset("item_sprites", "item_sprites.png", 16, 16, false)

--add_anim(fset, name, start, length, fps)
add_anim("item_sprites", "item_money_bag",  0, 1, 8)
add_anim("item_sprites", "item_candy",      1, 1, 8)
add_anim("item_sprites", "item_heart",      2, 1, 8)
add_anim("item_sprites", "item_star",       3, 1, 8)
add_anim("item_sprites", "item_star_angry", 4, 1, 8)
add_anim("item_sprites", "item_gear_big",   5, 1, 8)
add_anim("item_sprites", "item_gear",       6, 1, 8)

for i=1, 16 do add_item(1400 + i*16, 100, "item_gear") end
add_item(1050, 400, "item_gear");
for i=1, 3 do add_item(1900 + i*16, 740, "item_gear") end


move_player_to_map("test_map")
move_player_to_target("new_game_spawn");

