#include "dllmain.h"
#include <sys/stat.h>

#define StartThread(mainThread, dllhandle) I_beginthreadex(0, 0, (_beginthreadex_proc_type)mainThread, dllhandle, 0, 0);

void Log_(const char* fmt, ...) {
	char		text[4096];
	va_list		ap;
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	std::ofstream logfile(xorstr_("C:\\aio\\debug\\aio_debuglog.logs"), std::ios::app);
	if (logfile.is_open() && text)	logfile << text << std::endl;
	logfile.close();
}

bool IsPathExist(const std::string& s)
{
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}


__declspec(dllexport)HRESULT present_hk(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!pSwapChain)
		return ori_present(pSwapChain, SyncInterval, Flags);
	if (d3d12::pCommandQueue == nullptr)
	{
		ori_present(pSwapChain, SyncInterval, Flags);
	}

	DXGI_SWAP_CHAIN_DESC sdesc;
	pSwapChain->GetDesc(&sdesc);
	if (sdesc.OutputWindow == GetForegroundWindow())
	{
		ImFont* main_font = imgui::start(
			reinterpret_cast<IDXGISwapChain3*>(pSwapChain),
			reinterpret_cast<ID3D12CommandQueue*>((d3d12::pCommandQueue)), nullptr, 16.0f);

		imgui::imgui_frame_header();
		
		if (GetAsyncKeyState(VK_HOME) & 1)
			g_vars->msettings.b_menuEnable = !g_vars->msettings.b_menuEnable;


		if (g_vars->msettings.b_menuEnable)
		{
			ImGui::GetIO().MouseDrawCursor;
			menu->Menu();
		}

		if (g_vars->msettings.b_textinputnInfo)
		{
			ImGui::GetIO().MouseDrawCursor;
			menu->Informatio();
		}

		imgui::imgui_no_border(g_game::init, main_font);

		imgui::imgui_frame_end();
	}
	return ori_present(pSwapChain, SyncInterval, Flags);
}

int GetLogonStatus(int status) {
	return reinterpret_cast<int(*)(int)>(g_vars->baseModule + g_vars->goffsets.logonstatus)(status);
}

void Initialize()
{
	g_vars = new global_vars();
	//E8 ? ? ? ? 83 F8 02 0F 84 ? ? ? ? 48 89
	g_vars->baseModule = (QWORD)(iat(GetModuleHandleA).get()("ModernWarfare.exe"));

	g_vars->procId = utility::GetProcId(L"ModernWarfare.exe");
	g_vars->hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, g_vars->procId);

	g_vars->goffsets.logonstatus = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x3000000, 0x1F00000, "\xE8\x00\x00\x00\x00\x83\xF8\x02\x0F\x84\x00\x00\x00\x00\x48\x89", "x????xxxxx????xx", 1, 5, 0);

	while (GetLogonStatus(0) != 2)
	{
		std::this_thread::sleep_for(
			std::chrono::milliseconds(5));
	}
	g_vars->hWind = process::get_process_window();
}

