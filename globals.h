#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#include "framework.h"
#include "color.h"

typedef struct _settings
{
	bool b_menuEnable = false;
	bool b_debugEnable = true;
	bool b_textinputnInfo = false;
	bool b_map = false;
	bool b_fov = false;
	bool b_no_flashbang = false;
	bool b_hearbeat = false;
	bool b_custom_clantag = false;
	bool b_brightmax = false;
	bool b_thridperson = false;
	bool b_sprint = false;
	bool b_ingame = false;
	bool b_box = false;
	bool b_line = false;
	bool b_names = false;
	bool b_crosshair = false;
	bool b_skeleton = false;
	bool b_friendly = false;
	bool b_distance = false;
	bool b_visible = false;
	bool b_visible_only = false;
	bool b_norecoil = false;
	bool b_nospread = false;
	bool b_health = false;
	bool b_no_stun = false;
	bool b_shield = false;
	bool b_owner = false;


	int gamemode = 0;
	int max_distance = 250;
	int player_max = 1;
	int box_options = 1;
	int bone_index = 1;

	float f_fov = 1.20f;
	float f_map = 1.0f;
	float bone_size = 2.f; // 0 ~ 5
	float font_size = 16.f;
	int i_score = 9468484; //1 ~ 5555555555
	int i_timeplayed = 778987889;
	int i_games = 55658; //1 ~ 5555555555
	int i_wins = 7468484; //1 ~ 5555555555
	int i_kills = 5248627; //1 ~ 5555555555
	int i_deaths = 1254876; //1 ~ 5555555555
	int i_downs = 17254876; //1 ~ 5555555555;
	int i_top5 = 8598452; //1 ~ 5555555555
	int i_top10 = 5584590; //1 ~ 5555555555
	int i_top25 = 85894557; //1 ~ 5555555555

	utils::color_var White = utils::color_var(C_Color(255, 255, 255));
	utils::color_var Black = utils::color_var(C_Color(0, 0, 0));
	utils::color_var Red = utils::color_var(C_Color(255, 0, 0));
	utils::color_var Green = utils::color_var(C_Color(0, 255, 0));
	utils::color_var Blue = utils::color_var(C_Color(0, 0, 255));
	utils::color_var visible_team_color = utils::color_var(C_Color(0, 0, 255));
	utils::color_var visible_box_color = utils::color_var(C_Color(0, 255, 0));
	utils::color_var visible_bone_color = utils::color_var(C_Color(0, 255, 0));
	utils::color_var visible_line_color = utils::color_var(C_Color(0, 255, 0));
	utils::color_var n_visilbe_team_color = utils::color_var(C_Color(255, 255, 255));
	utils::color_var n_visible_box_color = utils::color_var(C_Color(255, 0, 0));
	utils::color_var n_visible_bone_color = utils::color_var(C_Color(255, 0, 0));
	utils::color_var n_visible_line_color = utils::color_var(C_Color(255, 0, 0));
	utils::color_var name_color = utils::color_var(C_Color(255, 255, 0));
	utils::color_var dis_color = utils::color_var(C_Color(255, 255, 0));
	utils::color_var fov_color = utils::color_var(C_Color(255, 255, 255));
	utils::color_var crosshair_color = utils::color_var(C_Color(255, 255, 255));
	utils::color_var cash_color = utils::color_var(C_Color(0, 255, 0));
	utils::color_var ammo_color = utils::color_var(C_Color(255, 255, 255));
	utils::color_var ammo_create_color = utils::color_var(C_Color(255, 255, 255));
	utils::color_var weapon_color = utils::color_var(C_Color(255, 255, 255));
	utils::color_var ncrate = utils::color_var(C_Color(0, 0, 255));
	utils::color_var lcrate = utils::color_var(C_Color(255, 128, 0));
	utils::color_var mission_color = utils::color_var(C_Color(102, 178, 255));
	utils::color_var killstreak_color = utils::color_var(C_Color(153, 51, 255));

}settings;

