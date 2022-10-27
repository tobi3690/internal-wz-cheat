#include "menu.h"

ImFont* MainCaps;
ImFont* Main;
ImFont* FMenu;
std::string rebrand = "";// brand name
static char operator_skin[128] = "";
static bool befortext = false;
static bool aftertext = false;
static bool usetextcolor = false;
static const char* color_items[] = { "RED","GREEN", "YELLOW", "BLUE", "CYAN", "PINK", "WHITE", "DEFAULT MAP COLOR", "GREY OR DEFAULT MAP COLOR","BLACK", "YALE BLUE", "LIGHT YELLOW","ORANGE" };
static const char* color_current_item = "Select Color";

static const char* before_items[] = { "A BUTTON XBOX", "X BUTTON PS", "B BUTTON XBOX", "O BUTTON PS", "X BUTTON XBOX", "SQUARE BUTTON PS", "Y BUTTON XBOX", "TRIANGLE BUTTON", "PS", "LB", "RB", "LT", "RT", "LS", "RS", "Dpad UP", "Dpad LEFT", "Dpad RIGHT", "Dpad DOWN", "Start", "Select", "Mouse Wheel", "Mouse 4", "Mouse 3", "Mouse Wheel UP", "Mouse Wheel Down", "Mouse", "Audio", "Ticket", "Warning Red", "Headshot", "Headshot Sign", "Unlock", "Spinny Boi", "Grenade", "Left Up", "Right Up", "Left Stick", "Right Stick", "Left Stick", "Right Stick", "Mantle", "Dpad", "Pros", "Cons", "Warning", "Double Arrow", "Lock", "COD Points", "Up Arrow", "Down Arrow", "Left Arrow", "Right Arrow", "LMB", "RMB", "Shotgun", "Scroll Wheel", "Mouse + ", "Hitmarker", "Key", "Party" };
static const char* before_current_item = "Select Before Symbols";

static const char* after_items[] = { "A BUTTON XBOX", "X BUTTON PS", "B BUTTON XBOX", "O BUTTON PS", "X BUTTON XBOX", "SQUARE BUTTON PS", "Y BUTTON XBOX", "TRIANGLE BUTTON", "PS", "LB", "RB", "LT", "RT", "LS", "RS", "Dpad UP", "Dpad LEFT", "Dpad RIGHT", "Dpad DOWN", "Start", "Select", "Mouse Wheel", "Mouse 4", "Mouse 3", "Mouse Wheel UP", "Mouse Wheel Down", "Mouse", "Audio", "Ticket", "Warning Red", "Headshot", "Headshot Sign", "Unlock", "Spinny Boi", "Grenade", "Left Up", "Right Up", "Left Stick", "Right Stick", "Left Stick", "Right Stick", "Mantle", "Dpad", "Pros", "Cons", "Warning", "Double Arrow", "Lock", "COD Points", "Up Arrow", "Down Arrow", "Left Arrow", "Right Arrow", "LMB", "RMB", "Shotgun", "Scroll Wheel", "Mouse + ", "Hitmarker", "Key", "Party" };
static const char* after_current_item = "Select After Symbols";

void visual()
{
	ImGui::BeginGroupBox(xorstr_("##VISUAL"), ImVec2(0, 240));
	{
		ImGui::Dummy(ImVec2(0.0f, 3.0f));
		const char* box_opt[] = { "Complete", "Corners" };
		ImGui::Checkbox(xorstr_("Show Boxes"), &g_vars->msettings.b_box);
		ImGui::SameLine();
		ImGui::Combo(xorstr_("##BOXOPTION"), &g_vars->msettings.box_options, box_opt, 2);
		ImGui::Dummy(ImVec2(0.0f, 3.0f));

		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		ImGui::Checkbox(xorstr_("Show Bones"), &g_vars->msettings.b_skeleton);
		ImGui::SameLine();
		ImGui::SliderFloat(xorstr_("##BONESIZE"), &g_vars->msettings.bone_size, 1.f, 5.f, xorstr_("Bone Size: %.0f"));
		ImGui::Dummy(ImVec2(0.0f, 1.0f));

		ImGui::Checkbox(xorstr_("Check Visible"), &g_vars->msettings.b_visible);
		ImGui::SameLine();

		ImGui::Checkbox(xorstr_("Show Only Visible"), &g_vars->msettings.b_visible_only);
		ImGui::Dummy(ImVec2(0.0f, 1.0f));

		ImGui::Checkbox(xorstr_("Show Lines"), &g_vars->msettings.b_line);
		ImGui::Dummy(ImVec2(0.0f, 1.0f));

		ImGui::Checkbox(xorstr_("Show Names"), &g_vars->msettings.b_names);
		ImGui::Dummy(ImVec2(0.0f, 1.0f));

		ImGui::Checkbox(xorstr_("Show Friendlies"), &g_vars->msettings.b_friendly);
		ImGui::Dummy(ImVec2(0.0f, 1.0f));

		ImGui::Checkbox(xorstr_("Show Distance"), &g_vars->msettings.b_distance);
		ImGui::SameLine();
		ImGui::SliderInt(xorstr_("##MAXDISTANCE"), &g_vars->msettings.max_distance, 100, 1000, xorstr_("Distance: %d"));
		ImGui::Dummy(ImVec2(0.0f, 1.0f));

		ImGui::SliderFloat(xorstr_("##FontSize"), &g_vars->msettings.font_size, 12.f, 32.f, xorstr_("Font Size: %.0f"));
		ImGui::Dummy(ImVec2(0.0f, 1.0f));

		ImGui::Checkbox(xorstr_("Show health"), &g_vars->msettings.b_health);
		ImGui::Dummy(ImVec2(0.0f, 1.0f));

		ImGui::Checkbox(xorstr_("Show Crosshair"), &g_vars->msettings.b_crosshair);
		ImGui::Dummy(ImVec2(0.0f, 1.0f));


	}
	ImGui::EndGroupBox();
}

