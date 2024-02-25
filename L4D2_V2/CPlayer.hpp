#pragma once

#include <Windows.h>

//TODO: Переместить его куда-то.
class Vector3
{
	float x, y, z;
};

class CPlayer
{
public:
	char pad_0000[148]; //0x0000
	Vector3 pos; //0x0094
	char pad_00A0[76]; //0x00A0
	int32_t iHealth; //0x00EC
	char pad_00F0[2048]; //0x00F0
	int32_t iWeaponId; //0x08F0
	char pad_08F4[1876]; //0x08F4
};