typedef struct _offsets
{
	void* rbx_jmp;
	uintptr_t jmp_rbx;
	uintptr_t logonstatus = 0x6116f90;
	uintptr_t gamemode = 0x154E4CB8;
	uintptr_t entitiespos_ptr = 0x4c619c0;
	uintptr_t distribute = 0x18114528;
	uintptr_t visible = 0x68AA110;
	uintptr_t refdef_ptr = 0x159E5EA8;
	uintptr_t camera_ptr = 0x12EFD4A0;
	uintptr_t camere_view = 0x1E8;
	uintptr_t camera_view_x = 0x108;
	uintptr_t camera_view_y = 0x118;
	uintptr_t camera_view_z = 0x128;
	uintptr_t client_local_index = 0x204;
	uintptr_t c_client_offset = 0x4C70;
	uintptr_t client_health = 0x8C;
	uintptr_t local_index_offset = 0x32168;
	uintptr_t name_array = 0x14D69F70;
	uintptr_t c_size = 0x60B8;
	uintptr_t c_valid = 0xb0;
	uintptr_t c_teamid = 0x688;
	uintptr_t c_entity_index = 0xCB0;
	uintptr_t c_position = 0x2C0;
	uintptr_t c_stance = 0xD60;
	uintptr_t c_death1 = 0x220;
	uintptr_t c_death2 = 0x48;
	uintptr_t game_return = 0x62fb89d;
	uintptr_t client_encrypted_ptr = 0x153EA528;
	uintptr_t client_base = 0xAE860;
	uintptr_t bone_encrypted_ptr = 0x12E861B8;
	uintptr_t bone_base = 0x57224;
	uintptr_t clantag = 0x0;
	uintptr_t norecoil = 0x0;
	uintptr_t ddl_loadasset = 0x0;
	uintptr_t ddl_getrootstate = 0x0;
	uintptr_t ddl_getdllbuffer = 0x0;
	uintptr_t ddl_movetoname = 0x0;
	uintptr_t ddl_movetopath = 0x0;
	uintptr_t ddl_setint = 0x0;
	uintptr_t ddl_setstring = 0x0;
	uintptr_t ddl_parse = 0x0;
	uintptr_t unlock_offsets = 0x0;
	uintptr_t Dvar_FindVarByName = 0x0;
	uintptr_t Dvar_SetBoolInternal = 0x0;
	uintptr_t Dvar_SetBoolByName = 0x0;
	uintptr_t Dvar_SetFloat_Internal = 0x0;
	uintptr_t Dvar_RegisterFloat = 0x0;
	uintptr_t Dvar_SetInt_Internal = 0x0;
	uintptr_t Dvar_SetIntByName = 0x0;
	
}offsets;

typedef struct _cached
{
	uintptr_t local_ptr = 0;
	uintptr_t player_ptr = 0;
	uintptr_t cached_bone_ptr = 0;
	uintptr_t cached_character_ptr = 0;
	uintptr_t cached_base_ptr = 0;
	uintptr_t cached_entity_ptr = 0;
	uintptr_t inputptr = 0;
	uintptr_t entity_ptr = 0;
	uintptr_t bone_tagPos_ptr = 0;
	uintptr_t current_visible_offset = 0;
	uintptr_t cached_visible_base = 0;
	uintptr_t last_visible_offset = 0;
	int local_team_id = 0;
	int player_team_id = 0;
	int local_index = 0;
	bool b_is_localalive = false;
	bool b_is_playeralive = false;
	bool bone_tagPos = false;
	bool is_friendly = false;

} cached;

typedef struct _globals_vars
{
	uintptr_t baseModule;
	HWND hWind;
	HANDLE hProc;
	DWORD procId;
	offsets goffsets;
	settings msettings;
	cached gcached;

} global_vars;

extern global_vars* g_vars;

#endif // !GLOBAL_H