void op()
{

	ImGui::BeginGroupBox(xorstr_("##OP"), ImVec2(0, 105));
	{
		static const char* gametype[] = { "Multiplayer", "Warzone" };
		static const char* current_type = "Warzone";
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		for (int i = 0; i < 8; i++)
		{
			ImGui::Spacing();
			ImGui::SameLine();
		}
		if (ImGui::BeginCombo("##GAMETYPE", current_type)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(gametype); n++)
			{
				bool is_selected = (current_type == gametype[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(gametype[n], is_selected))
					current_type = gametype[n];
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
			}
			ImGui::EndCombo();
		}
		ImGui::Dummy(ImVec2(0.0f, 1.0f));

		for (int i = 0; i < 8; i++)
		{
			ImGui::Spacing();
			ImGui::SameLine();
		}
		ImGui::InputTextWithHint(xorstr_("##TestWeapon"), xorstr_("Operator skin Id (1-2925)"), operator_skin, ARRAYSIZE(operator_skin));
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		if (ImGui::Button(xorstr_("Set Operator"), ImVec2(-5, 32)))
		{
			if (current_type == "Multiplayer")
			{
				g_vars->msettings.gamemode = 0;
				setOperators("default_western", atoi(operator_skin));
			}
			if (current_type == "Warzone")
			{
				g_vars->msettings.gamemode = 1;
				setOperators("default_western", atoi(operator_skin));
			}
		}


	}
	ImGui::EndGroupBox();
}

void ShowToastNotificationAfterUserLeftParty(const char* Username) {
	// Function Pattern: 48 89 6c 24 ? 4c 89 44 24 ? 56 57 41 56
	// Function Offset: 0x2Af4C80
	void(__fastcall * ShowToastNotificationAfterUserLeftParty_t)(int, int, int, const char* text, int);
	return reinterpret_cast<decltype(ShowToastNotificationAfterUserLeftParty_t)>(g_vars->baseModule + 0x2AF4C80)(0, 0, 0, Username, 0);
}
void OnReceiveIncomingPartyMember(const char* Username)
{
	// Pattern: CC 48 89 74 24 ? 57 48 83 EC 20 4C 8B 05 ? ? ? ? 33 + 1 
	// Current Offset: 0x2AF7190
	void(__fastcall * OnReceiveIncomingPartyMember_t)(int, int, int, const char* text, int, bool, bool);
	return reinterpret_cast<decltype(OnReceiveIncomingPartyMember_t)>(g_vars->baseModule + 0x2AF7190)(0, 0, 0, Username, 0, true, true);
}

