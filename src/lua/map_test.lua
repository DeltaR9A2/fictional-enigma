print("Begin Lua Script: map_test.lua");

edit_map("test_map");

add_fset("item_sprites", "item_sprites.png", 16, 16, false)
add_anim("item_sprites", "item_money_bag", 0, 1, 8, false)
add_anim("item_sprites", "item_candy", 1, 1, 8, false)
add_anim("item_sprites", "item_heart", 2, 1, 8, false)
add_anim("item_sprites", "item_star", 3, 1, 8, false)

-- add_item(200, 100, "item_candy");
for i=1, 16 do add_item(1400 + i*16, 100, "item_candy") end

add_item(1050, 400, "item_candy");

for i=1, 3 do add_item(1900 + i*16, 740, "item_candy") end

add_fset("fx_sprites", "fx_ice_spike.png", 8, 1, false)
add_anim("fx_sprites", "fx_ice_spike", 0, 8, 12, false)

anarchy = "portrait_anarchy_default.png"
biohazard = "portrait_biohazard_default.png"
danger = "portrait_danger_default.png"
radiation = "portrait_placeholder.png"
frost = "portrait_frost_default.png"
heart = "portrait_heart_default.png"
pentagram = "portrait_placeholder.png"
venus = "portrait_venus_default.png"

dialogue_event_data = {
--	[config string] = {portrait, dialogue text}

	["tutorial_anarchy"]   = {anarchy,   "Use the Z key to interact with 'targets'. Targets include things like people, doors, switches, and more."},
	["tutorial_biohazard"] = {biohazard, "You have mastered the art of jumping. Now try falling down through these platforms."},
	["tutorial_danger"]    = {danger,    "Tutorial dialogue 003."},
	["tutorial_radiation"] = {radiation, "Tutorial dialogue 004."},
	["tutorial_frost"]     = {frost,     "This pit is wide enough that you can barely jump across. It's also deep enough that you can't jump out on the other side."},
	["tutorial_heart"]     = {heart,     "You must've made the jump over that pit, huh? Impressive. ... Or did you take the long way around?"},
	["tutorial_pentagram"] = {pentagram, "Tutorial dialogue 007."},
	["tutorial_venus"]     = {venus,     "Tutorial dialogue 008."}
}

add_event("dialogue_tutorial_anarchy",   "dialogue_event_func", "tutorial_anarchy");
add_event("dialogue_tutorial_biohazard", "dialogue_event_func", "tutorial_biohazard");
add_event("dialogue_tutorial_danger",    "dialogue_event_func", "tutorial_danger");
add_event("dialogue_tutorial_radiation", "dialogue_event_func", "tutorial_radiation");
add_event("dialogue_tutorial_frost",     "dialogue_event_func", "tutorial_frost");
add_event("dialogue_tutorial_heart",     "dialogue_event_func", "tutorial_heart");
add_event("dialogue_tutorial_pentagram", "dialogue_event_func", "tutorial_pentagram");
add_event("dialogue_tutorial_venus",     "dialogue_event_func", "tutorial_venus");

add_target("npc_dta", 64,  128+8, "npc_anarchy", "dialogue_tutorial_anarchy");
add_target("npc_dtb", 512, 64+8,  "npc_biohazard",   "dialogue_tutorial_biohazard");
add_target("npc_dtd", 512, 320+8,  "npc_danger",   "dialogue_tutorial_danger");
add_target("npc_dtr", 160, 320+8,  "npc_radiation",   "dialogue_tutorial_radiation");
add_target("npc_dtf", 272, 640+8,  "npc_frost",   "dialogue_tutorial_frost");
add_target("npc_dth", 552, 640+8,  "npc_heart",   "dialogue_tutorial_heart");
add_target("npc_dtp", 800, 64+8,  "npc_pentagram",   "dialogue_tutorial_pentagram");
add_target("npc_dtv", 1232, 64+8,  "npc_venus",   "dialogue_tutorial_venus");

add_target("new_game_spawn", 200,  128, "npc_spawn_point", "none");

