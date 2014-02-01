
static_framesets = {
    {"p_frost_f_r", "player_frost_female.png",  8,  8, false},
    {"p_frost_f_l", "player_frost_female.png",  8,  8, true },
}

static_animations = {
    {"p_frost_f_r", "frost_f_idle_r",  0,  4,  5},
    {"p_frost_f_r", "frost_f_duck_r",  4,  4,  5},
    {"p_frost_f_r", "frost_f_move_r",  8,  8, 10},
    {"p_frost_f_r", "frost_f_jump_r", 16,  2,  8},
    {"p_frost_f_r", "frost_f_hang_r", 18,  2,  8},
    {"p_frost_f_r", "frost_f_fall_r", 20,  2,  8},
    {"p_frost_f_r", "frost_f_skid_r", 22,  2,  8},

    {"p_frost_f_l", "frost_f_idle_l",  0,  4,  5},
    {"p_frost_f_l", "frost_f_duck_l",  4,  4,  5},
    {"p_frost_f_l", "frost_f_move_l",  8,  8, 10},
    {"p_frost_f_l", "frost_f_jump_l", 16,  2,  8},
    {"p_frost_f_l", "frost_f_hang_l", 18,  2,  8},
    {"p_frost_f_l", "frost_f_fall_l", 20,  2,  8},
    {"p_frost_f_l", "frost_f_skid_l", 22,  2,  8},
}

for i, row in ipairs(static_framesets) do
	add_fset(unpack(row))
end

for i, row in ipairs(static_animations) do
	add_anim(unpack(row))
end
