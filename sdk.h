#pragma once
#include "framework.h"
#include "globals.h"
#include "vec.h"
#include "vec2.h"
#include "client.h"
#include "bone.h"
#include "draw.h"
#include "spoofcall.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#define is_valid_ptr(p) ((uintptr_t)(p) <= 0x7FFFFFFEFFFF && (uintptr_t)(p) >= 0x1000) 
#define is_bad_ptr(p)	(!is_valid_ptr(p))

extern HMODULE m_hModule;

template <typename T>
bool IsValidPtr(PVOID ptr)
{
	if (is_bad_ptr(ptr))return false;
	else
		return true;

}

namespace process
{
	extern HWND hwnd;
	BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam);
	HWND get_process_window();
	HWND get_process_window(DWORD procID);
}

namespace sdk
{
	enum BONE_INDEX : unsigned long
	{

		BONE_POS_HELMET = 8,

		BONE_POS_HEAD = 7,
		BONE_POS_NECK = 6,
		BONE_POS_CHEST = 5,
		BONE_POS_MID = 4,
		BONE_POS_TUMMY = 3,
		BONE_POS_PELVIS = 2,

		BONE_POS_RIGHT_FOOT_1 = 21,
		BONE_POS_RIGHT_FOOT_2 = 22,
		BONE_POS_RIGHT_FOOT_3 = 23,
		BONE_POS_RIGHT_FOOT_4 = 24,

		BONE_POS_LEFT_FOOT_1 = 17,
		BONE_POS_LEFT_FOOT_2 = 18,
		BONE_POS_LEFT_FOOT_3 = 19,
		BONE_POS_LEFT_FOOT_4 = 20,

		BONE_POS_LEFT_HAND_1 = 13,
		BONE_POS_LEFT_HAND_2 = 14,
		BONE_POS_LEFT_HAND_3 = 15,
		BONE_POS_LEFT_HAND_4 = 16,

		BONE_POS_RIGHT_HAND_1 = 9,
		BONE_POS_RIGHT_HAND_2 = 10,
		BONE_POS_RIGHT_HAND_3 = 11,
		BONE_POS_RIGHT_HAND_4 = 12
	};

	enum STANCE : int
	{
		STAND = 0,
		CROUNCH = 1,
		PRONE = 2,
		KNOCKED = 3
	};

	extern class cg_client
	{
	public:

		int32_t get_index();

		bool is_valid();

		bool is_dead();

		int32_t get_team_id();

		int32_t get_stance();

		uint64_t get_pos();
	};

	cg_client* get_playerinfo(int entityNum);
	cg_client* get_localentity();

	class name_t {
	public:
		uint32_t idx;
		//char unk0[0x10];
		char name[36];
		uint8_t unk1[0x64];
		uint32_t health;
	};

	class RefdefView
	{
	public:
		Vector2 tanHalfFov; // 0x00
		unsigned __int8 unk1[0xC]; // 0x08
		Vector3 axis[3]; // 0x14
	};

	class refdef_t
	{
	public:
		int x; // 0x00
		int y; // 0x04
		int Width; // 0x08
		int Height; // 0x0C
		RefdefView view; // 0x10
	};

	class posInfo_t
	{
	public:
		float get_rotation() const;
	public:
		char pad_0x0[0xC];
		DWORD nIsSoldierEntity;     //this+0xC
		char pad_0x10[0x8];
		void* m_next_member;        //this+0x18
		char pad_0x20[0x18];
		char flags[8];              //this+0x38
		Vector3 m_position;         //this+0x40
		char pad_0x4C[0xC];
		float m_rotation;           //this+0x58
	};

	extern refdef_t* refdef;
	
	bool in_game();
	int get_max_player_acount();
	void clear_cached();
	refdef_t* get_refdef();
	uint64_t get_visible_base(int i);
	bool is_visible(int i);
	void update_last_visible();
	
	bool get_bone_by_index(int i, int bone_id, Vector3* out_pos);
	int get_player_health(int entityNum);
	std::string get_player_name(int entityNum);
	void no_recoil();
}

namespace g_game
{
	void init(ImFont* font);
}


/* 430 */
struct unnamed_type_enumeration
{
	int stringCount;
	const char* strings;
};

/* 431 */
struct unnamed_type_integer
{
	int min;
	int max;
};

/* 432 */
struct unnamed_type_integer64
{
	__int64 min;
	__int64 max;
};

/* 433 */
struct unnamed_type_unsignedInt64
{
	unsigned __int64 min;
	unsigned __int64 max;
};

/* 434 */
struct unnamed_type_value
{
	float min;
	float max;
	float devguiStep;
};

/* 435 */
struct unnamed_type_vector
{
	float min;
	float max;
	float devguiStep;
};

/* 436 */
union DvarLimits
{
	unnamed_type_enumeration enumeration;
	unnamed_type_integer integer;
	unnamed_type_integer64 integer64;
	unnamed_type_unsignedInt64 unsignedInt64;
	unnamed_type_value value;
	unnamed_type_vector vector;
};