void loadout()
{
	static const char* wz_items[] = { "(MW) Gold", "(MW) Platinum", "(MW) Damascus", "(MW) Obsidian" , "(MW) Acticamo", "(MW) Banded", "(CW) Gold", "(CW) Diamond", "(CW) DMU", "(CW) Golden Viper", "(CW) Plague Diamond", "(CW) Dark Aether", "(CW) Cherry Blossom", "(VG) Gold", "(VG) Diamond", "(VG) Atomic", "(VG) Fake Diamond", "(VG) Golden Viper", "(VG) Plague Diamond", "(VG) Dark Aether", "(VG) False Orospector", "(VG) Death Prospector" , "(VG) Titanium Chrome", "(VG) Liquid Metal", "(VG) Skynet" };
	static const char* wz_current_itme = "Select Camo";

	static const char* mp_items[] = { "(MW) Gold", "(MW) Platinum", "(MW) Damascus", "(MW) Obsidian" , "(MW) Acticamo", "(MW) Banded", "(CW) Gold", "(CW) Diamond", "(CW) DMU", "(CW) Golden Viper", "(CW) Plague Diamond", "(CW) Dark Aether", "(CW) Cherry Blossom", "(VG) Gold", "(VG) Diamond", "(VG) Atomic", "(VG) Fake Diamond", "(VG) Golden Viper", "(VG) Plague Diamond", "(VG) Dark Aether" };
	static const char* mp_current_itme = "Select Camo";

	static int mp_classes = 0;
	static int wz_classes = 0;
	static int mp_weaponstype = 0;
	static int wz_weaponstype = 0;
	static char mpclass_name[255] = "";
	static char wzclass_name[255] = "";
	ImGui::BeginGroupBox(xorstr_("##UNLOCK"), ImVec2(0, 65));
	{
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		ImGui::BeginChild("##UNLOCK", ImVec2(0, 0));
		{

			if (ImGui::Button(xorstr_("Unlock All"), ImVec2(150, 30)))
			{
				setUnlock();
				ShowToastNotificationAfterUserLeftParty("^6ALIVE ON TOP");
			}
			ImGui::SameLine();
			ImGui::Checkbox(xorstr_("No Owner Check"), &g_vars->msettings.b_owner);
			if (g_vars->msettings.b_owner)
			{
				dvar_set2(xorstr_("NRQQOMLOQL"), 0);
				dvar_set2(xorstr_("RRTLRKKTT"), 0);
				dvar_set2(xorstr_("MKQPRPLQKL"), 0);
			}
			else
			{
				dvar_set2(xorstr_("NRQQOMLOQL"), 1);
				dvar_set2(xorstr_("RRTLRKKTT"), 1);
				dvar_set2(xorstr_("MKQPRPLQKL"), 1);
			}

		}
		ImGui::EndChild();
	}
	ImGui::EndGroupBox();
	ImGui::BeginGroupBox(xorstr_("##CAMOLOADOUT"), ImVec2(0, 180));
	{
		static const char* gametype[] = { "Multiplayer", "Warzone" };
		static const char* current_type = "Warzone";
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		ImGui::BeginChild("##CAMOLOADOUT", ImVec2(-1, -1));
		{
			for (int i = 0; i < 8; i++)
			{
				ImGui::Spacing();
				ImGui::SameLine();
			}
			if (ImGui::BeginCombo("##COMBOGAMETYPE", current_type)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < IM_ARRAYSIZE(gametype); n++)
				{
					bool is_selected = (current_type == gametype[n]); // You can store your selection however you want, outside or inside your objects
					if (ImGui::Selectable(gametype[n], is_selected))
						current_type = gametype[n];
					if (is_selected)
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
				}
				ImGui::EndCombo();
			}
			for (int i = 0; i < 8; i++)
			{
				ImGui::Spacing();
				ImGui::SameLine();
			}

			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			if (current_type == "Multiplayer")
			{
				for (int i = 0; i < 8; i++)
				{
					ImGui::Spacing();
					ImGui::SameLine();
				}
				ImGui::Combo("##mpnamess", &mp_classes, xorstr_("Loadout 1\0Loadout 2\0Loadout 3\0Loadout 4\0Loadout 5\0Loadout 6\0Loadout 7\0Loadout 8\0Loadout 9\0Loadout 10\0\0"));
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				for (int i = 0; i < 8; i++)
				{
					ImGui::Spacing();
					ImGui::SameLine();
				}

				ImGui::InputTextWithHint(xorstr_("##CLASSNAME"), xorstr_("Loadout Name"), mpclass_name, sizeof(mpclass_name));
				ImGui::SameLine();
				if (ImGui::Button(xorstr_("?"), ImVec2(15, 20)))
				{

				}
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				if (ImGui::Button(xorstr_("Rename Class Name"), ImVec2(-5, 25)))
				{
					setName(mp_classes, mpclass_name);
				}
				for (int i = 0; i < 8; i++)
				{
					ImGui::Spacing();
					ImGui::SameLine();
				}
				ImGui::Combo("##MPGuns", &mp_weaponstype, xorstr_("Primary\0Secondary\0\0"));
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				for (int i = 0; i < 8; i++)
				{
					ImGui::Spacing();
					ImGui::SameLine();
				}
				if (ImGui::BeginCombo(xorstr_("##mpcombo"), mp_current_itme)) // The second parameter is the label previewed before opening the combo.
				{
					for (int n = 0; n < IM_ARRAYSIZE(mp_items); n++)
					{
						bool is_selected = (mp_current_itme == mp_items[n]); // You can store your selection however you want, outside or inside your objects
						if (ImGui::Selectable(mp_items[n], is_selected))
							mp_current_itme = mp_items[n];
						if (is_selected)
							ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
					}
					ImGui::EndCombo();
				}
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				if (ImGui::Button(xorstr_("Set Multiplayer Camo"), ImVec2(-5, 20)))
				{
					if (mp_current_itme == "(MW) Gold")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 111);
					}

					if (mp_current_itme == "(MW) Platinum")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 112);
					}

					if (mp_current_itme == "(MW) Damascus")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 113);
					}

					if (mp_current_itme == "(MW) Obsidian")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 114);
					}

					if (mp_current_itme == "(MW) Acticamo")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 2);
					}

					if (mp_current_itme == "(MW) Banded")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 3);
					}

					if (mp_current_itme == "(CW) Gold")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 133);
					}

					if (mp_current_itme == "(CW) Diamond")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 134);
					}

					if (mp_current_itme == "(CW) DMU")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 135);
					}

					if (mp_current_itme == "(CW)Golden Viper")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 242);
					}

					if (mp_current_itme == "(CW) Plague Diamond")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 243);
					}

					if (mp_current_itme == "(CW) Plague Diamond")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 244);
					}

					if (mp_current_itme == "(CW) Cherry Blossom")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 160);
					}

					if (mp_current_itme == "(VG) Gold")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 345);
					}

					if (mp_current_itme == "(VG) Diamond")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 346);
					}

					if (mp_current_itme == "(VG) Atomic")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 350);
					}

					if (mp_current_itme == "(VG) Fake Diamond")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 349);
					}

					if (mp_current_itme == "(VG) Golden Viper")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 402);
					}

					if (mp_current_itme == "(VG) Plague Diamond")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 403);
					}

					if (mp_current_itme == "(VG) Dark Aether")
					{
						g_vars->msettings.gamemode = 0;
						setCamo(mp_classes, mp_weaponstype, 404);
					}
				}
			}

			if (current_type == "Warzone")
			{

				for (int i = 0; i < 8; i++)
				{
					ImGui::Spacing();
					ImGui::SameLine();
				}

				ImGui::Combo("##wznamess", &wz_classes, xorstr_("Loadout 1\0Loadout 2\0Loadout 3\0Loadout 4\0Loadout 5\0Loadout 6\0Loadout 7\0Loadout 8\0Loadout 9\0Loadout 10\0\0"));
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				for (int i = 0; i < 8; i++)
				{
					ImGui::Spacing();
					ImGui::SameLine();
				}

				ImGui::InputTextWithHint(xorstr_("##CLASSNAME"), xorstr_("Loadout Name"), wzclass_name, sizeof(wzclass_name));
				ImGui::SameLine();
				if (ImGui::Button(xorstr_("? "), ImVec2(15, 20)))
				{
					//g_vars->msettings.b_textinputnInfo = !g_vars->msettings.b_textinputnInfo;
				}
				ImGui::Dummy(ImVec2(0.0f, 1.0f));

				if (ImGui::Button(xorstr_("Rename Class Name"), ImVec2(-5, 20)))
				{
					g_vars->msettings.gamemode = 1;
					setName(wz_classes, wzclass_name);
				}
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				for (int i = 0; i < 8; i++)
				{
					ImGui::Spacing();
					ImGui::SameLine();
				}
				ImGui::Combo("##WZGuns", &wz_weaponstype, xorstr_("Primary\0Secondary\0\0"));
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				for (int i = 0; i < 8; i++)
				{
					ImGui::Spacing();
					ImGui::SameLine();
				}
				if (ImGui::BeginCombo(xorstr_("##combo"), wz_current_itme)) // The second parameter is the label previewed before opening the combo.
				{
					for (int n = 0; n < IM_ARRAYSIZE(wz_items); n++)
					{
						bool is_selected1 = (wz_current_itme == wz_items[n]); // You can store your selection however you want, outside or inside your objects
						if (ImGui::Selectable(wz_items[n], is_selected1))
							wz_current_itme = wz_items[n];
						if (is_selected1)
							ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
					}
					ImGui::EndCombo();
				}
				ImGui::Dummy(ImVec2(0.0f, 1.0f));
				if (ImGui::Button(xorstr_("Set Warzone Camo"), ImVec2(-5, 20)))
				{
					if (wz_current_itme == "(MW) Gold")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 111);
					}

					if (wz_current_itme == "(MW) Platinum")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 112);
					}

					if (wz_current_itme == "(MW) Damascus")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 113);
					}

					if (wz_current_itme == "(MW) Obsidian")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 114);
					}

					if (wz_current_itme == "(MW) Acticamo")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 2);
					}

					if (wz_current_itme == "(MW) Banded")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 3);
					}

					if (wz_current_itme == "(CW) Gold")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 133);
					}

					if (wz_current_itme == "(CW) Diamond")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 134);
					}

					if (wz_current_itme == "(CW) DMU")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 135);
					}

					if (wz_current_itme == "(CW)Golden Viper")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 242);
					}

					if (wz_current_itme == "(CW) Plague Diamond")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 243);
					}

					if (wz_current_itme == "(CW) Dark Aether")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 244);
					}

					if (wz_current_itme == "(CW) Cherry Blossom")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 160);
					}

					if (wz_current_itme == "(VG) Gold")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 345);
					}

					if (wz_current_itme == "(VG) Diamond")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 346);
					}

					if (wz_current_itme == "(VG) Atomic")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 350);
					}

					if (wz_current_itme == "(VG) Fake Diamond")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 349);
					}

					if (wz_current_itme == "(VG) Golden Viper")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 402);
					}

					if (wz_current_itme == "(VG) Plague Diamond")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 403);
					}

					if (wz_current_itme == "(VG) Dark Aether")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 404);
					}

					if (wz_current_itme == "(VG) False Orospector")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 509);
					}

					if (wz_current_itme == "(VG) Death Prospector")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 510);
					}

					if (wz_current_itme == "(VG) Titanium Chrome")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 511);
					}

					if (wz_current_itme == "(VG) Liquid Metal")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 512);
					}

					if (wz_current_itme == "(VG) Skynet")
					{
						g_vars->msettings.gamemode = 1;
						setCamo(wz_classes, wz_weaponstype, 513);
					}
				}
			}

		}
		ImGui::EndChild();
	}

	ImGui::EndGroupBox();

}

