#include "draw.h"
#define D3DX_PI    ((FLOAT)  3.141592654f)

namespace fb
{
	struct Vec2 { union { float v[2]; struct { float x; float y; }; }; };
	struct Vec3 { union { float v[3]; struct { float x; float y; float z; }; }; };
struct Vec4 { public: union { float v[4]; struct { float x; float y; float z; float w; }; }; };
					static Vec4 asVec4V(float x, float y, float z, float w) { Vec4 out; out.x = x; out.y = y; out.z = z; out.w = w; return out; }
					struct Matrix4x4 { union { Vec4 v[4]; float m[4][4]; struct { Vec4 right; Vec4 up; Vec4 forward; Vec4 trans; }; }; };
					typedef Matrix4x4 LinearTransform;

					struct AxisAlignedBox
					{
						Vec4 min;
						Vec4 max;
					};

					struct LinearTransform_AABB
					{
					public:
						LinearTransform m_Transform;
						AxisAlignedBox m_Box;
						char _pad[0x200];
					};

}

namespace draw
{
	void draw_line(const ImVec2& from, const ImVec2& to, C_Color color, float thickness)
	{
		ImGui::GetBackgroundDrawList()->AddLine(from, to, color.GetU32(), thickness);
	}

	void fill_rectangle(const float x, const float y, const float width, const float hight, const C_Color color)
	{
		const float end_y = y + hight;
		for (float curr_y = y; curr_y < end_y; ++curr_y)
		{
			draw_line(ImVec2(x, curr_y), ImVec2(x + width, curr_y), color, 1.5f);
		}
	}

	void draw_crosshair()
	{
		constexpr long crosshair_size = 10.0f;
		ImVec2 origin;
		origin.x = sdk::refdef->Width / static_cast<float>(2);
		origin.y = sdk::refdef->Height / static_cast<float>(2);
		draw_line(ImVec2((origin.x), (origin.y) - crosshair_size), ImVec2((origin.x), (origin.y) + crosshair_size), g_vars->msettings.crosshair_color.color(), 1.5f);
		draw_line(ImVec2((origin.x) - crosshair_size, (origin.y)), ImVec2((origin.x) + crosshair_size, (origin.y)), g_vars->msettings.crosshair_color.color(), 1.5f);
	}

	void draw_box(const float x, const float y, const float width, const float height, const C_Color color, float thickness)
	{
		draw_line(ImVec2(x, y), ImVec2(x + width, y), color, thickness);
		draw_line(ImVec2(x, y), ImVec2(x, y + height), color, thickness);
		draw_line(ImVec2(x, y + height), ImVec2(x + width, y + height), color, thickness);
		draw_line(ImVec2(x + width, y), ImVec2(x + width, y + height), color, thickness);
	}

