#include "sdk.h"
HWND process::hwnd;

BOOL CALLBACK process::EnumWindowCallBack(HWND hWnd, LPARAM lParam)
{
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWnd, &dwPid);
	if (dwPid == lParam)
	{
		hwnd = hWnd;
		return FALSE;
	}
	return TRUE;
}

HWND process::get_process_window()
{
	if (hwnd)
		return hwnd;

	EnumWindows(process::EnumWindowCallBack, GetCurrentProcessId());

	if (hwnd == NULL)
		Exit();

	return hwnd;
}

HWND process::get_process_window(DWORD procID)
{
	if (hwnd)
		return hwnd;

	EnumWindows(process::EnumWindowCallBack, procID);

	if (hwnd == NULL)
		Exit();

	return hwnd;
}

namespace sdk
{
	sdk::refdef_t* refdef = 0;

	int32_t cg_client::get_index()
	{

		if (!IsValidPtr<cg_client>(this))
			return 0;

		return *reinterpret_cast<int32_t*>((uintptr_t)this + g_vars->goffsets.c_entity_index);
	}

	bool cg_client::is_valid()
	{
		if (!IsValidPtr<cg_client>(this))
			return false;

		return *reinterpret_cast<bool*>((uintptr_t)this + g_vars->goffsets.c_valid);
	}

	bool cg_client::is_dead()
	{
		if (!IsValidPtr<cg_client>(this))
			return false;

		auto dead1 = *reinterpret_cast<bool*>((uintptr_t)this + g_vars->goffsets.c_death1);
		auto dead2 = *reinterpret_cast<bool*>((uintptr_t)this + g_vars->goffsets.c_death2);
		return !(!dead1 && !dead2 && is_valid());
	}

	int32_t cg_client::get_team_id()
	{
		if (!IsValidPtr<cg_client>(this))
			return 0;

		return *reinterpret_cast<int32_t*>((uintptr_t)this + g_vars->goffsets.c_teamid);
	}

	int32_t cg_client::get_stance()
	{
		if (!IsValidPtr<cg_client>(this))
			return 0;

		return *reinterpret_cast<int32_t*>((uintptr_t)this + g_vars->goffsets.c_stance);
	}

	uint64_t cg_client::get_pos()
	{
		if (!IsValidPtr<cg_client>(this))
			return 0;

		return *reinterpret_cast<uint64_t*>((uintptr_t)this + g_vars->goffsets.c_position);
	}

	cg_client* get_playerinfo(int entityNum)
	{
		uint64_t decryptedPtr = clientinfo_dec();
		if (is_valid_ptr(decryptedPtr))
		{
			uint64_t client_info = client_base_dec();
			if (is_valid_ptr(client_info))
			{
				return (cg_client*)(client_info + (entityNum * g_vars->goffsets.c_size));
			}
		}
		return 0;
	}

	cg_client* get_localentity()
	{
		uint64_t decryptedPtr = clientinfo_dec();
		if (is_bad_ptr(decryptedPtr))
			return 0;

		auto local_index = *(uint64_t*)(decryptedPtr + g_vars->goffsets.local_index_offset);

		if (is_bad_ptr(local_index))
			return 0;

		g_vars->gcached.local_index = *(int*)(local_index + g_vars->goffsets.client_local_index);

		return get_playerinfo(g_vars->gcached.local_index);
	}

	bool in_game()
	{
		return *reinterpret_cast<bool*>(g_vars->baseModule + g_vars->goffsets.gamemode + 0x4) > 0;
	}

	int get_max_player_acount()
	{
		return *(int*)(g_vars->baseModule + g_vars->goffsets.gamemode);
	}