void dvars()
{
	ImGui::BeginGroupBox(xorstr_("##DVAR"), ImVec2(0, 260));
	{
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		ImGui::BeginChild("##DVAR", ImVec2(0, 0));
		{
			ImGui::Checkbox(xorstr_("FOV "), &g_vars->msettings.b_fov);
			if (g_vars->msettings.b_fov) {
				dvar_set2("NSSLSNKPN", g_vars->msettings.f_fov);
			}
			ImGui::SameLine();
			ImGui::SliderFloat(xorstr_("##FOVSLIDER"), &g_vars->msettings.f_fov, 1.0f, 2.0f, "%.1f");
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			ImGui::Checkbox(xorstr_("Mini Map "), &g_vars->msettings.b_map);
			if (g_vars->msettings.b_map) {
				dvar_set2("MKMRRLNRTM", g_vars->msettings.f_map);
			}
			ImGui::SameLine();
			ImGui::SliderFloat(xorstr_("##MAPSLIDER"), &g_vars->msettings.f_map, 1.0f, 2.0f, "%.1f");
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			ImGui::Checkbox(xorstr_("Max Bright "), &g_vars->msettings.b_brightmax);
			if (g_vars->msettings.b_brightmax) {
				dvar_set2("NQKKOONQPR", 0);
				dvar_set2("MTLMSQMNTR", 0);
				dvar_set2("RNPPKQOTN", 0);
				dvar_set2("LKOLRONRNQ", 0);
				dvar_set2("LTOKRMRTMM", 0);
			}
			else
			{
				dvar_set2("NQKKOONQPR", 1);
				dvar_set2("MTLMSQMNTR", 1);
				dvar_set2("RNPPKQOTN", 1);
				dvar_set2("LKOLRONRNQ", 1);
				dvar_set2("LTOKRMRTMM", 1);
			}
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			ImGui::Checkbox(xorstr_("Heartbeat Cheat "), &g_vars->msettings.b_hearbeat);
			if (g_vars->msettings.b_hearbeat)
			{
				dvar_set2("NLLRSSOQMQ", 10000);
				dvar_set2("NSKNMSMOLP", 1);
			}
			else
			{
				dvar_set2("cg_drawShellshock", 1);
			}
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			ImGui::Checkbox(xorstr_("No Flash Bangs "), &g_vars->msettings.b_no_flashbang);
			if (g_vars->msettings.b_no_flashbang)
			{
				dvar_set2("cg_drawShellshock", 0);
			}
			else
			{
				dvar_set2("cg_drawShellshock", 1);
			}
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			ImGui::Checkbox(xorstr_("Third Person"), &g_vars->msettings.b_thridperson);
			if (g_vars->msettings.b_thridperson)
			{
				dvar_set2("NOSLRNTRKL", 1);
			}
			else {
				dvar_set2("NOSLRNTRKL", 0);
			}
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			ImGui::Checkbox(xorstr_("Unlimited Sprint"), &g_vars->msettings.b_sprint);
			if (g_vars->msettings.b_sprint)
			{
				dvar_set2("MQPTMLNLPN", 1);
				dvar_set2("NLQONKPTLT", 1000);
				dvar_set2("TOSNKQPRS", 1000);
				dvar_set2("NSTMLPOMSQ", 20);
			}
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			ImGui::Checkbox(xorstr_("No Stun"), &g_vars->msettings.b_no_stun);
			if (g_vars->msettings.b_no_stun)
			{
				dvar_set2("MMQKQOSTNS", 1);
			}
			else
			{
				dvar_set2("MMQKQOSTNS", 0);
			}
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			ImGui::Checkbox(xorstr_("No Shield Shake"), &g_vars->msettings.b_shield);
			if (g_vars->msettings.b_shield)
			{
				dvar_set2("LQKTTRTSNS", 0);
			}
			else
			{
				dvar_set2("LQKTTRTSNS", 1);
			}
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			if (ImGui::Button(xorstr_("Disable Name Profanity"), ImVec2(-5, 25)))
			{
				dvar_set2(xorstr_("PLTMTSLKT"), 1);
			}
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			if (ImGui::Button(xorstr_("Skip Tutorial"), ImVec2(-5, 25)))
			{
				dvar_set2(xorstr_("LSPSKLPNQT"), 1);
			}
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			if (ImGui::Button(xorstr_("Start Caldera Private Match"), ImVec2(-5, 25)))
			{
				dvar_set2(xorstr_("LOQQOSNQKN"), 1);
				dvar_set2(xorstr_("PKMLMMTSN"), 1);
			}

		}
		ImGui::EndChild();
	}
	ImGui::EndGroupBox();
}
static const char* itemclantag[] = { "Logo IW", "Logo RVN", "Logo SHG","Logo DW","Logo HMS","Logo BNOX","Logo 3ARC","Logo VV","Logo TFB" ,"Logo KING", "Logo Blizzard","Red 1W","Red LW","Red IW DEV","Red RAVN","Red RAVEN","Red R4VEN", "Red OW", "Red BN0X","Red 34RC","Red ATVI" };
static const char* current_clantag = "Select Clan Tag";

