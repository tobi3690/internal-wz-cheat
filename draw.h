#pragma once
#include "framework.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "globals.h"
#include "color.h"
#include "vec.h"
#include "vec2.h"
#include "sdk.h"

namespace draw
{
	void draw_line(const ImVec2& from, const ImVec2& to, C_Color color, float thickness);
	void draw_crosshair();
	void draw_box(const float x, const float y, const float width, const float height, const C_Color color, float thickness);
	void draw_corned_box(const POINT& rect, const POINT& size, C_Color color, float thickness);
	void draw_sketch_edge_text(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, C_Color color, bool center);
	void draw_bones(unsigned long i, float size, C_Color color, float x, float y, float w, float h);
	bool World2Screen(const Vector3& WorldPos, Vector2* ScreenPos, Vector2* BoxSize);
	bool w2s(Vector3 vOrigin, Vector2* vOut);
	bool getBonesIndex(int entityNum, unsigned int boneIndex, Vector3* bonePos);
	void draw_health(int i_health, Vector3 pos);
}