	void clear_cached()
	{
		g_vars->gcached.cached_bone_ptr = 0;
		g_vars->gcached.cached_character_ptr = 0;
		g_vars->gcached.cached_base_ptr = 0;
		g_vars->gcached.local_ptr = 0;
		g_vars->gcached.local_index = 0;
		g_vars->gcached.cached_visible_base = 0;
		g_vars->gcached.current_visible_offset = 0;
		g_vars->gcached.last_visible_offset = 0;
		g_vars->gcached.player_ptr = 0;
		g_vars->gcached.bone_tagPos_ptr = 0;
		g_vars->gcached.local_team_id = 0;
		g_vars->gcached.cached_entity_ptr = 0;
		g_vars->msettings.player_max = 1;
	}

	refdef_t* get_refdef()
	{
		uint32_t crypt_0 = *(uint32_t*)(g_vars->baseModule + g_vars->goffsets.refdef_ptr);
		uint32_t crypt_1 = *(uint32_t*)(g_vars->baseModule + g_vars->goffsets.refdef_ptr + 0x4);
		uint32_t crypt_2 = *(uint32_t*)(g_vars->baseModule + g_vars->goffsets.refdef_ptr + 0x8);

		// lower 32 bits
		uint32_t entry_1 = (uint32_t)(g_vars->baseModule + g_vars->goffsets.refdef_ptr);
		uint32_t entry_2 = (uint32_t)(g_vars->baseModule + g_vars->goffsets.refdef_ptr + 0x4);

		// decryption
		uint32_t _low = entry_1 ^ crypt_2;
		uint32_t _high = entry_2 ^ crypt_2;

		uint32_t low_bit = crypt_0 ^ _low * (_low + 2);
		uint32_t high_bit = crypt_1 ^ _high * (_high + 2);

		auto unencrypted_refdef = ((QWORD)high_bit << 32) + low_bit;
		//LOG::log("ref_def: " + std::to_string(unencrypted_refdef));
		return (refdef_t*)(unencrypted_refdef);
	}

	int decrypt_visible_flag(int i, QWORD valid_list)
	{
		auto ptr = valid_list + ((static_cast<unsigned long long>(i) * 9 + 0x14e) * 8) + 0x10;
		uint64_t dw1 = (*(uint64_t*)(ptr + 4) ^ (uint64_t)ptr);
		uint64_t dw2 = ((dw1 + 2) * dw1);
		BYTE dec_visible_flag = *(BYTE*)(ptr) ^ BYTE1(dw2) ^ (BYTE)dw2;

		return (int)dec_visible_flag;
	}

	uint64_t get_visible_base(int i)
	{
		for (int j = 4000; j >= 0; j--)
		{
			uint64_t nIndex = (j + (static_cast<unsigned long long>(j) << 2)) << 0x6;
			uint64_t vis_base_ptr = *(uint64_t*)(g_vars->baseModule + g_vars->goffsets.distribute) + nIndex;
			uint64_t cmp_function = *(uint64_t*)(vis_base_ptr + 0x90);

			if (!cmp_function)
				continue;

			uint64_t about_visible = g_vars->baseModule + g_vars->goffsets.visible;
			if (cmp_function == about_visible)
			{
				uint64_t visible_head_offset = *(uint64_t*)(vis_base_ptr + 0x108);
				if (!visible_head_offset)
					continue;

				auto ptr = visible_head_offset + (static_cast<unsigned long long>(i) * 9 + 0x14e) * 8;
				if (!ptr)
					continue;

				uint64_t visible_flag = (ptr + 0x10) ^ *(uint64_t*)(ptr + 0x14);
				if (!visible_flag)
					continue;

				uint64_t dec_visible_flag = visible_flag * (visible_flag + 2);
				if (!dec_visible_flag)
					continue;

				BYTE visible_flags = *(uint64_t*)(ptr + 0x10) ^ dec_visible_flag ^ BYTE1(dec_visible_flag);

				if (visible_flags == 3)
				{
					g_vars->gcached.current_visible_offset = vis_base_ptr;
					return g_vars->gcached.current_visible_offset;
				}
			}
		}
		return 0;
	}