static char customclantag[5] = "";

void clantag()
{
	ImGui::BeginGroupBox(xorstr_("##CLAGTAGS"), ImVec2(0, 115));
	{
		for (int i = 0; i < 8; i++)
		{
			ImGui::Spacing();
			ImGui::SameLine();
		}

		if (ImGui::BeginCombo("##combo4", current_clantag)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(itemclantag); n++)
			{
				bool is_selected4 = (current_clantag == itemclantag[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(itemclantag[n], is_selected4))
					current_clantag = itemclantag[n];
				if (is_selected4)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
			}
			ImGui::EndCombo();
		}
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		if (ImGui::Button(xorstr_("Set Clan Tag"), ImVec2(-5, 20))) {
			if (current_clantag == "Logo IW")
				CL_PlayerData_SetCustomClanTag("iw");
			if (current_clantag == "Logo RVN")
				CL_PlayerData_SetCustomClanTag("rvn");
			if (current_clantag == "Logo SHG")
				CL_PlayerData_SetCustomClanTag("shg");
			if (current_clantag == "Logo DW")
				CL_PlayerData_SetCustomClanTag("dw");
			if (current_clantag == "Logo HMS")
				CL_PlayerData_SetCustomClanTag("hms");
			if (current_clantag == "Logo BNOX")
				CL_PlayerData_SetCustomClanTag("bnox");
			if (current_clantag == "Logo 3ARC")
				CL_PlayerData_SetCustomClanTag("3arc");
			if (current_clantag == "Logo VV")
				CL_PlayerData_SetCustomClanTag("vv");
			if (current_clantag == "Logo TFB")
				CL_PlayerData_SetCustomClanTag("tfb");
			if (current_clantag == "Red 1W")
				CL_PlayerData_SetCustomClanTag("1W");
			if (current_clantag == "Red LW")
				CL_PlayerData_SetCustomClanTag("LW");
			if (current_clantag == "Red IW DEV")
				CL_PlayerData_SetCustomClanTag("IWDev");
			if (current_clantag == "Red RAVN")
				CL_PlayerData_SetCustomClanTag("RAVN");
			if (current_clantag == "Red RAVEN")
				CL_PlayerData_SetCustomClanTag("RAVEN");
			if (current_clantag == "Red R4VEN")
				CL_PlayerData_SetCustomClanTag("R4VEN");
			if (current_clantag == "Red OW")
				CL_PlayerData_SetCustomClanTag("OW");
			if (current_clantag == "Red BN0X")
				CL_PlayerData_SetCustomClanTag("BN0X");
			if (current_clantag == "Red 34RC")
				CL_PlayerData_SetCustomClanTag("34RC");
			if (current_clantag == "Red ATVI")
				CL_PlayerData_SetCustomClanTag("ATVI");
			if (current_clantag == "Logo KING")
				CL_PlayerData_SetCustomClanTag("KING");
			if (current_clantag == "Logo Blizzard")
				CL_PlayerData_SetCustomClanTag("BLIZ");
		}
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		for (int i = 0; i < 8; i++)
		{
			ImGui::Spacing();
			ImGui::SameLine();
		}
		ImGui::InputTextWithHint(xorstr_("##CLANTAG"), xorstr_("Custom Clan Tag"), customclantag, sizeof(customclantag));
		ImGui::Dummy(ImVec2(0.0f, 1.0f));
		if (ImGui::Button(xorstr_("Set Custom Tag"), ImVec2(-5, 20)))
		{
			CL_PlayerData_SetCustomClanTag(customclantag);
		}
	}
	ImGui::EndGroupBox();
}
float color_menu[4]{ 255 / 255.f, 28 / 255.f, 247 / 255.f, 1.0f };
static std::string tabs[] = { "Visual's","Dvar's", "Operator's", "Loadout's", "ClanTag's" };
int active_tab = -1;

