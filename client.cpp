#include "client.h"

uintptr_t clientinfo_dec()
{
	auto peb = __readgsqword(0x60);
	auto baseModuleAddr = g_vars->baseModule;
	uintptr_t returnstatus = 0;

	if (g_vars->gcached.cached_character_ptr != 0)
		return g_vars->gcached.cached_character_ptr;

	uintptr_t encrypted_address = *(uintptr_t*)(baseModuleAddr + g_vars->goffsets.client_encrypted_ptr);

	if (encrypted_address)
	{
		auto var_3 = encrypted_address;
		auto var_4 = (var_3) >> 0x1d;
		auto var_5 = (encrypted_address) ^ (var_4);
		auto var_6 = var_5;
		auto var_7 = (var_6) >> 0x3a;
		auto var_8 = (var_5) ^ (var_7);
		auto var_9 = (~(baseModuleAddr + 0x3696d69b)) ^ (~peb);
		auto var_10 = (~(~peb)) * (~(baseModuleAddr + 0x5912b8fa));
		auto var_11 = ((var_8)-(var_9)) ^ (var_10);
		auto var_12 = (var_11) * (*reinterpret_cast<uint64_t*>(~(*reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c90d6)) + 0xb));
		auto var_13 = (var_12) * (0x72438001511af22f);
		returnstatus = (var_13)+(0x7c1266d8dea86835);
		
		g_vars->gcached.cached_character_ptr = returnstatus;
		LOGS_ADDR(g_vars->gcached.cached_character_ptr);
		return  g_vars->gcached.cached_character_ptr;
	}
	return 0;
}