	bool is_visible(int i)
	{
		if (!g_vars->gcached.last_visible_offset)
			return false;

		uint64_t VisibleList = *(uint64_t*)(g_vars->gcached.last_visible_offset + 0x108);
		if (!VisibleList)
			return false;

		uint64_t rdx = VisibleList + (static_cast<unsigned long long>(i) * 9 + 0x14E) * 8;
		if (!rdx)
			return false;

		uint64_t VisibleFlags = (rdx + 0x10) ^ *(uint64_t*)(rdx + 0x14);
		if (!VisibleFlags)
			return false;

		uint64_t  v511 = VisibleFlags * (VisibleFlags + 2);
		if (!v511)
			return false;

		BYTE VisibleFlags1 = *(uint64_t*)(rdx + 0x10) ^ v511 ^ BYTE1(v511);
		if (VisibleFlags1 == 3) {
			return true;
		}
		return false;
	}

	void update_last_visible()
	{
		g_vars->gcached.last_visible_offset = g_vars->gcached.current_visible_offset;
	}

	bool get_bone_by_index(int i, int bone_id, Vector3* out_pos)
	{
		uint64_t decrypted_ptr = bone_dec(g_vars->baseModule);

		if (is_bad_ptr(decrypted_ptr))return false;

		unsigned int bone_index = bone_index_dec(i);

		if (bone_index != 0)
		{
			uint64_t bone_ptr = *(uint64_t*)(decrypted_ptr + (static_cast<unsigned long long>(bone_index) * 0x150) + 0xC0);

			if (is_bad_ptr(bone_ptr))return false;
			{
				uint64_t client_info = g_vars->gcached.cached_character_ptr;

				if (is_bad_ptr(client_info))return false;

				Vector3 bone_pos = *(Vector3*)(bone_ptr + (static_cast<unsigned long long>(bone_id) * 0x20) + 0x10);

				Vector3 BasePos = *(Vector3*)(client_info + g_vars->goffsets.bone_base);

				out_pos->x = bone_pos.x += BasePos.x;
				out_pos->y = bone_pos.y += BasePos.y;
				out_pos->z = bone_pos.z += BasePos.z;

				return true;
			}
		}

		return false;
	}

	int get_player_health(int entityNum)
	{
		uint64_t bgs = *(uint64_t*)(g_vars->baseModule + g_vars->goffsets.name_array);

		if (bgs)
		{

			name_t* pClientInfo = (name_t*)(bgs + g_vars->goffsets.c_client_offset + (entityNum * 0xD0));

			if (pClientInfo)
			{
				return pClientInfo->health;
			}
		}
		return 0;
	}

	std::string get_player_name(int entityNum)
	{
		uint64_t bgs = *(uint64_t*)(g_vars->baseModule + g_vars->goffsets.name_array);
		if (is_bad_ptr(bgs)) return "";

		if (bgs)
		{
			name_t* clientInfo_ptr = (name_t*)(bgs + g_vars->goffsets.c_client_offset + (static_cast<unsigned long long>(entityNum) * 0xD0));
			if (is_bad_ptr(clientInfo_ptr)) return "";

			int length = strlen(clientInfo_ptr->name);
			for (int j = 0; j < length; ++j)
			{
				char ch = clientInfo_ptr->name[j];
				bool is_english = ch >= 0 && ch <= 127;
				if (!is_english)
					return xorstr_("Player");
			}
			return clientInfo_ptr->name;
		}
		return xorstr_("Player");
	}

	void no_recoil()
	{
		uint64_t characterInfo_ptr = g_vars->gcached.cached_character_ptr;
		if (characterInfo_ptr)
		{
			// up, down
			QWORD r12 = characterInfo_ptr;
			r12 += g_vars->goffsets.norecoil;
			QWORD rsi = r12 + 0x4;
			DWORD edx = *(QWORD*)(r12 + 0xC);
			DWORD ecx = (DWORD)r12;
			ecx ^= edx;
			DWORD eax = (DWORD)((QWORD)ecx + 0x2);
			eax *= ecx;
			ecx = (DWORD)rsi;
			ecx ^= edx;
			DWORD udZero = 0.5f;
			//left, right
			eax = (DWORD)((QWORD)ecx + 0x2);
			eax *= ecx;
			DWORD lrZero = 0.5f;
			*(DWORD*)(r12) = udZero;
			*(DWORD*)(rsi) = lrZero;
		}
	}
}

