load_map("map_room_002.png", "map_room_002_image.png")

add_event("goto_room_001", "goto_func", "room_001");
add_target("npc_door_to_room_001", 256-64,  192, "npc_door", "goto_room_001");

move_player_to_target("npc_door_to_room_001")