uint64_t client_base_dec()
{
	auto peb = __readgsqword(0x60);
	auto baseModuleAddr = g_vars->baseModule;
	uintptr_t returnstatus = 0;

	if (g_vars->gcached.cached_base_ptr != 0)
		return g_vars->gcached.cached_base_ptr;

	uintptr_t encrypted_address = *(uintptr_t*)(clientinfo_dec() + g_vars->goffsets.client_base);
	if (encrypted_address)
	{

		auto client_case = _rotr64(peb, 17) & 0xF; //peb >> 0x13 & 0xF;
		switch (client_case)
		{
		case 0:
		{
			auto var_7 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_19 = peb;
			auto var_20 = (~(var_19)) * (baseModuleAddr + 0xae1e);
			auto var_34 = ((encrypted_address)+(var_20)) * (*reinterpret_cast<uint64_t*>(~(var_7)+0xb));
			auto var_39 = (var_34) * (0x8444575bc128764d);
			auto var_46 = peb;
			auto var_47 = (var_46) ^ (baseModuleAddr + 0x6e08);
			auto var_48 = ((var_39)+(var_47)) ^ (baseModuleAddr);
			auto var_53 = (~(baseModuleAddr + 0x370fcfbf)) * (peb);
			auto var_54 = (var_48) ^ (var_53);
			auto var_55 = var_54;
			auto var_56 = (var_55) >> 0x25;
			auto var_57 = (var_54) ^ (var_56);
			auto var_58 = (var_57) ^ (0x51517f59b44e05a7);
			returnstatus = var_58;
			break;
		}
		case 1:
		{
			auto var_7 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_11 = (encrypted_address)+(peb);
			auto var_12 = (var_11) >> 0x5;
			auto var_13 = ((encrypted_address)+(peb)) ^ (var_12);
			auto var_21 = var_13;
			auto var_22 = (var_21) >> 0xa;
			auto var_23 = (var_13) ^ (var_22);
			auto var_24 = var_23;
			auto var_25 = (var_24) >> 0x14;
			auto var_26 = (var_23) ^ (var_25);
			auto var_30 = var_26;
			auto var_31 = (var_30) >> 0x28;
			auto var_32 = (var_26) ^ (var_31);
			auto var_33 = var_32;
			auto var_34 = (var_33) >> 0x18;
			auto var_35 = (var_32) ^ (var_34);
			auto var_42 = var_35;
			auto var_43 = (var_42) >> 0x30;
			auto var_44 = (var_35) ^ (var_43);
			auto var_51 = ((var_44)+(0x2b947af18bdf7649)) * (*reinterpret_cast<uint64_t*>(~(var_7)+0xb));
			auto var_65 = ((var_51)-(baseModuleAddr)) ^ (0x424cc33a62b6b112);
			auto var_71 = (var_65) * (0x714666bfa2f59e99);
			returnstatus = var_71;
			break;
		}
		case 2:
		{
			auto var_2 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_15 = encrypted_address;
			auto var_16 = (var_15) >> 0x21;
			auto var_17 = (encrypted_address) ^ (var_16);
			auto var_21 = var_17;
			auto var_22 = (var_21) >> 0x19;
			auto var_23 = (var_17) ^ (var_22);
			auto var_25 = var_23;
			auto var_26 = (var_25) >> 0x32;
			auto var_27 = (var_23) ^ (var_26);
			auto var_40 = (((var_27)-(0x5be22a817f8f69be)) - (baseModuleAddr)) * (0x8b0dc71680cada95);
			auto var_45 = ((var_40)+(0x52a7ade368fde6d6)) ^ ((baseModuleAddr + 0x3f4d1f22) + (peb));
			auto var_55 = (var_45) * (*reinterpret_cast<uint64_t*>(~(var_2)+0xb));
			returnstatus = var_55;
			break;
		}
		case 3:
		{
			auto var_2 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_16 = peb;
			auto var_18 = (~(var_16)) * (baseModuleAddr + 0x3a96530a);
			auto var_19 = (var_18) ^ (encrypted_address);
			auto var_20 = peb;
			auto var_21 = (var_20) * (baseModuleAddr + 0xf27b);
			auto var_22 = ((var_21)+(var_19)) ^ (0x9408f416edf74072);
			auto var_30 = var_22;
			auto var_31 = (var_30) >> 0x3;
			auto var_32 = (var_22) ^ (var_31);
			auto var_42 = var_32;
			auto var_43 = (var_42) >> 0x6;
			auto var_44 = (var_32) ^ (var_43);
			auto var_51 = var_44;
			auto var_52 = (var_51) >> 0xc;
			auto var_53 = (var_44) ^ (var_52);
			auto var_61 = var_53;
			auto var_62 = (var_61) >> 0x18;
			auto var_63 = (var_53) ^ (var_62);
			auto var_64 = var_63;
			auto var_65 = (var_64) >> 0x30;
			auto var_66 = (var_63) ^ (var_65);
			auto var_67 = (var_66) * (*reinterpret_cast<uint64_t*>(~(var_2)+0xb));
			auto var_71 = (var_67) * (0x2e81c52395c11091);
			auto var_77 = var_71;
			auto var_78 = (var_77) >> 0x1d;
			auto var_79 = (var_71) ^ (var_78);
			auto var_82 = var_79;
			auto var_83 = (var_82) >> 0x3a;
			auto var_84 = (var_79) ^ (var_83);
			returnstatus = (var_84)+(peb);
			break;
		}
		case 4:
		{
			auto var_2 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_3 = baseModuleAddr + 0x1ab5;
			auto var_16 = (encrypted_address) ^ ((baseModuleAddr + 0x270bb714) + (peb));
			auto var_30 = peb;
			auto var_31 = (var_30) ^ (baseModuleAddr + 0xb637);
			auto var_36 = (var_16)+(var_31);
			auto var_37 = (var_36) >> 0xc;
			auto var_38 = ((var_16)+(var_31)) ^ (var_37);
			auto var_43 = var_38;
			auto var_44 = (var_43) >> 0x18;
			auto var_45 = (var_38) ^ (var_44);
			auto var_55 = var_45;
			auto var_56 = (var_55) >> 0x30;
			auto var_57 = (var_45) ^ (var_56);
			auto var_62 = (var_57) * (0x6d70eb890b3ad22f);
			auto var_67 = peb;
			auto var_68 = (var_67) * (var_3);
			auto var_71 = ((var_62)-(0x4963dd1458c0ded6)) ^ (var_68);
			auto var_72 = (var_71) * (*reinterpret_cast<uint64_t*>(~(var_2)+0xb));
			auto var_73 = (var_72) * (0x96377d124189254f);
			returnstatus = var_73;
			break;
		}
		case 5:
		{
			auto var_2 = 0xfe20e8d317156ae5;
			auto var_10 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_20 = peb;
			auto var_23 = (encrypted_address)+(((~(var_20)) - (baseModuleAddr)) + (0xffffffff8e99aafb));
			auto var_24 = (var_23) >> 0xe;
			auto var_25 = ((encrypted_address)+(((~(var_20)) - (baseModuleAddr)) + (0xffffffff8e99aafb))) ^ (var_24);
			auto var_26 = var_25;
			auto var_27 = (var_26) >> 0x1c;
			auto var_28 = (var_25) ^ (var_27);
			auto var_32 = var_28;
			auto var_33 = (var_32) >> 0x38;
			auto var_34 = (var_28) ^ (var_33);
			auto var_49 = *reinterpret_cast<uint64_t*>(~(var_10)+0xb);
			auto var_50 = (var_49) * (var_2);
			auto var_51 = (((var_34)+(peb)) - (baseModuleAddr)) * (var_50);
			auto var_61 = (var_51) * (0x358eb949ec533047);
			auto var_66 = (var_61) * (0xef4fef1d6987626b);
			returnstatus = var_66;
			break;
		}
		case 6:
		{
			auto var_9 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_19 = encrypted_address;
			auto var_20 = (var_19) >> 0x8;
			auto var_21 = (encrypted_address) ^ (var_20);
			auto var_28 = var_21;
			auto var_29 = (var_28) >> 0x10;
			auto var_30 = (var_21) ^ (var_29);
			auto var_35 = var_30;
			auto var_36 = (var_35) >> 0x20;
			auto var_37 = (var_30) ^ (var_36);
			auto var_46 = (var_37) * (*reinterpret_cast<uint64_t*>(~(var_9)+0xb));
			auto var_52 = (var_46) * (0x11317082766d195);
			auto var_58 = peb;
			auto var_59 = (var_52) ^ (((~(var_58)) - (baseModuleAddr)) - (0x54ca));
			auto var_69 = (var_59)-(0x354779e1cccd2384);
			auto var_70 = (var_69) >> 0x10;
			auto var_71 = ((var_59)-(0x354779e1cccd2384)) ^ (var_70);
			auto var_75 = var_71;
			auto var_76 = (var_75) >> 0x20;
			auto var_77 = ((baseModuleAddr + 0xea8e) + (peb)) ^ (var_76);
			auto var_78 = (var_71) ^ (var_77);
			auto var_79 = (var_78) ^ (0xd49c71ae1132826c);
			returnstatus = var_79;
			break;
		}
		case 7:
		{
			auto var_9 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_15 = encrypted_address;
			auto var_16 = (var_15) >> 0x20;
			auto var_17 = (encrypted_address) ^ (var_16);
			auto var_23 = (var_17) * (*reinterpret_cast<uint64_t*>(~(var_9)+0xb));
			auto var_31 = (var_23) ^ (peb);
			auto var_36 = baseModuleAddr;
			auto var_37 = (var_31)+((var_36)-(peb));
			auto var_38 = (var_37) >> 0x1f;
			auto var_39 = ((var_31)+((var_36)-(peb))) ^ (var_38);
			auto var_40 = var_39;
			auto var_41 = (var_40) >> 0x3e;
			auto var_42 = (var_39) ^ (var_41);
			auto var_49 = (var_42) * (0xf561a788c94087e3);
			auto var_59 = (var_49) * (0x59a390fff277f733);
			returnstatus = var_59;
			break;
		}
		case 8:
		{
			auto var_2 = baseModuleAddr + 0xed89;
			auto var_3 = 0xf06c404b8b9c14fb;
			auto var_11 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_17 = peb;
			auto var_18 = (var_17) * (var_2);
			auto var_23 = peb;
			auto var_24 = (~(var_23)) * (baseModuleAddr + 0x5c28917a);
			auto var_25 = ((encrypted_address)-(var_18)) ^ (var_24);
			auto var_33 = var_25;
			auto var_34 = (var_33) >> 0x18;
			auto var_35 = (var_25) ^ (var_34);
			auto var_41 = var_35;
			auto var_42 = (var_41) >> 0x30;
			auto var_43 = (var_35) ^ (var_42);
			auto var_47 = var_43;
			auto var_48 = (var_47) >> 0x22;
			auto var_49 = (var_43) ^ (var_48);
			auto var_57 = *reinterpret_cast<uint64_t*>(~(var_11)+0xb);
			auto var_58 = (var_57) * (var_3);
			auto var_59 = (var_49) * (var_58);
			auto var_68 = (var_59) ^ (baseModuleAddr);
			auto var_72 = var_68;
			auto var_73 = (var_72) >> 0x17;
			auto var_74 = (var_68) ^ (var_73);
			auto var_75 = var_74;
			auto var_76 = (var_75) >> 0x2e;
			auto var_77 = (var_74) ^ (var_76);
			returnstatus = var_77;
			break;
		}
		case 9:
		{
			auto var_10 = 0xf3519cfd2988b33f;
			auto var_11 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_19 = *reinterpret_cast<uint64_t*>(~(var_11)+0xb);
			auto var_20 = (var_19) * (var_10);
			auto var_21 = (encrypted_address) * (var_20);
			auto var_25 = var_21;
			auto var_26 = (var_25) >> 0x1d;
			auto var_27 = (var_21) ^ (var_26);
			auto var_31 = var_27;
			auto var_32 = (var_31) >> 0x3a;
			auto var_33 = (var_27) ^ (var_32);
			auto var_38 = peb;
			auto var_39 = (var_38) ^ (baseModuleAddr + 0xf753);
			auto var_55 = (((var_33)-(var_39)) + (baseModuleAddr)) ^ (peb);
			auto var_63 = var_55;
			auto var_64 = (var_63) >> 0x23;
			auto var_65 = (var_55) ^ (var_64);
			returnstatus = var_65;
			break;
		}
		case 10:
		{
			auto var_9 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_16 = (encrypted_address) * (*reinterpret_cast<uint64_t*>(~(var_9)+0xb));
			auto var_22 = (var_16) ^ (baseModuleAddr);
			auto var_28 = (var_22) * (0x4ad6ea14a066c191);
			auto var_36 = (var_28) ^ (0xdc65390d47d056a0);
			auto var_42 = (var_36) ^ (0xb8da137814c9d3ae);
			auto var_52 = var_42;
			auto var_53 = (var_52) >> 0x26;
			auto var_54 = (var_42) ^ (var_53);
			auto var_55 = peb;
			auto var_56 = (~(baseModuleAddr + 0x5bf832a4)) * (~(var_55));
			auto var_58 = ((var_54)+(var_56)) ^ (baseModuleAddr + 0x4a1e);
			auto var_59 = (var_58) ^ (~(var_55));
			returnstatus = var_59;
			break;
		}
		case 11:
		{
			auto var_3 = 0x3faa3806c032fd77;
			auto var_11 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_22 = ((encrypted_address)-(peb)) ^ (peb);
			auto var_26 = var_22;
			auto var_27 = (var_26) >> 0x3;
			auto var_28 = (var_22) ^ (var_27);
			auto var_36 = var_28;
			auto var_37 = (var_36) >> 0x6;
			auto var_38 = (var_28) ^ (var_37);
			auto var_43 = var_38;
			auto var_44 = (var_43) >> 0xc;
			auto var_45 = (var_38) ^ (var_44);
			auto var_46 = var_45;
			auto var_47 = (var_46) >> 0x18;
			auto var_48 = (var_45) ^ (var_47);
			auto var_49 = var_48;
			auto var_50 = (var_49) >> 0x30;
			auto var_51 = (var_48) ^ (var_50);
			auto var_58 = var_51;
			auto var_59 = (var_58) >> 0x1;
			auto var_60 = (var_51) ^ (var_59);
			auto var_64 = var_60;
			auto var_65 = (var_64) >> 0x2;
			auto var_66 = (var_60) ^ (var_65);
			auto var_68 = var_66;
			auto var_69 = (var_68) >> 0x4;
			auto var_70 = (var_66) ^ (var_69);
			auto var_71 = var_70;
			auto var_72 = (var_71) >> 0x8;
			auto var_73 = (var_70) ^ (var_72);
			auto var_78 = var_73;
			auto var_79 = (var_78) >> 0x10;
			auto var_80 = (var_73) ^ (var_79);
			auto var_87 = var_80;
			auto var_88 = (var_87) >> 0x20;
			auto var_89 = (var_80) ^ (var_88);
			auto var_101 = *reinterpret_cast<uint64_t*>(~(var_11)+0xb);
			auto var_102 = (var_101) * (var_3);
			auto var_103 = ((var_89)-(0x7bab80f552bd5ec8)) * (var_102);
			returnstatus = var_103;
			break;
		}
		case 12:
		{
			auto var_2 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_16 = (encrypted_address) * (0xbb19470d6ae7a731);
			auto var_27 = (var_16) ^ (baseModuleAddr);
			auto var_34 = (~(baseModuleAddr + 0x587b)) ^ (peb);
			auto var_43 = (((var_27)-(baseModuleAddr)) - (0x3f665698940e2966)) - (var_34);
			auto var_44 = (var_43) >> 0x26;
			auto var_45 = ((((var_27)-(baseModuleAddr)) - (0x3f665698940e2966)) - (var_34)) ^ (var_44);
			auto var_52 = ((var_45)+(0xeaaac30d57277d71)) * (*reinterpret_cast<uint64_t*>(~(var_2)+0xb));
			returnstatus = var_52;
			break;
		}
		case 13:
		{
			auto var_2 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_4 = 0x19581117c77620a1;
			auto var_16 = (encrypted_address) * (*reinterpret_cast<uint64_t*>(~(var_2)+0xb));
			auto var_23 = peb;
			auto var_30 = ((var_16)+(baseModuleAddr + 0x71ad)) + (~(var_23));
			auto var_31 = (var_30) >> 0x19;
			auto var_32 = (((var_16)+(baseModuleAddr + 0x71ad)) + (~(var_23))) ^ (var_31);
			auto var_45 = var_32;
			auto var_46 = (var_45) >> 0x32;
			auto var_47 = (var_32) ^ (var_46);
			auto var_51 = ((var_47)-(0x3a488310d595e9e7)) ^ (0xf673c04080d067e4);
			auto var_58 = (var_51) * (var_4);
			auto var_61 = peb;
			auto var_62 = (var_61) ^ (baseModuleAddr + 0x8425);
			returnstatus = ((var_58)-(var_62)) + (baseModuleAddr);
			break;
		}
		case 14:
		{
			auto var_2 = baseModuleAddr + 0x40f9;
			auto var_3 = 0x26fb0319beb1739b;
			auto var_13 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_18 = peb;
			auto var_20 = (var_18) * (baseModuleAddr + 0x2258a697);
			auto var_21 = (var_20) ^ ((baseModuleAddr + 0x1a5aa98b) + (peb));
			auto var_22 = (encrypted_address) ^ (var_21);
			auto var_23 = var_22;
			auto var_24 = (var_23) >> 0x1c;
			auto var_25 = (var_22) ^ (var_24);
			auto var_26 = var_25;
			auto var_27 = (var_26) >> 0x38;
			auto var_28 = (var_25) ^ (var_27);
			auto var_32 = (var_28) * (var_3);
			auto var_35 = peb;
			auto var_36 = (var_35) ^ (var_2);
			auto var_44 = ((var_32)-(var_36)) * (*reinterpret_cast<uint64_t*>(~(var_13)+0xb));
			auto var_49 = (var_44) ^ (0xcc24f156f668ecb0);
			auto var_60 = (var_49) ^ (0x6bcea51362df5161);
			returnstatus = var_60;
			break;
		}
		case 15:
		{
			auto var_7 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c9125);
			auto var_18 = ((encrypted_address)+((baseModuleAddr + 0x2ce4bf2c) + (peb))) * (0xbfffb9ef3d554ae3);
			auto var_24 = peb;
			auto var_25 = (var_24) ^ (baseModuleAddr + 0x21a1);
			auto var_33 = ((var_18)-(var_25)) ^ (baseModuleAddr);
			auto var_39 = (var_33) * (*reinterpret_cast<uint64_t*>(~(var_7)+0xb));
			auto var_52 = (var_39)+((baseModuleAddr + 0x613356b8) + (peb));
			auto var_53 = (var_52) >> 0x21;
			auto var_54 = ((var_39)+((baseModuleAddr + 0x613356b8) + (peb))) ^ (var_53);
			auto var_55 = var_54;
			auto var_56 = (var_55) >> 0x26;
			auto var_57 = (var_54) ^ (var_56);
			returnstatus = var_57;
			break;
		}
		//
		}
		LOGS("ClientBase Case: %s", std::to_string(client_case));
		g_vars->gcached.cached_base_ptr = returnstatus;
		LOGS_ADDR(g_vars->gcached.cached_base_ptr);

		return g_vars->gcached.cached_base_ptr;
	}
	return 0;
}