typedef uint64_t(__fastcall* t_get_entity_pos)(int, int, float*, Vector3*);
Vector3 get_entities_ptr(int entityNum)
{
	auto adr = (t_get_entity_pos)(g_vars->baseModule + g_vars->goffsets.entitiespos_ptr);
	float test[32];
	Vector3 Position = Vector3(0, 0, 0);
	//spoof_call(TestEntityFunc, 0, EntityID, test, &Position);
	auto entitiesPtr = spoof_call(g_vars->goffsets.rbx_jmp, adr, (int)0, entityNum, test, &Position);
	return Position;
}

namespace g_game
{
	void main_loop(ImFont* font);
	void ui_header()
	{
		if (g_vars->msettings.b_menuEnable)
		{
			ImGuiIO& io = ImGui::GetIO();
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.65f));
			ImGui::Begin("A", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
			ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
			ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
			int dwWidth = GetSystemMetrics(SM_CXSCREEN) / 4;
			int dwHeight = GetSystemMetrics(SM_CYSCREEN) / 2;

		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
			ImGui::Begin("A", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
			ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
			ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
			int dwWidth = GetSystemMetrics(SM_CXSCREEN) / 4;
			int dwHeight = GetSystemMetrics(SM_CYSCREEN) / 2;


		}
	}

	void ui_end()
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
	}

	void init(ImFont* font)
	{
		ui_header();
		main_loop(font);
		ui_end();
	}

	void main_loop(ImFont* font)
	{
		g_vars->msettings.b_ingame = sdk::in_game();

		if (!g_vars->msettings.b_ingame)
		{
			sdk::clear_cached();
			sdk::refdef = 0;
			return;
		}

		if (g_vars->msettings.player_max == 1)
			g_vars->msettings.player_max = sdk::get_max_player_acount();

		if (sdk::refdef == 0)
			sdk::refdef = sdk::get_refdef();

		sdk::cg_client* local_client_info = sdk::get_localentity();

		if (!local_client_info) return;

		auto local_index = local_client_info->get_index();
		g_vars->gcached.local_index = local_index;

		int local_player_health = sdk::get_player_health(local_index);

		if (!local_player_health)
			return;

		//LOGS(" Local Health %d", local_player_health);

		Vector3 local_pos_info = get_entities_ptr(local_index);

		if (local_pos_info.IsZero())
			return;

		g_vars->gcached.local_team_id = local_client_info->get_team_id();

		if (g_vars->msettings.b_crosshair)
			draw::draw_crosshair();

		for (int i = 0; i < g_vars->msettings.player_max; i++)
		{
			if (g_vars->gcached.local_index == i)
				continue;

			Vector3 position = get_entities_ptr(i);

			//LOGS(" Entity Pos: %lf, %lf, %lf", position.x, position.y, position.z);

			float fdistance = local_pos_info.Distance(position) / 40;

			if (fdistance > g_vars->msettings.max_distance)
				continue;

			float show_info_offset = 0;

			sdk::cg_client* player_info = sdk::get_playerinfo(i);

			if (!player_info)
				continue;

			if (!player_info || player_info->is_valid() != 1 || i != player_info->get_index())
				continue;

			auto entityinfo_teamid = player_info->get_team_id();

			bool is_friendly = entityinfo_teamid == g_vars->gcached.local_team_id;

			if (is_friendly && !g_vars->msettings.b_friendly)
				continue;

			sdk::get_visible_base(i);

			bool is_visible = sdk::is_visible(i);

			auto player_health = sdk::get_player_health(i);

			auto is_player_alive = !player_info->is_dead() && player_health > 0;

			if (!is_player_alive && !is_visible)
				continue;

			Vector2 ScreenPos, BoxSize;
			Vector2 positionTransformed = Vector2(0, 0);

			if (draw::World2Screen(position, &ScreenPos, &BoxSize))
			{
				if (g_vars->msettings.b_names)
				{

					show_info_offset += 0;
					utils::color_var current_color;
					std::string pName = sdk::get_player_name(i);
					std::string teamIDStr(xorstr("[").crypt_get() + std::to_string(entityinfo_teamid) + xorstr("]").crypt_get() + pName);
					draw::draw_sketch_edge_text(font, teamIDStr, ImVec2(
						ScreenPos.x + (BoxSize.x / 2),
						ScreenPos.y + BoxSize.y + 5 + show_info_offset), 16.0f, g_vars->msettings.name_color.color(), true);
				}

				if (g_vars->msettings.b_distance)
				{
					utils::color_var current_color;
					show_info_offset += 15;
					std::string distance_string(xorstr("[ ").crypt_get());
					distance_string += std::to_string(fdistance);
					std::string::size_type end = distance_string.find(xorstr(".").crypt_get());
					if (end != std::string::npos && (end + 2) <= (distance_string.length() - 1))
						distance_string.erase(distance_string.begin() + end + 2, distance_string.end());
					distance_string += xorstr("m ]").crypt_get();
					draw::draw_sketch_edge_text(font, distance_string, ImVec2(
						ScreenPos.x + (BoxSize.x / 2),
						ScreenPos.y + BoxSize.y + 5 + show_info_offset), 16.0f, g_vars->msettings.dis_color.color(), true);
				}

				if (g_vars->msettings.b_line)
				{

					utils::color_var current_color;
					if (g_vars->msettings.b_visible && is_visible)
						current_color = is_friendly ? g_vars->msettings.visible_team_color : g_vars->msettings.visible_line_color;
					else
						current_color = is_friendly ? g_vars->msettings.n_visilbe_team_color : g_vars->msettings.n_visible_line_color;

					ImVec2 origin;
					origin.x = sdk::refdef->Width;
					origin.y = sdk::refdef->Height;

					draw::draw_line(ImVec2(origin.x / 2, origin.y / 2), ImVec2(ScreenPos.x + (BoxSize.x / 2), ScreenPos.y + BoxSize.y), current_color.color(), 2.f);
				}

				if (g_vars->msettings.b_box)
				{
					utils::color_var current_color;
					if (g_vars->msettings.b_visible && is_visible)
						current_color = is_friendly ? g_vars->msettings.visible_team_color : g_vars->msettings.visible_box_color;
					else
						current_color = is_friendly ? g_vars->msettings.n_visilbe_team_color : g_vars->msettings.n_visible_box_color;

					switch (g_vars->msettings.box_options)
					{
					case 0: draw::draw_box(ScreenPos.x, ScreenPos.y, BoxSize.x, BoxSize.y, current_color.color(), 2.f); break;
					case 1: draw::draw_corned_box(POINT(ScreenPos.x, ScreenPos.y), POINT(BoxSize.x, BoxSize.y), current_color.color(), 2.f); break;
					}
				}

				if (g_vars->msettings.b_skeleton)
				{
					utils::color_var current_color;
					if (g_vars->msettings.b_visible && is_visible)
						current_color = is_friendly ? g_vars->msettings.visible_team_color : g_vars->msettings.visible_bone_color;
					else
						current_color = is_friendly ? g_vars->msettings.n_visilbe_team_color : g_vars->msettings.n_visible_box_color;

					draw::draw_bones(i, g_vars->msettings.bone_size, current_color.color(), ScreenPos.x, ScreenPos.y, BoxSize.x, BoxSize.y);
				}

				if (g_vars->msettings.b_health)
					draw::draw_health(sdk::get_player_health(i),position);
			}
		}

		sdk::update_last_visible();
	}
}

