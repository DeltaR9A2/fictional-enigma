print("Begin Lua Script: pcs.lua");

static_framesets = {
    {"p_frost_f_r", "player_frost_female.png",  8,  8, false},
    {"p_frost_f_l", "player_frost_female.png",  8,  8, true },

    {"p_generic_r", "player_generic.png",  8,  8, false},
    {"p_generic_l", "player_generic.png",  8,  8, true }
}

static_animations = {
    {"p_frost_f_r", "frost_f_idle_r",  0,  4,  5},
    {"p_frost_f_r", "frost_f_move_r",  8,  8, 10},
    {"p_frost_f_r", "frost_f_jump_r", 16,  2,  8},
    {"p_frost_f_r", "frost_f_hang_r", 18,  2,  8},
    {"p_frost_f_r", "frost_f_fall_r", 20,  2,  8},
    {"p_frost_f_r", "frost_f_skid_r", 22,  2,  8},

    {"p_frost_f_l", "frost_f_idle_l",  0,  4,  5},
    {"p_frost_f_l", "frost_f_move_l",  8,  8, 10},
    {"p_frost_f_l", "frost_f_jump_l", 16,  2,  8},
    {"p_frost_f_l", "frost_f_hang_l", 18,  2,  8},
    {"p_frost_f_l", "frost_f_fall_l", 20,  2,  8},
    {"p_frost_f_l", "frost_f_skid_l", 22,  2,  8},


    {"p_generic_r", "generic_idle_r",  0,  1.0,  5},
    {"p_generic_r", "generic_move_r",  8,  6, 10},
    {"p_generic_r", "generic_jump_r", 16,  1,  8},
    {"p_generic_r", "generic_hang_r", 18,  1,  8},
    {"p_generic_r", "generic_fall_r", 20,  1,  8},
    {"p_generic_r", "generic_skid_r", 22,  1,  8},

    {"p_generic_l", "generic_idle_l",  0,  1.0,  5},
    {"p_generic_l", "generic_move_l",  8,  6, 10},
    {"p_generic_l", "generic_jump_l", 16,  1,  8},
    {"p_generic_l", "generic_hang_l", 18,  1,  8},
    {"p_generic_l", "generic_fall_l", 20,  1,  8},
    {"p_generic_l", "generic_skid_l", 22,  1,  8}
}

-- Welcome to the Blender
for i, row in ipairs(static_framesets) do
  print("add_fset", table.unpack(row));
	add_fset(table.unpack(row))
end
-- VrrrrRRRrrrrRRRRrrrrrrrrr....
for i, row in ipairs(static_animations) do
  print("add_anim", table.unpack(row));
	add_anim(table.unpack(row))
end
