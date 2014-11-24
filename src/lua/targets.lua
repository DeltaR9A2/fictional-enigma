print("Begin Lua Script: targets.lua");

add_fset("npc_sprites", "npc_sprites.png",  16,  8, false)
add_anim("npc_sprites", "npc_anarchy_f_l", 4,  1,  8, false)
add_anim("npc_sprites", "npc_vending_machine_broken", 5, 1, 8, false)
add_anim("npc_sprites", "npc_vending_machine_working", 6, 2, 8, false)

add_fset("item_sprites", "item_sprites.png", 16, 16, false)
add_anim("item_sprites", "item_money_bag", 0, 1, 8, false)

add_fset("fx_sprites", "fx_ice_spike.png", 8, 1, false)
add_anim("fx_sprites", "fx_ice_spike", 0, 8, 12, false)

anarchy = "portrait_anarchy_default.png"
frost = "portrait_frost_default.png"

function dialogue_tutorial()
	print("Tutorial dialogue activated.");
	simple_dialogue(anarchy, "Tutorial dialogue.");
end

function dialogue_broken_vending_machine()
	simple_dialogue(frost, "... seems broken.");
end

add_event("dialogue_anarchy_tutorial", "dialogue_tutorial");
add_event("dialogue_broken_vending_machine", "dialogue_broken_vending_machine");

add_target("npc_tutorial_anarchy", 64, 128+8, "npc_anarchy_f_l", "dialogue_anarchy_tutorial");
add_target("npc_tutorial_broken_vending_machine", 512, 64+8, "npc_vending_machine_broken", "dialogue_broken_vending_machine");