dvar_s* Dvar_FindVarByName(const char* dvarName)
{
	//[48 83 EC 48 49 8B C8 E8 ?? ?? ?? ?? + 0x7] resolve call.
	return reinterpret_cast<dvar_s * (__fastcall*)(const char* dvarName)>(g_vars->baseModule + g_vars->goffsets.Dvar_FindVarByName)(dvarName);
}

uintptr_t Dvar_SetBool_Internal(dvar_s* a1, bool a2)
{
	//E8 ? ? ? ? 80 3D ? ? ? ? ? 4C 8D 35 ? ? ? ? 74 43 33 D2 F7 05 ? ? ? ? ? ? ? ? 76 2E
	return reinterpret_cast<std::ptrdiff_t(__fastcall*)(dvar_s * a1, bool a2)>(g_vars->baseModule + g_vars->goffsets.Dvar_SetBoolInternal)(a1, a2);
}

uintptr_t Dvar_SetInt_Internal(dvar_s* a1, unsigned int a2)
{
	//40 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 0F B6 41 09 48 8B D9
	return reinterpret_cast<std::ptrdiff_t(__fastcall*)(dvar_s * a1, unsigned int a2)>(g_vars->baseModule + g_vars->goffsets.Dvar_SetInt_Internal)(a1, a2);
}