void cMenu::Menu()
{

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_ButtonHovered] = ImColor(43, 43, 43);

	colors[ImGuiCol_WindowBg] = ImColor(43, 43, 43);
	colors[ImGuiCol_ChildBg] = ImColor(43, 43, 43);
	colors[ImGuiCol_PopupBg] = ImColor(43, 43, 43);
	colors[ImGuiCol_FrameBgHovered] = ImColor(43, 43, 43);
	colors[ImGuiCol_FrameBg] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_Border] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255);
	colors[ImGuiCol_FrameBgActive] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_Header] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.0f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 0.86f);
	colors[ImGuiCol_HeaderActive] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255);
	colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_Button] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_TextDisabled] = ImColor(255, 255, 255);




	ImGuiStyle* style = &ImGui::GetStyle();
	style->FramePadding = ImVec2(4, 2);
	style->ItemSpacing = ImVec2(10, 2);
	style->IndentSpacing = 12;
	style->ScrollbarSize = 10;

	style->WindowRounding = 4;
	style->FrameRounding = 4;
	style->PopupRounding = 4;
	style->ScrollbarRounding = 6;
	style->GrabRounding = 4;
	style->TabRounding = 4;

	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style->WindowMenuButtonPosition = ImGuiDir_Right;
	style->DisplaySafeAreaPadding = ImVec2(4, 4);




	if (ImGui::Begin(xorstr_("##MENU"), NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
	{
		ImGui::SetNextWindowSize({ 430 , 500 }, ImGuiCond_Always);
		int dwWidth = GetSystemMetrics(SM_CXSCREEN) / 3;
		int dwHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
		ImGui::SetWindowPos(ImVec2(dwWidth * 2.0f, dwHeight * 0.2f), ImGuiCond_Once);
		ImGui::PushFont(MainCaps);

		if (ImGui::BeginChild("Line", ImVec2(-1, 25), false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {

			ImVec2 p = ImGui::GetCursorScreenPos();

			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x, p.y + 3),
				ImVec2(p.x + ImGui::GetWindowWidth(), p.y + -2), ImColor(color_menu[0], color_menu[1], color_menu[2]));

			ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(p.x, p.y + 3),
				ImVec2(p.x + ImGui::GetWindowWidth() / 2, p.y + -3), ImColor(0, 0, 0, 125), ImColor(0, 0, 0, 15), ImColor(0, 0, 0, 15), ImColor(0, 0, 0, 125));

			ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(p.x + ImGui::GetWindowWidth() / 2, p.y + 3),
				ImVec2(p.x + ImGui::GetWindowWidth(), p.y + -3), ImColor(0, 0, 0, 15), ImColor(0, 0, 0, 125), ImColor(0, 0, 0, 125), ImColor(0, 0, 0, 15));

			ImGui::GetWindowDrawList()->AddLine(ImVec2(p.x, p.y + 2), ImVec2(p.x + ImGui::GetWindowWidth(), p.y + 2), ImColor(0, 0, 0, 150));

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(rebrand.c_str()).x) / 2);
			ImGui::TextColored(ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.0f), rebrand.c_str());

		}
		ImGui::EndChild();
		ImGui::PopFont();
		/*ImGui::PushFont(Main);
		layout();
		ImGui::PopFont();*/

		ImGui::PushFont(Main);
		for (int i = 0; i < IM_ARRAYSIZE(tabs); i++) {
			if (ImGui::Tab(tabs[i].c_str(), active_tab == i, ImVec2(115, 50))) {
				active_tab = i;
			}
			if (i < (IM_ARRAYSIZE(tabs) - 1))
				ImGui::SameLine();
		}
		ImGui::PopFont();
		ImGui::PushFont(FMenu);

		switch (active_tab) {
		case 0: visual(); break;
		case 1: dvars();   break;
		case 2:	op(); break;
		case 3: loadout(); break;
		case 4: clantag(); break;
		}


		ImGui::PopFont();
	}
	ImGui::End();
}

