
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

configure_target(0xDDCC00FF, "npc_anarchy_f_l", anarchy, "What are YOU looking at?");
configure_target(0xFF00FFFF, "fx_ice_spike", frost, "... seems broken.");
configure_target(0x55DDCCFF, "npc_vending_machine_working", frost, "Looks like this one still works.");
configure_target(0xAA0000FF, "item_money_bag", frost, "Is this... a bag of money..?");