	void draw_corned_box(const POINT& rect, const POINT& size, C_Color color, float thickness)
	{
		size.x - 5;
		const float lineW = (size.x / 5);
		const float lineH = (size.y / 6);
		const float lineT = 1;

		//outline
		draw_line(ImVec2(rect.x - lineT, rect.y - lineT), ImVec2(rect.x + lineW, rect.y - lineT), color, thickness); //top left
		draw_line(ImVec2(rect.x - lineT, rect.y - lineT), ImVec2(rect.x - lineT, rect.y + lineH), color, thickness);
		draw_line(ImVec2(rect.x - lineT, rect.y + size.y - lineH), ImVec2(rect.x - lineT, rect.y + size.y + lineT), color, thickness); //bot left
		draw_line(ImVec2(rect.x - lineT, rect.y + size.y + lineT), ImVec2(rect.x + lineW, rect.y + size.y + lineT), color, thickness);
		draw_line(ImVec2(rect.x + size.x - lineW, rect.y - lineT), ImVec2(rect.x + size.x + lineT, rect.y - lineT), color, thickness); // top right
		draw_line(ImVec2(rect.x + size.x + lineT, rect.y - lineT), ImVec2(rect.x + size.x + lineT, rect.y + lineH), color, thickness);
		draw_line(ImVec2(rect.x + size.x + lineT, rect.y + size.y - lineH), ImVec2(rect.x + size.x + lineT, rect.y + size.y + lineT), color, thickness); // bot right
		draw_line(ImVec2(rect.x + size.x - lineW, rect.y + size.y + lineT), ImVec2(rect.x + size.x + lineT, rect.y + size.y + lineT), color, thickness);

		//inline
		draw_line(ImVec2(rect.x, rect.y), ImVec2(rect.x, rect.y + lineH), color, thickness);//top left
		draw_line(ImVec2(rect.x, rect.y), ImVec2(rect.x + lineW, rect.y), color, thickness);
		draw_line(ImVec2(rect.x + size.x - lineW, rect.y), ImVec2(rect.x + size.x, rect.y), color, thickness); //top right
		draw_line(ImVec2(rect.x + size.x, rect.y), ImVec2(rect.x + size.x, rect.y + lineH), color, thickness);
		draw_line(ImVec2(rect.x, rect.y + size.y - lineH), ImVec2(rect.x, rect.y + size.y), color, thickness); //bot left
		draw_line(ImVec2(rect.x, rect.y + size.y), ImVec2(rect.x + lineW, rect.y + size.y), color, thickness);
		draw_line(ImVec2(rect.x + size.x - lineW, rect.y + size.y), ImVec2(rect.x + size.x, rect.y + size.y), color, thickness);//bot right
		draw_line(ImVec2(rect.x + size.x, rect.y + size.y - lineH), ImVec2(rect.x + size.x, rect.y + size.y), color, thickness);
	}