uintptr_t Dvar_SetBoolByName(const char* dvarName, bool value)
{
	//"48 89 ? ? ? 57 48 81 EC ? ? ? ? 0F B6 ? 48 8B"
	int64(__fastcall * Dvar_SetBoolByName_t)(const char* dvarName, bool value); //48 89 5C 24 ? 57 48 81 EC ? ? ? ? 0F B6 DA
	return reinterpret_cast<decltype(Dvar_SetBoolByName_t)>(g_vars->baseModule + g_vars->goffsets.Dvar_SetBoolByName)(dvarName, value);
}

uintptr_t Dvar_SetFloat_Internal(dvar_s* a1, float a2)
{
	//E8 ? ? ? ? 45 0F 2E C8 RESOLVE CALL
	return reinterpret_cast<std::ptrdiff_t(__fastcall*)(dvar_s * a1, float a2)>(g_vars->baseModule + g_vars->goffsets.Dvar_SetFloat_Internal)(a1, a2);
}

uintptr_t Dvar_SetIntByName(const char* dvarname, int value)
{
	uintptr_t(__fastcall * Dvar_SetIntByName_t)(const char* dvarname, int value); //48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 8B DA 48 8B F9
	return reinterpret_cast<decltype(Dvar_SetIntByName_t)>(g_vars->baseModule + g_vars->goffsets.Dvar_SetIntByName)(dvarname, value);
}
__int64 Com_DDL_LoadAsset(__int64 file) {
	uintptr_t address = g_vars->baseModule + g_vars->goffsets.ddl_loadasset;
	return ((__int64 (*)(__int64))address)(file);
}

__int64 DDL_GetRootState(__int64 state, __int64 file) {
	uintptr_t address = g_vars->baseModule + g_vars->goffsets.ddl_getrootstate;
	return ((__int64 (*)(__int64, __int64))address)(state, file);
}

bool CL_PlayerData_GetDDLBuffer(__int64 context, int controllerindex, int stats_source, unsigned int statsgroup) {
	uintptr_t address = g_vars->baseModule + g_vars->goffsets.ddl_getdllbuffer;
	return ((bool (*)(__int64, int, int, unsigned int))address)(context, controllerindex, stats_source, statsgroup);
}

__int64 DDL_MoveToName(__int64 fstate, __int64 tstate, __int64 path) {
	uintptr_t address = g_vars->baseModule + g_vars->goffsets.ddl_movetoname;
	return ((__int64 (*)(__int64, __int64, __int64))address)(fstate, tstate, path);
}

char DDL_MoveToPath(__int64* fromState, __int64* toState, int depth, const char** path) {
	uintptr_t address = g_vars->baseModule + g_vars->goffsets.ddl_movetopath;
	return ((char (*)(__int64* fromState, __int64* toState, int depth, const char** path))address)(fromState, toState, depth, path);
}

char DDL_SetInt(__int64 fstate, __int64 context, unsigned int value) {
	uintptr_t address = g_vars->baseModule + g_vars->goffsets.ddl_setint;
	return ((char (*)(__int64, __int64, unsigned int))address)(fstate, context, value);
}

