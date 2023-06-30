/**********************************************************************************************************
    ELEX-ELEX2-Geting-All-In-Game-Items Version 1.2. A program for geting all inventory items of
    the game ELEX 1 and 2. Used to enumerate all in-game inventory items and replace the old
    inventory item with the new item received.

    Copyright (C) 2023  Maxim Shershavikov
    This file is part of ELEX-ELEX2-Geting-All-In-Game-Items.

    ELEX-ELEX2-Geting-All-In-Game-Items is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by the Free Software Foundation,
    either version 3 of the License, or (at your option) any later version.

    ELEX-ELEX2-Geting-All-In-Game-Items is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program.
    If not, see <https://www.gnu.org/licenses/>. Email m.shershavikov@yandex.ru

    To read a copy of the GNU General Public License in a file COPYING.txt, to do this, enter 3 at
    the beginning of the program.
**********************************************************************************************************/

#pragma once

#include <iostream>
#include <Windows.h>
#include <memoryapi.h>
#include <psapi.h>
#include <vector>
#include <set>
#include <string>
#include <format>

using namespace std;

#define ELEX1_STRUCT_GET_INVENTAR_HEAD 0x0140c14728L
#define ELEX2_STRUCT_GET_INVENTAR_HEAD 0x0141123230L

#define ELEX_1_2_PAGE_SIZE_INVENTAR_PTR 0x6001000L

#define OFFSET_ELEX1 0x148000 
#define OFFSET_ELEX2 0x0 

#define BYTE_FF_4 0xffffffff

#define BLOCK2_LL2 0
#define BLOCK2_LL3 1

#define NUMBER_OF_ITEMS_ELEX2 1360
#define NUMBER_OF_ITEMS_ELEX1 1629

#define ELEX2_BLOCK1_HEAD 0x0140f989c0L
#define ELEX1_BLOCK1_HEAD 0x0140b2a068L
#define ELEX2_BLOCK2_HEAD 0x01410a8920L
#define ELEX1_BLOCK2_HEAD 0x0140bd1158L

#define INVENTAR_ITEMS_HEAD_ELEX2 0x01410b2300L
#define INVENTAR_ITEMS_HEAD_ELEX1 0x0140bd85c8L

struct Ids {
    LONGLONG Addr;
    DWORD ll2;
    DWORD ll3;
    DWORD Signature1;
    DWORD Signature2;
    DWORD Signature3;
    DWORD Signature4;
    LONGLONG ll6;
};

struct Get_inventar {
    LONGLONG Head;
    LONGLONG PtrInventar;
};

struct Inventar_items_elex2 {
    LONGLONG Head;
    LONGLONG ChangeAddres;
    LONGLONG ll3;
    LONGLONG ll4;
    LONGLONG ll5;
    LONGLONG FFFFFFFF;
    LONGLONG ll7;
    DWORD dw8;
    DWORD nums;
    LONGLONG StartPtr;
};

struct Inventar_items_elex1 {
    LONGLONG Head;
    LONGLONG ChangeAddres;
    LONGLONG ll3;
    LONGLONG addr;
    LONGLONG ll5;
    LONGLONG ll6;
    LONGLONG FFFFFFFF;
    LONGLONG ll8;
    DWORD dw9;
    DWORD nums;
    LONGLONG StartPtr;
};

struct Block_1 {
    LONGLONG Head;
    LONGLONG ll2;
    LONGLONG ll3;
    LONGLONG WeUsePtr;
    LONGLONG ll5;
    LONGLONG ToControllPtr;
    LONGLONG ll7;
    LONGLONG ll8;
    LONGLONG ll9;
    LONGLONG ll10;
    LONGLONG ll11;
    LONGLONG ll12;
    LONGLONG ll13;
    LONGLONG ll14;
    LONGLONG ll15;
    LONGLONG ll16;
    LONGLONG ll17;
    LONGLONG ll18;
    LONGLONG ll19;
    LONGLONG ll20;
};

struct Block_2 {
    LONGLONG Head;
    LONGLONG ll2;
    LONGLONG ll3;
};

set<long long> size_page_elex2 = { 0xf000, 0xff000, 0x9b000, 0x10d000, 0x113000, 0x108000, 0x1ff000, 0xf7000, 0xd4000, 0xe9000, 0xcb000, 0xa8000, 0xd9000, 0x69000, 0x41000, 0x42000, 0xcc000, 0xac000, 0x64000, 0x119000, 0x86000, 0x4d000, 0xc3000, 0x6e000, 0x41000 };
set<long long> size_page_elex1 = { 0xf000, 0xff000, 0x1ff000, 0x109000, 0x44000, 0x18a000, 0x142000, 0x3ff000, 0x41000, 0x133000 };
