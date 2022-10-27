#include "bone.h"

uintptr_t bone_dec(uintptr_t baseModuleAddr)
{


	if (g_vars->gcached.cached_bone_ptr != 0)
		return g_vars->gcached.cached_bone_ptr;

	uintptr_t returnstatus = 0;
	uintptr_t encrypted_address = 0;

	encrypted_address = *(uintptr_t*)(baseModuleAddr + g_vars->goffsets.bone_encrypted_ptr);

	if (encrypted_address)
	{
		DWORD64 peb = __readgsqword(0x60);
		/*auto r11 = peb;

		auto bone_case = r11;
		bone_case <<= 0x29;
		bone_case &= 0xf;*/
		auto bone_case = _rotr64(peb, 15) & 0xF;
		switch (bone_case)
		{
		case 0:
		{
			auto var_13 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_18 = encrypted_address;
			auto var_19 = (var_18) >> 0xe;
			auto var_20 = (encrypted_address) ^ (var_19);
			auto var_21 = var_20;
			auto var_22 = (var_21) >> 0x1c;
			auto var_23 = (var_20) ^ (var_22);
			auto var_30 = var_23;
			auto var_31 = (var_30) >> 0x38;
			auto var_32 = (var_23) ^ (var_31);
			auto var_44 = (var_32)+((baseModuleAddr + 0x271b) + (peb));
			auto var_45 = (var_44) >> 0x5;
			auto var_46 = ((var_32)+((baseModuleAddr + 0x271b) + (peb))) ^ (var_45);
			auto var_52 = var_46;
			auto var_53 = (var_52) >> 0xa;
			auto var_54 = (var_46) ^ (var_53);
			auto var_55 = var_54;
			auto var_56 = (var_55) >> 0x14;
			auto var_57 = (var_54) ^ (var_56);
			auto var_69 = var_57;
			auto var_70 = (var_69) >> 0x28;
			auto var_71 = (var_57) ^ (var_70);
			auto var_72 = (var_71) * (*reinterpret_cast<uint64_t*>(~(var_13)+0xb));
			auto var_78 = (var_72) ^ ((baseModuleAddr + 0x7cfa4c3b) + (peb));
			auto var_91 = (var_78) * (0xf8aa951bb0157dc5);
			auto var_97 = (var_91) * (0x91e80479ebd7ece3);
			returnstatus = (var_97)+(0x59d99dbec5bf7207);
			break;
		}
		case 1:
		{
			auto var_3 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_19 = (peb + 0x1) * (baseModuleAddr + 0x3468a21b);
			auto var_31 = ((encrypted_address)+((var_19)+(peb))) * (*reinterpret_cast<uint64_t*>(~(var_3)+0xb));
			auto var_37 = var_31;
			auto var_38 = (var_37) >> 0x13;
			auto var_39 = (var_31) ^ (var_38);
			auto var_47 = var_39;
			auto var_48 = (var_47) >> 0x26;
			auto var_49 = (var_39) ^ (var_48);
			auto var_60 = (((var_49)+(0x2a6fb164c7c7c37)) + (peb)) * (0x31786d5b514e2445);
			returnstatus = var_60;
			break;
		}
		case 2:
		{
			auto var_3 = 0x66f6a79ac477e83b;
			auto var_11 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_22 = (encrypted_address) ^ (peb);
			auto var_42 = ((var_22)+((0xd15efc7605043e35) - (baseModuleAddr))) + (0x3cecfca596c3eb4b);
			auto var_43 = (var_42) >> 0x13;
			auto var_44 = (((var_22)+((0xd15efc7605043e35) - (baseModuleAddr))) + (0x3cecfca596c3eb4b)) ^ (var_43);
			auto var_51 = var_44;
			auto var_52 = (var_51) >> 0x26;
			auto var_53 = (var_44) ^ (var_52);
			auto var_60 = (var_53) ^ (baseModuleAddr);
			auto var_66 = *reinterpret_cast<uint64_t*>(~(var_11)+0xb);
			auto var_67 = (var_66) * (var_3);
			auto var_68 = (var_60) * (var_67);
			returnstatus = var_68;
			break;
		}
		case 3:
		{
			auto var_9 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_14 = ((encrypted_address)+((~(baseModuleAddr + 0x6cfe)) - (peb))) * (0xf759b2c19a95153b);
			auto var_15 = (var_14) ^ (0x31a0ebeb025cf8b7);
			auto var_21 = (var_15)-(peb);
			auto var_22 = (var_21) >> 0x7;
			auto var_23 = ((var_15)-(peb)) ^ (var_22);
			auto var_24 = var_23;
			auto var_25 = (var_24) >> 0xe;
			auto var_26 = (var_23) ^ (var_25);
			auto var_32 = var_26;
			auto var_33 = (var_32) >> 0x1c;
			auto var_34 = (var_26) ^ (var_33);
			auto var_36 = var_34;
			auto var_37 = (var_36) >> 0x38;
			auto var_39 = peb;
			auto var_40 = (var_37) ^ (~(var_39));
			auto var_41 = (var_34) ^ (var_40);
			auto var_42 = (var_41) ^ (baseModuleAddr + 0xd3d7);
			auto var_52 = ((var_42)+(0xd11165ef37bdf356)) * (*reinterpret_cast<uint64_t*>(~(var_9)+0xb));
			returnstatus = var_52;
			break;
		}
		case 4:
		{
			auto var_12 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_18 = baseModuleAddr;
			auto var_24 = ((encrypted_address)+((var_18)-(peb))) * (0xf5d96e68528c29ad);
			auto var_36 = ((var_24)+(baseModuleAddr)) * (*reinterpret_cast<uint64_t*>(~(var_12)+0xb));
			auto var_39 = var_36;
			auto var_40 = (var_39) >> 0x2;
			auto var_41 = (var_36) ^ (var_40);
			auto var_51 = var_41;
			auto var_52 = (var_51) >> 0x4;
			auto var_53 = (var_41) ^ (var_52);
			auto var_61 = var_53;
			auto var_62 = (var_61) >> 0x8;
			auto var_63 = (var_53) ^ (var_62);
			auto var_67 = var_63;
			auto var_68 = (var_67) >> 0x10;
			auto var_69 = (var_63) ^ (var_68);
			auto var_76 = var_69;
			auto var_77 = (var_76) >> 0x20;
			auto var_78 = (var_77) ^ (peb);
			auto var_79 = (var_69) ^ (var_78);
			auto var_84 = var_79;
			auto var_85 = (var_84) >> 0xe;
			auto var_86 = (var_79) ^ (var_85);
			auto var_93 = var_86;
			auto var_94 = (var_93) >> 0x1c;
			auto var_95 = (var_86) ^ (var_94);
			auto var_96 = var_95;
			auto var_97 = (var_96) >> 0x38;
			auto var_98 = (var_95) ^ (var_97);
			returnstatus = var_98;
			break;
		}
		case 5:
		{
			auto var_3 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_7 = (encrypted_address) * (0xee2b65b6d956376b);
			auto var_14 = var_7;
			auto var_15 = (var_14) >> 0xf;
			auto var_16 = (var_7) ^ (var_15);
			auto var_22 = var_16;
			auto var_23 = (var_22) >> 0x1e;
			auto var_24 = (var_16) ^ (var_23);
			auto var_30 = var_24;
			auto var_31 = (var_30) >> 0x3c;
			auto var_32 = (var_24) ^ (var_31);
			auto var_37 = (var_32) ^ (baseModuleAddr);
			auto var_42 = (var_37) * (*reinterpret_cast<uint64_t*>(~(var_3)+0xb));
			auto var_48 = baseModuleAddr + 0x1d26;
			auto var_49 = (~(var_48)) * (peb);
			auto var_53 = (var_42)+(var_49);
			auto var_54 = (var_53) >> 0x14;
			auto var_55 = ((var_42)+(var_49)) ^ (var_54);
			auto var_58 = var_55;
			auto var_59 = (var_58) >> 0x28;
			auto var_60 = (var_55) ^ (var_59);
			auto var_61 = (var_60) ^ (0x758f25deba0696d5);
			returnstatus = var_61;
			break;
		}
		case 6:
		{
			auto var_12 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_18 = encrypted_address;
			auto var_19 = (var_18) >> 0x8;
			auto var_20 = (encrypted_address) ^ (var_19);
			auto var_25 = var_20;
			auto var_26 = (var_25) >> 0x10;
			auto var_27 = (var_20) ^ (var_26);
			auto var_34 = var_27;
			auto var_35 = (var_34) >> 0x20;
			auto var_36 = (var_27) ^ (var_35);
			auto var_45 = (var_36)+((baseModuleAddr + 0xb19) + (peb));
			auto var_46 = (var_45) >> 0x27;
			auto var_47 = ((var_36)+((baseModuleAddr + 0xb19) + (peb))) ^ (var_46);
			auto var_54 = var_47;
			auto var_55 = (var_54) >> 0x2;
			auto var_56 = (var_47) ^ (var_55);
			auto var_69 = var_56;
			auto var_70 = (var_69) >> 0x4;
			auto var_71 = (var_56) ^ (var_70);
			auto var_72 = var_71;
			auto var_73 = (var_72) >> 0x8;
			auto var_74 = (var_71) ^ (var_73);
			auto var_78 = var_74;
			auto var_79 = (var_78) >> 0x10;
			auto var_80 = (var_74) ^ (var_79);
			auto var_82 = var_80;
			auto var_83 = (var_82) >> 0x20;
			auto var_84 = (var_80) ^ (var_83);
			auto var_85 = (var_84) ^ (0xa0535006b5ed0bbe);
			auto var_90 = (var_85) * (0xeaf7c3724d67a01b);
			auto var_105 = ((var_90)+(peb)) * (*reinterpret_cast<uint64_t*>(~(var_12)+0xb));
			returnstatus = var_105;
			break;
		}
		case 7:
		{
			auto var_8 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_12 = (encrypted_address) ^ (0xbcbd5d2fdab9eb62);
			auto var_20 = var_12;
			auto var_21 = (var_20) >> 0x17;
			auto var_22 = (var_12) ^ (var_21);
			auto var_28 = var_22;
			auto var_29 = (var_28) >> 0x2e;
			auto var_30 = (var_22) ^ (var_29);
			auto var_36 = (peb) * (0xfffffffffffffffe);
			auto var_40 = ((var_30)+(var_36)) * (0x2b14aee821b6fcd3);
			auto var_48 = peb;
			auto var_49 = (var_40) * (*reinterpret_cast<uint64_t*>(~(var_8)+0xb));
			auto var_53 = ((var_49)+(baseModuleAddr + 0x52c63cf9)) + (~(var_48));
			auto var_54 = (var_53) >> 0x1e;
			auto var_55 = (((var_49)+(baseModuleAddr + 0x52c63cf9)) + (~(var_48))) ^ (var_54);
			auto var_66 = var_55;
			auto var_67 = (var_66) >> 0x3c;
			auto var_68 = (var_55) ^ (var_67);
			returnstatus = var_68;
			break;
		}
		case 8:
		{
			auto var_11 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_15 = baseModuleAddr + 0x530aef3d;
			auto var_16 = (~(var_15)) * (peb);
			auto var_22 = peb;
			auto var_23 = (var_22) * (baseModuleAddr + 0x25319751);
			auto var_24 = ((encrypted_address)+(var_16)) ^ (var_23);
			auto var_25 = (var_24) * (0x40bba076b7dc80cf);
			auto var_38 = var_25;
			auto var_39 = (var_38) >> 0xc;
			auto var_40 = (var_25) ^ (var_39);
			auto var_48 = var_40;
			auto var_49 = (var_48) >> 0x18;
			auto var_50 = (var_40) ^ (var_49);
			auto var_57 = var_50;
			auto var_58 = (var_57) >> 0x30;
			auto var_59 = (var_50) ^ (var_58);
			auto var_64 = (var_59) * (0xd5e6aa33709f91d5);
			auto var_70 = (var_64) ^ (0xda06d68ab046c062);
			auto var_79 = ((var_70)+(peb)) * (*reinterpret_cast<uint64_t*>(~(var_11)+0xb));
			returnstatus = var_79;
			break;
		}
		case 9:
		{
			auto var_14 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_22 = (encrypted_address) * (*reinterpret_cast<uint64_t*>(~(var_14)+0xb));
			auto var_28 = (var_22) * (0xf804974aef77395d);
			auto var_37 = ((var_28)-(baseModuleAddr)) ^ (0x1b6db8bf9ccc9d46);
			auto var_45 = var_37;
			auto var_46 = (var_45) >> 0x28;
			auto var_47 = (var_37) ^ (var_46);
			auto var_49 = var_47;
			auto var_50 = (var_49) >> 0x13;
			auto var_51 = (var_47) ^ (var_50);
			auto var_57 = var_51;
			auto var_58 = (var_57) >> 0x26;
			auto var_59 = (var_51) ^ (var_58);
			auto var_62 = var_59;
			auto var_63 = (var_62) >> 0x1e;
			auto var_64 = (var_59) ^ (var_63);
			auto var_65 = var_64;
			auto var_66 = (var_65) >> 0x3c;
			auto var_67 = (var_64) ^ (var_66);
			auto var_72 = (var_67) ^ (0xa7b8389482fd512d);
			returnstatus = var_72;
			break;
		}
		case 10:
		{
			auto var_13 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_18 = (encrypted_address) ^ (peb);
			auto var_27 = (var_18) * (*reinterpret_cast<uint64_t*>(~(var_13)+0xb));
			auto var_38 = (var_27)+(peb);
			auto var_39 = (var_38) >> 0x12;
			auto var_40 = ((var_27)+(peb)) ^ (var_39);
			auto var_44 = var_40;
			auto var_45 = (~(baseModuleAddr + 0xbb59)) * (peb);
			auto var_46 = (var_44) >> 0x24;
			auto var_47 = (var_45) ^ (var_46);
			auto var_48 = (var_40) ^ (var_47);
			auto var_49 = (var_48) * (0xc472df91229c7801);
			auto var_60 = (var_49) * (0x7592c013e421de8f);
			auto var_61 = (var_60) ^ (0x838cdebfec8ff17f);
			returnstatus = var_61;
			break;
		}
		case 11:
		{
			auto var_11 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_16 = encrypted_address;
			auto var_17 = (var_16) >> 0xd;
			auto var_18 = (encrypted_address) ^ (var_17);
			auto var_29 = var_18;
			auto var_30 = (var_29) >> 0x1a;
			auto var_31 = (var_18) ^ (var_30);
			auto var_38 = var_31;
			auto var_39 = (var_38) >> 0x34;
			auto var_40 = (var_31) ^ (var_39);
			auto var_47 = var_40;
			auto var_48 = (var_47) >> 0xe;
			auto var_49 = (var_40) ^ (var_48);
			auto var_55 = var_49;
			auto var_56 = (var_55) >> 0x1c;
			auto var_57 = (var_49) ^ (var_56);
			auto var_62 = var_57;
			auto var_63 = (var_62) >> 0x38;
			auto var_64 = (var_57) ^ (var_63);
			auto var_69 = peb;
			auto var_72 = (~(var_69)) * (~(baseModuleAddr + 0x356d));
			auto var_73 = (var_64) * (0x7166c733139dbbf);
			auto var_79 = ((var_73)+((peb)+((var_72) * 1))) * (*reinterpret_cast<uint64_t*>(~(var_11)+0xb));
			auto var_81 = var_79;
			auto var_82 = (var_81) >> 0x26;
			auto var_83 = (var_79) ^ (var_82);
			auto var_84 = (var_83) ^ (baseModuleAddr);
			returnstatus = var_84;
			break;
		}
		case 12:
		{
			auto var_11 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_19 = (encrypted_address) * (*reinterpret_cast<uint64_t*>(~(var_11)+0xb));
			auto var_29 = (var_19) ^ (peb);
			auto var_31 = (var_29) ^ (baseModuleAddr + 0x7881);
			auto var_36 = (var_31) ^ (peb);
			auto var_39 = (var_36) ^ (baseModuleAddr + 0x19e6);
			auto var_45 = var_39;
			auto var_46 = (var_45) >> 0xf;
			auto var_47 = (var_39) ^ (var_46);
			auto var_51 = var_47;
			auto var_52 = (var_51) >> 0x1e;
			auto var_53 = (var_47) ^ (var_52);
			auto var_54 = var_53;
			auto var_55 = (var_54) >> 0x3c;
			auto var_56 = (var_53) ^ (var_55);
			auto var_63 = var_56;
			auto var_64 = (var_63) >> 0x3;
			auto var_65 = (var_56) ^ (var_64);
			auto var_70 = var_65;
			auto var_71 = (var_70) >> 0x6;
			auto var_72 = (var_65) ^ (var_71);
			auto var_75 = var_72;
			auto var_76 = (var_75) >> 0xc;
			auto var_77 = (var_72) ^ (var_76);
			auto var_81 = var_77;
			auto var_82 = (var_81) >> 0x18;
			auto var_83 = (var_77) ^ (var_82);
			auto var_89 = var_83;
			auto var_90 = (var_89) >> 0x30;
			auto var_91 = (var_83) ^ (var_90);
			auto var_99 = (var_91) ^ (0x5120aafaed8f6a4e);
			auto var_106 = (var_99) * (0x1dcf9dbad1a848d5);
			auto var_111 = (var_106) * (0xf507a45a63dd4591);
			returnstatus = var_111;
			break;
		}
		case 13:
		{
			auto var_11 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_15 = encrypted_address;
			auto var_16 = (var_15) >> 0x14;
			auto var_17 = (encrypted_address) ^ (var_16);
			auto var_36 = var_17;
			auto var_37 = (var_36) >> 0x28;
			auto var_38 = (var_17) ^ (var_37);
			auto var_43 = (var_38) ^ (peb);
			auto var_47 = (var_43) ^ (baseModuleAddr + 0x43042a8a);
			auto var_52 = var_47;
			auto var_53 = (var_52) >> 0x20;
			auto var_54 = (var_47) ^ (var_53);
			auto var_62 = (var_54) * (*reinterpret_cast<uint64_t*>(~(var_11)+0xb));
			auto var_74 = (((var_62)+(0x24589be3be654ff7)) + (baseModuleAddr)) * (0xf56ab30a19191145);
			returnstatus = (var_74)-(0x2760b7321b39cdbe);
			break;
		}
		case 14:
		{
			auto var_9 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_17 = (encrypted_address) * (*reinterpret_cast<uint64_t*>(~(var_9)+0xb));
			auto var_18 = var_17;
			auto var_19 = (var_18) >> 0xc;
			auto var_20 = (var_17) ^ (var_19);
			auto var_21 = var_20;
			auto var_22 = (var_21) >> 0x18;
			auto var_23 = (var_20) ^ (var_22);
			auto var_31 = var_23;
			auto var_32 = (var_31) >> 0x30;
			auto var_33 = (var_23) ^ (var_32);
			auto var_34 = (var_33) * (0xee7e73092ce3db77);
			auto var_35 = (var_34) ^ (baseModuleAddr);
			auto var_36 = ((var_35)+(baseModuleAddr)) ^ (0x87d7533e59a5575e);
			auto var_40 = peb;
			auto var_41 = baseModuleAddr + 0xa71c;
			auto var_42 = (~(var_40)) * (~(var_41));
			returnstatus = ((var_36)+(0x937f0c2466dd5e6a)) + (var_42);
			break;
		}
		case 15:
		{
			auto var_2 = *reinterpret_cast<uint64_t*>(baseModuleAddr + 0x72c923e);
			auto var_21 = ((encrypted_address)+(baseModuleAddr)) * (0xd01a9607766e93c5);
			auto var_29 = ((var_21)+(baseModuleAddr)) * (*reinterpret_cast<uint64_t*>(~(var_2)+0xb));
			auto var_34 = peb;
			auto var_36 = peb;
			auto var_37 = (var_36) * (baseModuleAddr + 0x6af0);
			auto var_38 = (~(var_34)) * (baseModuleAddr + 0x5c327df6);
			auto var_43 = (var_29)+((var_38)-(var_37));
			auto var_44 = (var_43) >> 0x11;
			auto var_45 = ((var_29)+((var_38)-(var_37))) ^ (var_44);
			auto var_51 = var_45;
			auto var_52 = (var_51) >> 0x22;
			auto var_53 = (var_45) ^ (var_52);
			auto var_59 = var_53;
			auto var_60 = (var_59) >> 0x7;
			auto var_61 = (var_53) ^ (var_60);
			auto var_69 = var_61;
			auto var_70 = (var_69) >> 0xe;
			auto var_71 = (var_61) ^ (var_70);
			auto var_72 = var_71;
			auto var_73 = (var_72) >> 0x1c;
			auto var_74 = (var_71) ^ (var_73);
			auto var_78 = var_74;
			auto var_79 = (var_78) >> 0x38;
			auto var_80 = (var_74) ^ (var_79);
			returnstatus = var_80;
			break;
		}
		// End of switch
		}
		LOGS("Bone Case: %s", std::to_string(bone_case));
		g_vars->gcached.cached_bone_ptr = returnstatus;
		LOGS_ADDR(g_vars->gcached.cached_bone_ptr);
		return g_vars->gcached.cached_bone_ptr;
	}
	return 0;
}