union DvarValue
{
	bool enabled; //0x0000
	int32_t integer; //0x0000
	uint32_t unsignedInt; //0x0000
	float value; //0x0000
	//Vector4 vector; //0x0000
	const char* string; //0x0000
	unsigned __int8 color[4]; //0x0000
	uint64_t unsignedInt64; //0x0000
	int64_t integer64; //0x0000
};

typedef enum DvarType : uint8_t
{
	DVAR_TYPE_BOOL = 0x0,
	DVAR_TYPE_FLOAT = 0x1,
	DVAR_TYPE_FLOAT_2 = 0x2,
	DVAR_TYPE_FLOAT_3 = 0x3,
	DVAR_TYPE_FLOAT_4 = 0x4,
	DVAR_TYPE_INT = 0x5,
	DVAR_TYPE_INT64 = 0x6,
	DVAR_TYPE_UINT64 = 0x7,
	DVAR_TYPE_ENUM = 0x8,
	DVAR_TYPE_STRING = 0x9,
	DVAR_TYPE_COLOR = 0xA,
	DVAR_TYPE_FLOAT_3_COLOR = 0xB,
	DVAR_TYPE_COUNT = 0xC,
} DvarType;


struct dvar_s
{
	char name[4]; //0x0
	uint32_t flags; //0x4
	BYTE level[1]; //0x8
	DvarType type; //0x9
	bool modified; //0xA
	uint32_t checksum; //0xC
	char* description; //0x10
	char pad2[16]; //0x18
	unsigned __int16 hashNext; //0x28
	DvarValue current; //0x30
	DvarValue latched; //0x40
	DvarValue reset; //0x50
	DvarLimits domain; //0x60
	//BbConstUsageFlags BbConstUsageFlags;
};


dvar_s* Dvar_FindVarByName(const char* dvarName);
uintptr_t Dvar_SetBoolByName(const char* dvarName, bool value);
uintptr_t Dvar_SetFloat_Internal(dvar_s* a1, float a2);
uintptr_t Dvar_SetInt_Internal(dvar_s* a1, unsigned int a2);
uintptr_t Dvar_SetBool_Internal(dvar_s* a1, bool a2);