DWORD WINAPI Threading(HMODULE hmodule)
{
	Initialize();

	if (g_vars->msettings.b_debugEnable)
	{
		if (!IsPathExist(xorstr_("C:\\aio\\debug")))
		{
			CreateDirectoryA(xorstr_("C:\\aio\\debug"), NULL);
		}
	}

	g_vars->goffsets.jmp_rbx = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x00900000, 0x1F0000, xorstr_("\xFF\x23\x2C\x4D\xB3\xB7\x04"), xorstr_("xxxxxxx")) - g_vars->baseModule;
	g_vars->goffsets.rbx_jmp = (void*)(g_vars->baseModule + g_vars->goffsets.jmp_rbx);
	if (g_vars->msettings.b_debugEnable)
		LOGS_ADDR(g_vars->goffsets.jmp_rbx)

	if (g_vars->procId)
	{
		g_vars->goffsets.gamemode = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x03000000, 0xF00000, xorstr_("\x44\x8b\x00\x00\x00\x00\x00\xc6\x44\x24\x00\x00\xc6\x44\x24\x00\x00"), xorstr_("xx?????xxx??xxx???"), 3, 7, 0);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.gamemode)

			g_vars->goffsets.camera_ptr = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x02000000, 0x1F00000, xorstr_("\x48\x69\xC0\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x48\x03\x05\x00\x00\x00\x00"), xorstr_("xxx????x????xxx????"), 3, 7, 12);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.camera_ptr)

			g_vars->goffsets.refdef_ptr = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x03000000, 0x1F00000, xorstr_("\xF3\x0F\x11\x0F\x0F\xC6\xC1\x55\x0F\xC6\xC9\xAA\xF3\x0F\x11\x4F\x00\xF3\x0F\x11\x47\x00\xE8\x00\x00\x00\x00"), xorstr_("xxxxxxxxxxxxxxxx?xxxx?x????"), 3, 7, 27);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.refdef_ptr)

			g_vars->goffsets.entitiespos_ptr = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x04000000, 0x1F00000, xorstr_("\x45\x85\x00\x79\x00\x4d\x8d\x00\x0c\x4d\x8b\x00"), xorstr_("xx?x?xx?xxx?"), 1, 5, 17);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.entitiespos_ptr)

			g_vars->goffsets.distribute = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x05000000, 0x1FFFFFF, xorstr_("\x4c\x8B\x05\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x41\x0F\xB7\x80\x00\x00\x00\x00"), xorstr_("xxx????x????xxxx????"), 3, 7, 0);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.distribute)

			g_vars->goffsets.visible = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x06000000, 0x1FFFFFF, xorstr_("\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x87\x00\x00\x00\x00\xF3\x0F\x11\x87\x00\x00\x00\x00"), xorstr_("xxx????xxx????xxxx????"), 3, 7, 0);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.visible)

			g_vars->goffsets.local_index_offset = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x1000000, 0x1F00000, xorstr_("\x8B\xCB\xE8\x00\x00\x00\x00\x48\x69\xCF\x00\x00\x00\x00\x85\xC0"), xorstr_("xxx????xxx????xx"), 3, 0, -0x18, false);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.local_index_offset)

			g_vars->goffsets.c_death1 = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x2000000, 0x1FFFFFF, xorstr_("\xC7\x83\x00\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x44\x0F\x00\x00\x48\x8B\x00\x48\x8B\x00"), xorstr_("xx????????x????xx??xx?xx?"), 2, 0, -0xA, false);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.c_death1);

		g_vars->goffsets.c_death2 = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x2000000, 0x1FFFFFF, xorstr_("\xC7\x83\x00\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x44\x0F\x00\x00\x48\x8B\x00\x48\x8B\x00"), xorstr_("xx????????x????xx??xx?xx?"), 2, 0, 0, false);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.c_death2);

		g_vars->goffsets.c_size = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x5000000, 0x1FFFFFF, xorstr_("\x83\xFA\x01\x7D\x15\x48\x63\xC2\x48\x69\xD0\x00\x00\x00\x00\x48\x8D\x81\x00\x00\x00\x00\x48\x03\xC2\xC3"), xorstr_("xxxxxxxxxxx????xxx????xxxx"), 3, 0, 8, false);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.c_size);

		g_vars->goffsets.c_position = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x6000000, 0x1FFFFFF, xorstr_("\x4C\x89\x00\x00\x00\x00\x00\x4C\x8B\x00\x00\x00\x44\x89\x00\x00\x00"), xorstr_("xx?????xx???xx???"), 3, 0, 0, false);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.c_position);

		g_vars->goffsets.c_stance = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x1000000, 0x1FFFFFF, xorstr_("\x0F\x29\x74\x24\x00\x0F\x29\x7C\x24\x00\x8B\x70\x04\xB8"), xorstr_("xxxx?xxxx?xxxx"), 2, 0, 0x1B, false);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.c_stance);

		g_vars->goffsets.c_valid = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1FFFFFF, xorstr_("\x83\xb9\x00\x00\x00\x00\x00\x0f\x84\x00\x00\x00\x00\x8b\x83\x00"), xorstr_("xx?????xx????xx?"), 2, 0, 0, false);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.c_valid);

		g_vars->goffsets.c_teamid = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1FFFFFF, xorstr_("\x8b\x83\x00\x00\x00\x00\x85\x00\x74\x00\x3b\x81\x00\x00\x00\x00\x0f\x84\x00\x00\x00\x00"), xorstr_("xx????x?x?xx????xx????"), 2, 0, 0, false);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.c_teamid);

		g_vars->goffsets.c_entity_index = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1FFFFFF, xorstr_("\x8b\x83\x00\x00\x00\x00\x39\x81\x00\x00\x00\x00\x0f\x84\x00\x00\x00\x00"), xorstr_("xx????xx????xx????"), 2, 0, 0, false);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.c_entity_index);

		//Name
		g_vars->goffsets.name_array = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1FFFFFF, xorstr_("\x48\x8d\x00\x00\x00\x00\x00\x8b\xd3\x48\x8b\x0c\x00\x48\x8b\x01"), xorstr_("xx?????xxxxx?xxx"), 3, 7, 0);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.name_array);

			g_vars->goffsets.unlock_offsets = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x500000, 0x1F0000, xorstr_("\x33\xFF\x48\x8D\x15\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x8D\x0D"), xorstr_("xxxxx????xxx????xxx")) - g_vars->baseModule;
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.unlock_offsets);

		g_vars->goffsets.clantag = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1F00000, xorstr_("\x74\x00\x48\x8d\x15\x00\x00\x00\x00\x8b\xcf\xe8\x00\x00\x00\x00\x48\x8b\x5c\x24\x30"), xorstr_("x?xxx????xxx????xxxxx"), 1, 5, 11);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.clantag);

		g_vars->goffsets.ddl_loadasset = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x3000000, 0x1F00000, xorstr_("\xe8\x00\x00\x00\x00\x48\x8b\x00\x4c\x8d\x4c\x24\x00\x33\xc0\x48\x8d\x0d\x00\x00\x00\x00"), xorstr_("x????xx?xxxx?xxxxx????"), 1, 5, 0);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.ddl_loadasset);

		g_vars->goffsets.norecoil = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x05000000, 0xFFFFFFF, xorstr_("\x0f\x2e\x80\x50\x01\x00\x00\x0f\x85\x00\x00\x00\x00\x4d\x8d\x00\x00\x00\x00\x00"), xorstr_("xxxxxxxxx????xx?????"), 3, 0, 13, false);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.norecoil)

		g_vars->goffsets.ddl_getrootstate = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x2000000, 0x1F00000, xorstr_("\xe8\x00\x00\x00\x00\x8b\x0d\x00\x00\x00\x00\x0f\x10\x00"), xorstr_("x????xx????xx?"), 1, 5, 0);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.ddl_getrootstate);

		g_vars->goffsets.ddl_getdllbuffer = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1F00000, xorstr_("\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x48\x8B\xE9\x49\x63\xF8\x41\x8B\xC9\x48\x63\xF2\x41\x8B\xD9\xE8\x00\x00\x00\x00"), xorstr_("xxxx?xxxx?xxxx?xxxxxxxxxxxxxxxxxxxxx????")) - g_vars->baseModule;
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.ddl_getdllbuffer);

		g_vars->goffsets.ddl_movetoname = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x84\xC0\x74\x22\x48\x8D\x54\x24\x40"), xorstr_("x????xxxxxxxxx"), 1, 5, 0);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.ddl_movetoname);

		g_vars->goffsets.ddl_movetopath = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x6500000, 0xF00000, "\x48\x89\x74\x24\x00\x48\x89\x7C\x24\x00\x41\x56\x48\x83\xEC\x20\x4D\x8B\xF1\x48\x8B\xFA\x48\x85\xC9", "xxxx?xxxx?xxxxxxxxxxxxxxx") - g_vars->baseModule;
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.ddl_movetopath);

		g_vars->goffsets.ddl_setint = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1F00000, xorstr_("\x44\x8B\xC0\x48\x8D\x55\xB7\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00"), xorstr_("xxxxxxxxxxx?x????"), 1, 5, 12);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.ddl_setint);

		g_vars->goffsets.ddl_setstring = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x3000000, 0x1F00000, xorstr_("\x4c\x8b\x00\x48\x8b\x00\x48\x8b\x00\xe8\x00\x00\x00\x00\x84\x00\x75\x1b"), xorstr_("xx?xx?xx?x????x?xx"), 1, 5, 9);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.ddl_setstring);

		g_vars->goffsets.ddl_parse = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x2000000, 0x1F00000, "\x40\x55\x56\x41\x54\x41\x56\x41\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x44\x24\x00\x45\x33\xF6\x4D\x8B\xF9\x45\x89\x31", "xxxxxxxxxxxx????xxx????xxxxxxx?xxxxxxxxx") - g_vars->baseModule;
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.ddl_parse);

		g_vars->goffsets.Dvar_FindVarByName = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x2000000, 0x1F00000, xorstr_("\x48\x83\xEC\x48\x49\x8B\xC8\xE8\x00\x00\x00\x00"), xorstr_("xxxxxxxx????"), 1, 5, 7);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.Dvar_FindVarByName);


		g_vars->goffsets.Dvar_SetBoolInternal = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x2000000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x80\x3D\x00\x00\x00\x00\x00\x4C\x8D\x35\x00\x00\x00\x00\x74\x43\x33\xD2\xF7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x76\x2E"), xorstr_("x????xx?????xxx????xxxxxx????????xx"), 1, 5, 0);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.Dvar_SetBoolInternal);


		g_vars->goffsets.Dvar_SetInt_Internal = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x3000000, 0x1F00000, xorstr_("\x40\x53\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x84\x24\x00\x00\x00\x00\x0F\xB6\x41\x09\x48\x8B\xD9"), xorstr_("xxxxx????xxx????xxxxxxx????xxxxxxx")) - g_vars->baseModule;
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.Dvar_SetInt_Internal);


		g_vars->goffsets.Dvar_SetBoolByName = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x3000000, 0x1F00000, xorstr_("\x48\x89\x5C\x24\x00\x57\x48\x81\xEC\x00\x00\x00\x00\x0F\xB6\xDA"), xorstr_("xxxx?xxxx????xxx")) - g_vars->baseModule;
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.Dvar_SetBoolByName);

		g_vars->goffsets.Dvar_SetFloat_Internal = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x5000000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x45\x0F\x2E\xC8"), xorstr_("x????xxxx"), 1, 5, 0);
		if (g_vars->msettings.b_debugEnable)
			LOGS_ADDR(g_vars->goffsets.Dvar_SetFloat_Internal);

		if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success)
		{
			kiero::bind(54, (void**)&oExecuteCommandListsD3D12, imgui::hookExecuteCommandListsD3D12);
			kiero::bind(140, (void**)&ori_present, present_hk);

		}
	}

	return 0;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		StartThread(Threading, module);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
	return TRUE;
}