void cMenu::Informatio()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_ButtonHovered] = ImColor(43, 43, 43);
	colors[ImGuiCol_TitleBg] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_WindowBg] = ImColor(43, 43, 43);
	colors[ImGuiCol_ChildBg] = ImColor(43, 43, 43);
	colors[ImGuiCol_PopupBg] = ImColor(43, 43, 43);
	colors[ImGuiCol_FrameBgHovered] = ImColor(43, 43, 43);
	colors[ImGuiCol_FrameBg] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_Border] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255);
	colors[ImGuiCol_FrameBgActive] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_Header] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.0f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 0.86f);
	colors[ImGuiCol_HeaderActive] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255);
	colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_Button] = ImVec4(color_menu[0], color_menu[1], color_menu[2], 1.00f);
	colors[ImGuiCol_TextDisabled] = ImColor(255, 255, 255);



	ImGuiStyle* style = &ImGui::GetStyle();
	style->FramePadding = ImVec2(4, 2);
	style->ItemSpacing = ImVec2(10, 2);
	style->IndentSpacing = 12;
	style->ScrollbarSize = 10;

	style->WindowRounding = 4;
	style->FrameRounding = 4;
	style->PopupRounding = 4;
	style->ScrollbarRounding = 6;
	style->GrabRounding = 4;
	style->TabRounding = 4;

	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style->WindowMenuButtonPosition = ImGuiDir_Right;
	style->DisplaySafeAreaPadding = ImVec2(4, 4);
	ImGui::PushFont(Main);
	ImGui::SetNextWindowSize(ImVec2(380, 280), ImGuiCond_Always);
	ImGui::Begin(xorstr_("Colors & Symbols"), &g_vars->msettings.b_textinputnInfo, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
	int dwWidth = GetSystemMetrics(SM_CXSCREEN) / 4;
	int dwHeight = GetSystemMetrics(SM_CYSCREEN) / 3;
	ImGui::SetWindowPos(ImVec2(dwWidth * 2.0f, dwHeight * 0.2f), ImGuiCond_Once);
	ImGui::Dummy(ImVec2(0.0f, 1.0f));

	for (int i = 0; i < 5; i++)
	{
		ImGui::Spacing();
		ImGui::SameLine();
	}
	ImGui::Checkbox(xorstr_("Add Color To Text"), &usetextcolor);
	ImGui::Dummy(ImVec2(0.0f, 1.0f));
	for (int i = 0; i < 5; i++)
	{
		ImGui::Spacing();
		ImGui::SameLine();
	}
	if (usetextcolor)
	{
		if (ImGui::BeginCombo(xorstr_("##colorcombo"), color_current_item)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(color_items); n++)
			{
				bool is_selected = (color_current_item == color_items[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(color_items[n], is_selected))
					color_current_item = color_items[n];
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
			}
			ImGui::EndCombo();
		}
	}

	ImGui::Dummy(ImVec2(0.0f, 1.0f));
	for (int i = 0; i < 5; i++)
	{
		ImGui::Spacing();
		ImGui::SameLine();
	}

	ImGui::Checkbox(xorstr_("Add Button/Images before text"), &befortext);
	ImGui::Dummy(ImVec2(0.0f, 1.0f));
	for (int i = 0; i < 5; i++)
	{
		ImGui::Spacing();
		ImGui::SameLine();
	}
	if (befortext)
	{
		if (ImGui::BeginCombo(xorstr_("##beforecombo"), before_current_item)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(before_items); n++)
			{
				bool is_selected = (before_current_item == before_items[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(before_items[n], is_selected))
					before_current_item = before_items[n];
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
			}
			ImGui::EndCombo();
		}
	}

	ImGui::Dummy(ImVec2(0.0f, 1.0f));
	for (int i = 0; i < 5; i++)
	{
		ImGui::Spacing();
		ImGui::SameLine();
	}

	ImGui::Checkbox(xorstr_("Add Button/Images after text"), &aftertext);
	ImGui::Dummy(ImVec2(0.0f, 1.0f));
	for (int i = 0; i < 5; i++)

	{
		ImGui::Spacing();
		ImGui::SameLine();
	}
	if (aftertext)
	{
		if (ImGui::BeginCombo(xorstr_("##aftercombo"), after_current_item)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(after_items); n++)
			{
				bool is_selected = (after_current_item == after_items[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(after_items[n], is_selected))
					after_current_item = after_items[n];
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
			}
			ImGui::EndCombo();
		}
	}

	ImGui::End();
	ImGui::PopFont();
}