inline const char* dvartype(const char* dvarname)
{
	dvar_s* varbyname = Dvar_FindVarByName(dvarname);
	if (varbyname)
	{
		switch (varbyname->type)
		{
		case DvarType::DVAR_TYPE_BOOL:
		{
			return "DVAR_TYPE_BOOL";
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT:
		{
			return "DVAR_TYPE_FLOAT";
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_2: //vec2
		{
			return "DVAR_TYPE_FLOAT_2";
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_3: //vec3
		{
			return "DVAR_TYPE_FLOAT_3";
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_4: //vec4
		{
			return "DVAR_TYPE_FLOAT_4";
			break;
		}
		case DvarType::DVAR_TYPE_INT:
		{
			return "DVAR_TYPE_INT";
			break;
		}
		case DvarType::DVAR_TYPE_INT64:
		{
			return "DVAR_TYPE_INT64";
			break;
		}
		case DvarType::DVAR_TYPE_UINT64:
		{
			return "DVAR_TYPE_UINT64";
			break;
		}
		case DvarType::DVAR_TYPE_ENUM:
		{
			return "DVAR_TYPE_ENUM";
			break;
		}
		case DvarType::DVAR_TYPE_STRING:
		{
			return "DVAR_TYPE_STRING";
			break;
		}
		case DvarType::DVAR_TYPE_COLOR:
		{
			return "DVAR_TYPE_COLOR";
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_3_COLOR:
		{
			return "DVAR_TYPE_FLOAT_3_COLOR";
			break;
		}
		//case DvarType::DVAR_TYPE_COUNT:
		//	return std::to_string(varbyname->current.);
		//	break;
		default:
			return "[NA]";
			break;
		}
	}
}

static uintptr_t AVAL = NULL;
[[nodiscard]] static BYTE* currentDvarVal(const char* cmnd, uintptr_t& addr = AVAL)
{
	//BYTE* buff = new BYTE[1024];
	//std::unique_ptr < BYTE[] > buff(new BYTE[256]);
	auto buff = std::make_unique<BYTE[]>(256);

	std::string result = "(null)";
	dvar_s* varbyname = Dvar_FindVarByName(cmnd);
	if (varbyname)
	{
		addr = (uintptr_t)varbyname;
		switch (varbyname->type)
		{
		case DvarType::DVAR_TYPE_BOOL:
		{

			result = std::to_string(varbyname->current.enabled);
			//strcpy(buff.get(), result.c_str());
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT:
		{
			result = std::to_string(varbyname->current.value);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}

		case DvarType::DVAR_TYPE_INT:
		{
			result = std::to_string(varbyname->current.integer);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_INT64:
		{
			result = std::to_string(varbyname->current.integer64);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_UINT64:
		{
			result = std::to_string(varbyname->current.unsignedInt64);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_ENUM:
		{
			result = std::to_string(varbyname->current.integer);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_STRING:
		{
			result = varbyname->current.string;
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_COLOR:
		{
			result =
				" r: " + std::to_string(varbyname->current.color[0]) +
				" g: " + std::to_string(varbyname->current.color[1]) +
				" b: " + std::to_string(varbyname->current.color[2]) +
				" a: " + std::to_string(varbyname->current.color[3]);

			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_3_COLOR:
		{
			result =
				" r: " + std::to_string(varbyname->current.color[0]) +
				" g: " + std::to_string(varbyname->current.color[1]) +
				" b: " + std::to_string(varbyname->current.color[2]);
			memcpy(buff.get(), (BYTE*)result.c_str() + '\0', result.size() + 1);
			return buff.get();
			break;
		}
		default:
			break;
		}
	}
	addr = NULL;
	//delete[] buff;
	return (BYTE*)result.c_str();
}

template<typename T> inline void dvar_set(const char* dvarName, T value)
{
	dvar_s* dvar = Dvar_FindVarByName(dvarName);
	if (dvar)
	{
		if (dvar->flags > 0)
		{
			dvar->flags = 0;
		}
		switch (dvar->type)
		{
		case DvarType::DVAR_TYPE_BOOL:
		{
			return Dvar_SetBoolByName(dvarName, value);
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT:
		{
			return Dvar_SetFloat_Internal(dvar, value);
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_2: //vec2
		{
			//Dvar_SetVec2_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_3: //vec3
		{
			//Dvar_SetVec3_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_4: //vec4
		{
			//Dvar_SetVec4_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_INT:
		{
			//Dvar_SetInt_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_INT64:
		{
			//Dvar_SetInt64_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_UINT64:
		{
			//Dvar_SetUInt64_Internal
			return;
			break;
		}
		case DvarType::DVAR_TYPE_ENUM:
		{
			return;
			break;
		}
		case DvarType::DVAR_TYPE_STRING:
		{
			return;
			break;
		}
		case DvarType::DVAR_TYPE_COLOR:
		{
			return;
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT_3_COLOR:
		{
			return;
			break;
		}
		//case DvarType::DVAR_TYPE_COUNT:
		//	return std::to_string(varbyname->current.);
		//	break;
		default:
			return;
			break;
		}
	}
}

inline void dvarFloat(const char* dvarname, float val)
{
	auto DVARFLT_cg_fovScale = Dvar_FindVarByName(dvarname);
	if (DVARFLT_cg_fovScale)
	{
		Dvar_SetFloat_Internal(DVARFLT_cg_fovScale, val);
	}
}

inline uint32_t dvarflag(const char* dvarname)
{
	auto DVARFLT_cg_fovScale = Dvar_FindVarByName(dvarname);
	if (DVARFLT_cg_fovScale)
	{
		return DVARFLT_cg_fovScale->flags;
	}
	return NULL;
}

static void dvar_setBool(const char* dvarname, bool val)
{
	dvar_s* tpv = Dvar_FindVarByName(dvarname);
	if (tpv)
	{
		if (tpv->flags > 0)
		{
			tpv->flags = 0;
		}
		Dvar_SetBoolByName(dvarname, val);
	}
}

template<typename T> inline void dvar_set2(const char* dvarName, T value)
{
	dvar_s* dvar = Dvar_FindVarByName(dvarName);
	if (dvar)
	{
		if (dvar->flags > 0)
		{
			dvar->flags = 0;
		}
		switch (dvar->type)
		{
		case DvarType::DVAR_TYPE_BOOL:
		{
			Dvar_SetBool_Internal(dvar, value);
			break;
		}
		case DvarType::DVAR_TYPE_FLOAT:
		{
			Dvar_SetFloat_Internal(dvar, value);
			break;
		}
		case DvarType::DVAR_TYPE_INT:
		{
			Dvar_SetInt_Internal(dvar, value);
			break;
		}
		case DvarType::DVAR_TYPE_STRING:
		{
			break;
		}
		default:
			break;
		}
	}
}

__int64 Com_DDL_LoadAsset(__int64 file);
__int64 DDL_GetRootState(__int64 state, __int64 file);
bool CL_PlayerData_GetDDLBuffer(__int64 context, int controllerindex, int stats_source, unsigned int statsgroup);
__int64 DDL_MoveToName(__int64 fstate, __int64 tstate, __int64 path);
char DDL_MoveToPath(__int64* fromState, __int64* toState, int depth, const char** path);
char DDL_SetInt(__int64 fstate, __int64 context, unsigned int value);
char DDL_SetString(__int64 state, __int64 ddlContext, const char* value);
bool DDL_Parse(const char* pStr, const char** navStrings2, const int navStringMax, int* navStringCount);
char DDL_SetEnum(__int64 fstate, __int64 context, const char* value);

void setCamo(int loadout, int weapon, int camoID);
void setName(int loadout, const char name[255]);
void setOperators(const char operators[255], int operatorid);
void setUnlock();

void CL_PlayerData_SetCustomClanTag(const char* clanTag);