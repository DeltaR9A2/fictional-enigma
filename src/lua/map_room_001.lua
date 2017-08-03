load_map("map_room_001.png", "map_room_001_image.png")

add_event("goto_room_002", "goto_func", "room_002");
add_target("npc_door_to_room_002", 64,  192, "npc_door", "goto_room_002");

move_player_to_target("npc_door_to_room_002")