	void draw_sketch_edge_text(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, C_Color color, bool center)
	{
		constexpr float fStrokeVal1 = 1.0f;
		ImVec4 EdgeColor = ImVec4(0.0f, 0.f, 0.f, 255.f);
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		std::stringstream steam(text);
		std::string line;
		int i = 0;
		while (std::getline(steam, line))
		{
			ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());
			if (center)
			{
				window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - fStrokeVal1, pos.y + textSize.y * i), ImGui::GetColorU32(EdgeColor), line.c_str());
				window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + fStrokeVal1, pos.y + textSize.y * i), ImGui::GetColorU32(EdgeColor), line.c_str());
				window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f), (pos.y + textSize.y * i) - fStrokeVal1), ImGui::GetColorU32(EdgeColor), line.c_str());
				window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f), (pos.y + textSize.y * i) + fStrokeVal1), ImGui::GetColorU32(EdgeColor), line.c_str());
				window->DrawList->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), color.GetU32(), line.c_str());
			}
			else
			{
				window->DrawList->AddText(pFont, size, ImVec2((pos.x) - fStrokeVal1, (pos.y + textSize.y * i)), ImGui::GetColorU32(EdgeColor), line.c_str());
				window->DrawList->AddText(pFont, size, ImVec2((pos.x) + fStrokeVal1, (pos.y + textSize.y * i)), ImGui::GetColorU32(EdgeColor), line.c_str());
				window->DrawList->AddText(pFont, size, ImVec2((pos.x), (pos.y + textSize.y * i) - fStrokeVal1), ImGui::GetColorU32(EdgeColor), line.c_str());
				window->DrawList->AddText(pFont, size, ImVec2((pos.x), (pos.y + textSize.y * i) + fStrokeVal1), ImGui::GetColorU32(EdgeColor), line.c_str());
				window->DrawList->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), color.GetU32(), line.c_str());
			}
			i++;
		}
	}

	bool is_valid_bone(Vector2* screenPos, const long Count, float x, float y, float w, float h)
	{
		constexpr long size = 30;

		float r = x + w + size;
		float b = y + h;

		x -= size;

		for (long i = 0; i < Count; ++i)
		{
			if (screenPos[i].x < x || screenPos[i].x > r || screenPos[i].y < y || screenPos[i].y > b)
				return false;
		}
		return true;
	}

	Vector3 get_camera_location()
	{
		float x = *(float*)(*(uint64_t*)(g_vars->baseModule + g_vars->goffsets.camera_ptr) + g_vars->goffsets.camera_view_x);
		float y = *(float*)(*(uint64_t*)(g_vars->baseModule + g_vars->goffsets.camera_ptr) + g_vars->goffsets.camera_view_y);
		float z = *(float*)(*(uint64_t*)(g_vars->baseModule + g_vars->goffsets.camera_ptr) + g_vars->goffsets.camera_view_z);
		return Vector3(x, y, z);
	}


	bool World2Screen(const Vector3& WorldPos, Vector2* ScreenPos)
	{
		auto refdef = sdk::refdef;
		Vector3 mylocation = get_camera_location();

		Vector3 vLocal = WorldPos - mylocation;
		Vector3 vTrans = Vector3(vLocal.Dot(refdef->view.axis[1]), vLocal.Dot(refdef->view.axis[2]), vLocal.Dot(refdef->view.axis[0]));

		if (vTrans.z < 0.01f)
			return false;

		ScreenPos->x = (((float)refdef->Width / 2) * (1 - (vTrans.x / refdef->view.tanHalfFov.x / vTrans.z)));
		ScreenPos->y = (((float)refdef->Height / 2) * (1 - (vTrans.y / refdef->view.tanHalfFov.y / vTrans.z)));

		/*if (ScreenPos->x > refdef->Width || ScreenPos->y > refdef->Height || ScreenPos->x < 0 || ScreenPos->y < 0)
			return false;*/

		return true;
	}
	bool bones_to_screen(Vector3* BonePosArray, Vector2* ScreenPosArray, const long Count)
	{
		for (long i = 0; i < Count; ++i)
		{
			if (!World2Screen(BonePosArray[i], &ScreenPosArray[i]))
				return false;
		}
		return true;
	}
	void draw_bones(Vector2* bone_ScreenPos, long count, C_Color color, float size)
	{

		long last_count = count - 1;
		for (long i = 0; i < last_count; ++i)
			draw::draw_line(ImVec2(bone_ScreenPos[i].x, bone_ScreenPos[i].y), ImVec2(bone_ScreenPos[i + 1].x, bone_ScreenPos[i + 1].y), color, size);
	}
	void draw_bones(unsigned long i, float size, C_Color color, float x, float y, float w, float h)
	{
		Vector3 header_to_bladder[6], right_foot_to_bladder[5], left_foot_to_bladder[5], right_hand[5], left_hand[5];
		Vector2 screen_header_to_bladder[6], screen_right_foot_to_bladder[5], screen_left_foot_to_bladder[5], screen_right_hand[5], screen_left_hand[5];

		if (sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_HEAD, &header_to_bladder[0]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_NECK, &header_to_bladder[1]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_CHEST, &header_to_bladder[2]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_MID, &header_to_bladder[3]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_TUMMY, &header_to_bladder[4]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_PELVIS, &header_to_bladder[5]) &&

			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_RIGHT_FOOT_1, &right_foot_to_bladder[1]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_RIGHT_FOOT_2, &right_foot_to_bladder[2]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_RIGHT_FOOT_3, &right_foot_to_bladder[3]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_RIGHT_FOOT_4, &right_foot_to_bladder[4]) &&

			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_LEFT_FOOT_1, &left_foot_to_bladder[1]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_LEFT_FOOT_2, &left_foot_to_bladder[2]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_LEFT_FOOT_3, &left_foot_to_bladder[3]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_LEFT_FOOT_4, &left_foot_to_bladder[4]) &&

			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_LEFT_HAND_1, &right_hand[1]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_LEFT_HAND_2, &right_hand[2]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_LEFT_HAND_3, &right_hand[3]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_LEFT_HAND_4, &right_hand[4]) &&

			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_RIGHT_HAND_1, &left_hand[1]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_RIGHT_HAND_2, &left_hand[2]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_RIGHT_HAND_3, &left_hand[3]) &&
			sdk::get_bone_by_index(i, sdk::BONE_INDEX::BONE_POS_RIGHT_HAND_4, &left_hand[4]))
		{
			right_foot_to_bladder[0] = header_to_bladder[5];
			left_foot_to_bladder[0] = header_to_bladder[5];
			right_hand[0] = header_to_bladder[3];
			left_hand[0] = header_to_bladder[3];

			if (bones_to_screen(header_to_bladder, screen_header_to_bladder, 6))
				if (is_valid_bone(screen_header_to_bladder, 6, x, y, w, h))
					draw_bones(screen_header_to_bladder, 6, color, size);

			if (bones_to_screen(right_foot_to_bladder, screen_right_foot_to_bladder, 5))
				if (is_valid_bone(screen_right_foot_to_bladder, 5, x, y, w, h))
					draw_bones(screen_right_foot_to_bladder, 5, color, size);

			if (bones_to_screen(left_foot_to_bladder, screen_left_foot_to_bladder, 5))
				if (is_valid_bone(screen_left_foot_to_bladder, 5, x, y, w, h))
					draw_bones(screen_left_foot_to_bladder, 5, color, size);

			if (bones_to_screen(right_hand, screen_right_hand, 5))
				if (is_valid_bone(screen_right_hand, 5, x, y, w, h))
					draw_bones(screen_right_hand, 5, color, size);

			if (bones_to_screen(left_hand, screen_left_hand, 5))
				if (is_valid_bone(screen_left_hand, 5, x, y, w, h))
					draw_bones(screen_left_hand, 5, color, size);
		}
	}

	

	float xangle(const Vector3& LocalPos, const Vector3& WorldPos)
	{
		float dl = sqrt((WorldPos.x - LocalPos.x) * (WorldPos.x - LocalPos.x) + (WorldPos.y - LocalPos.y) * (WorldPos.y - LocalPos.y));

		if (dl == 0.0f)
			dl = 1.0f;

		float dl2 = abs(WorldPos.x - LocalPos.x);
		float teta = ((180.0f / D3DX_PI) * acos(dl2 / dl));

		if (WorldPos.x < LocalPos.x)
			teta = 180.0f - teta;

		if (WorldPos.y < LocalPos.y)
			teta = teta * -1.0f;

		if (teta > 180.0f)
			teta = (360.0f - teta) * (-1.0f);

		if (teta < -180.0f)
			teta = (360.0f + teta);

		return teta;
	}

	void rotation_point_alpha(float x, float y, float z, float alpha, Vector3* outVec3)
	{
		static HMODULE hD3dx9_43 = NULL;
		if (hD3dx9_43 == NULL)
			hD3dx9_43 = LoadLibraryA(xorstr("d3dx9_43.dll").crypt_get());


		typedef fb::LinearTransform* (WINAPI* t_D3DXMatrixRotationY)(fb::LinearTransform* pOut, FLOAT Angle);
		static t_D3DXMatrixRotationY D3DXMatrixRotationY = NULL;
		if (D3DXMatrixRotationY == NULL)
			D3DXMatrixRotationY = (t_D3DXMatrixRotationY)GetProcAddress(hD3dx9_43, xorstr("D3DXMatrixRotationY").crypt_get());

		typedef fb::Vec4* (WINAPI* t_D3DXVec3Transform)(fb::Vec4* pOut, CONST fb::Vec4* pV, CONST fb::LinearTransform* pM);
		static t_D3DXVec3Transform D3DXVec4Transform = NULL;
		if (D3DXVec4Transform == NULL)
			D3DXVec4Transform = (t_D3DXVec3Transform)GetProcAddress(hD3dx9_43, xorstr("D3DXVec4Transform").crypt_get());

		Matrix4x4 rot1;
		Vector4 vec = { x, z, y, 1.0f };
		D3DXMatrixRotationY((fb::LinearTransform*)&rot1, alpha * D3DX_PI / 180.0f);
		D3DXVec4Transform((fb::Vec4*)&vec, (const fb::Vec4*)&vec, (const  fb::LinearTransform*)&rot1);

		outVec3->x = vec.x;
		outVec3->y = vec.z;
		outVec3->z = vec.y;
	};

	

	bool World2Screen(const Vector3& WorldPos, Vector2* ScreenPos, Vector2* BoxSize)
	{
		auto ViewOrig = get_camera_location();

		float angleX = xangle(ViewOrig, WorldPos);

		Vector3 posl, posr;

		rotation_point_alpha(-16.0f, 0.0f, 65.0f, -angleX + 90.0f, &posl);
		rotation_point_alpha(16.0f, 0.0f, -5.0f, -angleX + 90.0f, &posr);

		Vector3 vposl, vposr;

		vposl.x = WorldPos.x + posl.x;
		vposl.y = WorldPos.y + posl.y;
		vposl.z = WorldPos.z + posl.z;

		vposr.x = WorldPos.x + posr.x;
		vposr.y = WorldPos.y + posr.y;
		vposr.z = WorldPos.z + posr.z;

		Vector2 screenPosl, screenPosr;

		if (!World2Screen(vposl, &screenPosl) || !World2Screen(vposr, &screenPosr))
		{
			return false;
		}

		BoxSize->x = abs(screenPosr.x - screenPosl.x);
		BoxSize->y = abs(screenPosl.y - screenPosr.y);

		ScreenPos->x = screenPosr.x - BoxSize->x;
		ScreenPos->y = screenPosl.y;

		return true;
	}
	bool w2s(Vector3 vOrigin, Vector2* vOut)
	{
		return false;
	}
	bool getBonesIndex(int entityNum, unsigned int boneIndex, Vector3* bonePos)
	{
		return false;
	}

	bool w2saim(const Vector3& WorldPos, POINT* ScreenPos, bool isBone = false)
	{
		auto refdefs = sdk::get_refdef();
		Vector3 myLocation = get_camera_location();

		Vector3 vLocal = WorldPos - myLocation; // worldLocation - cameraPosition; 
		Vector3 vTrans = Vector3(vLocal.Dot(refdefs->view.axis[1]), vLocal.Dot(refdefs->view.axis[2]),
			vLocal.Dot(refdefs->view.axis[0]));

		if (vTrans.z < 0.01f)
			return false;

		ScreenPos->x = ((refdefs->Width / 2) * (1 - (vTrans.x / refdefs->view.tanHalfFov.x / vTrans.z)));
		ScreenPos->y = ((refdefs->Height / 2) * (1 - (vTrans.y / refdefs->view.tanHalfFov.y / vTrans.z)));


		if (!isBone)
		{
			if (ScreenPos->x > refdefs->Width || ScreenPos->y > refdefs->Height || ScreenPos->x < 0 || ScreenPos->y < 0)
				return false;
		}

	}

	void draw_health(int i_health, Vector3 pos)
	{
		POINT bottom, top;

		if (!w2saim(pos, &bottom))
			return;

		pos.z += 60;
		if (!w2saim(pos, &top))
			return;

		top.y -= 5;
		auto height = top.y - bottom.y;
		auto width = height / 2.f;
		auto x = top.x - width / 1.8f;
		auto y = top.y;

		auto bar_width = max(0, min(127, i_health)) * (bottom.y - top.y) / 127.f;
		auto health = max(0, min(127, i_health));
		auto color_health = g_vars->msettings.Red;
		auto color_health1 = g_vars->msettings.Green;
		fill_rectangle(x, y, 4, 127 * (bottom.y - top.y) / 127.f, color_health.color());
		fill_rectangle(x + 1, y + 1, 2, bar_width - 2, color_health1.color());
	}
}