char DDL_SetString(__int64 state, __int64 ddlContext, const char* value) {
	uintptr_t address = g_vars->baseModule + g_vars->goffsets.ddl_setstring;
	return ((char (*)(__int64, __int64, const char*))address)(state, ddlContext, value);
}

bool DDL_Parse(const char* pStr, const char** navStrings2, const int navStringMax, int* navStringCount)
{
	uintptr_t address = g_vars->baseModule + g_vars->goffsets.ddl_parse;
	return ((bool (*)(const char* pStr, const char** navStrings2, const int navStringCount, int* param_4))address)(pStr, navStrings2, navStringMax, navStringCount);
}

char DDL_SetEnum(__int64 fstate, __int64 context, const char* value)
{
	uintptr_t address = g_vars->baseModule + 0x6efa6b0;
	return ((char (*)(__int64, __int64, const char*))address)(fstate, context, value);
}

void setCamo(int loadout, int weapon, int camoID)
{
	char context[255];
	char state[255];
	int string_count;
	char* str[16]{};
	const char* mode = "";
	char buffer[200];

	if (g_vars->msettings.gamemode == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	else if (g_vars->msettings.gamemode == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}
	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);
	DDL_GetRootState((__int64)state, ddl_file);
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.%i.camo"), loadout, weapon);
	DDL_Parse(buffer, (const char**)str, 32, &string_count);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
	{
		DDL_SetInt((__int64)state, (__int64)context, camoID);
	}
}

void setName(int loadout, const char name[255])
{
	char context[255];
	char state[255];
	int string_count;
	char* str[255]{};
	const char* mode = "";
	char buffer[200];

	if (g_vars->msettings.gamemode == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	else if (g_vars->msettings.gamemode == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}
	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);
	DDL_GetRootState((__int64)state, ddl_file);
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.name"), loadout);
	DDL_Parse(buffer, (const char**)str, 255, &string_count);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
	{
		DDL_SetString((__int64)state, (__int64)context, name);
	}
}


void setOperators(const char operators[255], int operatorid)
{
	char context[255];
	char state[255];
	int string_count;
	char* str[16]{};
	const char* mode = "";
	char buffer[200];

	if (g_vars->msettings.gamemode == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	else if (g_vars->msettings.gamemode == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}
	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);
	DDL_GetRootState((__int64)state, ddl_file);
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("customizationSetup.operatorCustomization.%s.skin"), operators);
	DDL_Parse(buffer, (const char**)str, 32, &string_count);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
	{
		DDL_SetInt((__int64)state, (__int64)context, operatorid);
	}
}

void setUnlock()
{
	uintptr_t num = (g_vars->baseModule + g_vars->goffsets.unlock_offsets + 0xc);
	int num2 = *reinterpret_cast<int*>(num);
	uintptr_t unlock_base = num + num2 + 4 - g_vars->baseModule;
	uintptr_t numptr = (g_vars->baseModule + unlock_base + 0x60);
	memcpy((BYTE*)numptr, (BYTE*)xorstr_("\x48\x83\xC4\x08\x48\x8B\x5C\x24\x30\x48\x8B\x74\x24\x38\x48\x83\xC4\x20\x5F\x48\xC7\xC0\x01\x00\x00\x00\xC3"), 28);
	*(uintptr_t*)(g_vars->baseModule + unlock_base + 8) = numptr;
	*(uintptr_t*)(g_vars->baseModule + unlock_base) = g_vars->baseModule + unlock_base;
}

void CL_PlayerData_SetCustomClanTag(const char* clanTag)
{
	//74 ?? 48 8d 15 ?? ?? ?? ?? 8b cf e8 ?? ?? ?? ?? 48 8b 5c 24 30
	uintptr_t address = g_vars->baseModule + g_vars->goffsets.clantag;
	((void(*)(int, const char*))address)(0, clanTag);
}