uintptr_t bone_index_dec(uint32_t client_id)
{
	auto baseModuleAddr = g_vars->baseModule;
	uintptr_t returnstatus = 0;

	auto var_1 = (client_id) * (0x13c8);
	uint64_t var_2;
	uint64_t var_3 = _umul128(0x9754dd877b4a13bb, var_1, (DWORD64*)&var_2);
	auto var_4 = (var_2) >> 0xc;
	auto var_5 = (var_4) * (0x1b11);
	auto var_6 = ((var_1)-(var_5)) * (0x1b11);
	uint64_t var_7;
	uint64_t var_8 = _umul128(0x78f2c55adae3b96b, var_6, (DWORD64*)&var_7);
	auto var_9 = var_6;
	auto var_10 = ((var_9)-(var_7)) >> 0x1;
	auto var_11 = ((var_10)+(var_7)) >> 0xd;
	auto var_12 = (var_11) * (0x2b77);
	uint64_t var_13;
	uint64_t var_14 = _umul128(0x2e8ba2e8ba2e8ba3, (var_6)-(var_12), (DWORD64*)&var_13);
	auto var_15 = (var_13) >> 0x2;
	auto var_16 = (var_15) * (0x16);
	uint64_t var_17;
	uint64_t var_18 = _umul128(0x276e982ed354b79b, (var_6)-(var_12), (DWORD64*)&var_17);
	auto var_19 = (var_17) >> 0x7;
	auto var_20 = ((var_16)+(var_19)) * (0x67e);
	auto var_21 = ((var_6)-(var_12)) * (0x680);
	auto var_22 = *reinterpret_cast<uint16_t*>(((var_21)-(var_20)) + 0x72ddec0 + ((baseModuleAddr) * 1));
	auto var_23 = (var_22) * (0x13c8);
	auto var_24 = 0xc388d5333baa90cd;
	uint64_t var_25;
	uint64_t var_26 = _umul128(var_24, var_23, (DWORD64*)&var_25);
	auto var_27 = var_23;
	auto var_28 = 0xc388d5333baa90cd;
	auto var_29 = ((var_27)-(var_25)) >> 0x1;
	auto var_30 = ((var_29)+(var_25)) >> 0xd;
	auto var_31 = (var_30) * (0x2449);
	auto var_32 = ((var_23)-(var_31)) * (0x324a);
	uint64_t var_33;
	uint64_t var_34 = _umul128(var_28, var_32, (DWORD64*)&var_33);
	auto var_35 = var_32;
	auto var_36 = ((var_35)-(var_33)) >> 0x1;
	auto var_37 = ((var_36)+(var_33)) >> 0xd;
	auto var_38 = (var_37) * (0x2449);
	uint64_t var_39;
	uint64_t var_40 = _umul128(0xaaaaaaaaaaaaaaab, (var_32)-(var_38), (DWORD64*)&var_39);
	auto var_41 = (var_39) >> 0x2;
	uint64_t var_42;
	uint64_t var_43 = _umul128(0xb67ced0541d95407, (var_32)-(var_38), (DWORD64*)&var_42);
	auto var_44 = (var_42) >> 0xb;
	auto var_45 = ((var_44)+(((var_41)+((var_41) * 2)) * 2)) * (0x1672);
	auto var_46 = ((var_32)-(var_38)) * (0x1674);
	auto var_47 = *reinterpret_cast<uint16_t*>(((var_46)-(var_45)) + 0x72e6da0 + ((baseModuleAddr) * 1));
	returnstatus = var_47;

	return returnstatus;
}