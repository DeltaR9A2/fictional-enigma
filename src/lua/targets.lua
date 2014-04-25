
add_fset("npc_sprites", "npc_sprites.png",  16,  8, false)
add_anim("npc_sprites", "npc_anarchy_f_l", 3,  1,  8)

anarchy = "portrait_anarchy_default.png"
frost = "portrait_frost_default.png"

configure_target(0xDDCC00FF, "npc_anarchy_f_l", anarchy, "What are YOU looking at?");
configure_target(0xFF00FFFF, "npc_anarchy_f_l", frost, "... seems broken.");
configure_target(0x55DDCCFF, "npc_anarchy_f_l", frost, "Looks like this one still works.");

