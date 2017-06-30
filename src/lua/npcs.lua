

add_fset("npc_sprites", "npc_sprites.png",  16,  8, false)

npc_sprite_data = {
	{"npc_anarchy",    0, 1, 1},
	{"npc_biohazard",  1, 1, 1},
	{"npc_danger",     2, 1, 1},
	{"npc_radiation",  3, 1, 1},
	{"npc_frost",      4, 1, 1},
	{"npc_heart",      5, 1, 1},
	{"npc_pentagram",  6, 1, 1},
	{"npc_venus",      7, 1, 1},
	{"npc_vitae",      8, 1, 1},
	{"npc_009",        9, 1, 1},
	{"npc_010",       10, 1, 1},
	{"npc_011",       11, 1, 1},
	{"npc_012",       12, 1, 1},
	{"npc_013",       13, 1, 1}
}

for i, row in ipairs(npc_sprite_data) do
	add_anim("npc_sprites", table.unpack(row));
end

