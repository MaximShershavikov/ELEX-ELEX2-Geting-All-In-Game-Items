/**********************************************************************************************************
    ELEX-ELEX2-Geting-All-In-Game-Items Version 1.0. A program for geting all inventory items of
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

#include "data_base_name_items.h"
#include "elex_items_main.h"

LONGLONG FindInventar(HANDLE hHandl, PROCESS_MEMORY_COUNTERS ppsmemCounters, LONGLONG StructGetInvetarHead, LONGLONG offset) {
    SIZE_T *lpNumOfBytes = new SIZE_T;
    Get_inventar* GetInv = new Get_inventar;
    LONGLONG next = NULL, StartAddress = NULL, EndAddress;
    MEMORY_BASIC_INFORMATION lpBuffer;
    while (next < ppsmemCounters.PeakPagefileUsage) {
        VirtualQueryEx(hHandl, (LPCVOID)next, &lpBuffer, sizeof(MEMORY_BASIC_INFORMATION));
        if (lpBuffer.RegionSize == ELEX_1_2_PAGE_SIZE_INVENTAR_PTR && lpBuffer.State == MEM_COMMIT && lpBuffer.Type == MEM_PRIVATE && lpBuffer.Protect == PAGE_READWRITE) {
            EndAddress = next + lpBuffer.RegionSize;
            StartAddress = next + offset;
            for (StartAddress; StartAddress < EndAddress; StartAddress++) {
                ReadProcessMemory(hHandl, (LPCVOID)StartAddress, GetInv, sizeof(Get_inventar), lpNumOfBytes);
                if (GetInv->Head == StructGetInvetarHead && GetInv->PtrInventar != NULL)
                    return GetInv->PtrInventar;
            }
        }
        next += lpBuffer.RegionSize;
    }
    return -1;
}

vector<Inventar_items_elex2> FindItemsInInventarElex2(HANDLE hHandl, LONGLONG addrInv, LONGLONG Block1_Head, LONGLONG Block2_Head) {
    SIZE_T *lpNumOfBytes = new SIZE_T;
    LONGLONG *addr_next = new LONGLONG;
    Block_1 *block_1 = new Block_1;
    Block_2 *block_2 = new Block_2;
    Inventar_items_elex2 *InventarItems = new Inventar_items_elex2;
    vector<Inventar_items_elex2> addr;
    int count = 0;
    do {
        ReadProcessMemory(hHandl, (LPCVOID)addrInv, InventarItems, sizeof(Inventar_items_elex2), lpNumOfBytes);
        if (InventarItems->Head == INVENTAR_ITEMS_HEAD_ELEX2 &&
        InventarItems->ChangeAddres != NULL &&
        InventarItems->ll3 == NULL &&
        InventarItems->ll4 == NULL &&
        InventarItems->ll5 == NULL &&
        InventarItems->FFFFFFFF == BYTE_FF_4 &&
        InventarItems->ll7 == NULL &&
        InventarItems->dw8 >= NULL &&
        InventarItems->nums != NULL) {
            ReadProcessMemory(hHandl, (LPCVOID)InventarItems->ChangeAddres, addr_next, sizeof(LONGLONG), lpNumOfBytes);
            ReadProcessMemory(hHandl, (LPCVOID)*addr_next, block_1, sizeof(Block_1), lpNumOfBytes);
            if (block_1->Head == Block1_Head && block_1->ToControllPtr != NULL) {
                ReadProcessMemory(hHandl, (LPCVOID)block_1->ToControllPtr, block_2, sizeof(Block_2), lpNumOfBytes);
                if (block_2->Head == Block2_Head && block_2->ll2 == BLOCK2_LL2 && block_2->ll3 == BLOCK2_LL3) {
                    InventarItems->StartPtr = addrInv;
                    addr.push_back(*InventarItems);
                }
            }
        }
        addrInv += sizeof(Inventar_items_elex2) - sizeof(LONGLONG);
        count++;
        if (count == 10000)
            break;
    } while (InventarItems->ChangeAddres != NULL && InventarItems->Head == INVENTAR_ITEMS_HEAD_ELEX2);
    return addr;
}

vector<Inventar_items_elex1> FindItemsInInventarElex1(HANDLE hHandl, LONGLONG addrInv, LONGLONG Block1_Head, LONGLONG Block2_Head) {
    SIZE_T* lpNumOfBytes = new SIZE_T;
    LONGLONG* addr_next = new LONGLONG;
    Block_1* block_1 = new Block_1;
    Block_2* block_2 = new Block_2;
    Inventar_items_elex1 *InventarItems = new Inventar_items_elex1;
    vector<Inventar_items_elex1> addr;
    int count = 0;
    do {
        ReadProcessMemory(hHandl, (LPCVOID)addrInv, InventarItems, sizeof(Inventar_items_elex1), lpNumOfBytes);
        if (InventarItems->Head == INVENTAR_ITEMS_HEAD_ELEX1 &&
            InventarItems->ChangeAddres != NULL &&
            InventarItems->ll3 == NULL &&
            InventarItems->addr != NULL &&
            InventarItems->ll5 == NULL &&
            InventarItems->ll6 == NULL &&
            InventarItems->FFFFFFFF == BYTE_FF_4 &&
            InventarItems->ll8 == NULL &&
            InventarItems->dw9 >= NULL &&
            InventarItems->nums != NULL) {
            ReadProcessMemory(hHandl, (LPCVOID)InventarItems->ChangeAddres, addr_next, sizeof(LONGLONG), lpNumOfBytes);
            ReadProcessMemory(hHandl, (LPCVOID)*addr_next, block_1, sizeof(Block_1), lpNumOfBytes);
            if (block_1->Head == Block1_Head && block_1->ToControllPtr != NULL) {
                ReadProcessMemory(hHandl, (LPCVOID)block_1->ToControllPtr, block_2, sizeof(Block_2), lpNumOfBytes);
                if (block_2->Head == Block2_Head && block_2->ll2 == BLOCK2_LL2 && block_2->ll3 == BLOCK2_LL3) {
                    InventarItems->StartPtr = addrInv;
                    addr.push_back(*InventarItems);
                }
            }
        }
        addrInv += sizeof(Inventar_items_elex1) - sizeof(LONGLONG);
        count++;
        if (count == 10000)
            break;
    } while (InventarItems->ChangeAddres != NULL && InventarItems->Head == INVENTAR_ITEMS_HEAD_ELEX1);
    return addr;
}

void GetInGameItems(HANDLE hHandl, PROCESS_MEMORY_COUNTERS ppsmemCounters, LONGLONG Block1_Head, LONGLONG Block2_Head, LONGLONG СhangeAddress, set<long long> size_page, string mode, int number_of_items) {
    MEMORY_BASIC_INFORMATION lpBuffer;
    Block_1* block_1 = new Block_1;
    Block_2* block_2 = new Block_2;
    Ids* id_struct = new Ids;
    SIZE_T* lpNumOfBytes = new SIZE_T;
    int count = 1;
    LONGLONG StartAddress = NULL, next = NULL, EndAddress;
    string yes_or_no, signatur;
    cout << " Please, Wait...." << '\n';
    while (count < number_of_items) {
        VirtualQueryEx(hHandl, (LPCVOID)next, &lpBuffer, sizeof(MEMORY_BASIC_INFORMATION));
        if (next > ppsmemCounters.PeakPagefileUsage) break;
        if (size_page.count(lpBuffer.RegionSize) == 1 && lpBuffer.State == MEM_COMMIT && lpBuffer.Type == MEM_PRIVATE && lpBuffer.Protect == PAGE_READWRITE) {
            StartAddress = next;
            EndAddress = next + lpBuffer.RegionSize;
            LONGLONG* read = new LONGLONG;
            for (StartAddress; StartAddress < EndAddress; StartAddress++) {
                ReadProcessMemory(hHandl, (LPCVOID)StartAddress, read, sizeof(LONGLONG), lpNumOfBytes);
                if (*read == Block1_Head) {
                    ReadProcessMemory(hHandl, (LPCVOID)StartAddress, block_1, sizeof(Block_1), lpNumOfBytes);
                    if (block_1->Head == Block1_Head && block_1->ToControllPtr != NULL) {
                        ReadProcessMemory(hHandl, (LPCVOID)block_1->ToControllPtr, block_2, sizeof(Block_2), lpNumOfBytes);
                        if (block_2->Head == Block2_Head && block_2->ll2 == BLOCK2_LL2 && block_2->ll3 == BLOCK2_LL3) {
                            ReadProcessMemory(hHandl, (LPCVOID*)block_1->WeUsePtr, id_struct, sizeof(Ids), lpNumOfBytes);
                            signatur = format("{:0>8x}", id_struct->Signature4) + format("{:0>8x}", id_struct->Signature3) + format("{:0>8x}", id_struct->Signature2) + format("{:0>8x}", id_struct->Signature1);
                            WriteProcessMemory(hHandl, (LPVOID)СhangeAddress, &block_1->WeUsePtr, sizeof(block_1->WeUsePtr), lpNumOfBytes);
                            if (mode == "ELEX.exe" && name_items_elex1.count(signatur) == 1)
                                cout << "[ " << count << " ] I found ( " << name_items_elex1[signatur] << " ) and changed!" << '\n';
                            else if (mode == "ELEX2.exe" && name_items_elex2.count(signatur) == 1)
                                cout << "[ " << count << " ] I found ( " << name_items_elex2[signatur] << " ) and changed!" << '\n';
                            else
                                cout << "[ " << count << " ] I found and changed!" << '\n';
                        m1:
                            cout << "Enter 'y' if you want to continue the search or 'n' if you want to end the search: ";
                            cin >> yes_or_no;
                            if (yes_or_no == "n" || yes_or_no == "N") return;
                            if (yes_or_no != "y" && yes_or_no != "Y") goto m1;
                            count++;
                            if (count > number_of_items)
                                cout << " Completed!" << '\n';
                            else
                                cout << " Please, Wait...." << '\n';
                        }
                    }
                }
            }
        }
        next += lpBuffer.RegionSize;
    }
}

DWORD FindPidElex(string mode) {
    DWORD aProcesses[10000], cbNeeded, cProcesses;
    EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded);
    for (int i = 0; i < 10000; i++) {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
        WCHAR name[MAX_PATH] = { 0 };
        GetModuleFileNameExW(hProcess, NULL, name, sizeof(name));
        wstring wstr(name);
        string str(wstr.begin(), wstr.end());
        int n = str.find(mode);
        if (n != -1)
            return aProcesses[i];
        CloseHandle(hProcess);
    }
    return -1;
}

LONGLONG GetСhangeAddrOneNameItem(HANDLE hHandl, vector<Inventar_items_elex1> *arr_struct_elex1, vector<Inventar_items_elex2> *arr_struct_elex2, string name) {
    string signatur;
    SIZE_T* lpNumOfBytes = new SIZE_T;
    Ids* id_struct = new Ids;
    if (arr_struct_elex1 != nullptr) {
        for (auto it = name_items_elex1.begin(); it != name_items_elex1.end(); it++) {
            if (it->second == name) {
                signatur = it->first;
                break;
            }
        }
        if (signatur != "") {
            for (auto it = arr_struct_elex1->begin(); it != arr_struct_elex1->end(); it++) {
                ReadProcessMemory(hHandl, (LPCVOID*)it->ChangeAddres, id_struct, sizeof(Ids), lpNumOfBytes);
                signatur = format("{:0>8x}", id_struct->Signature4) + format("{:0>8x}", id_struct->Signature3) + format("{:0>8x}", id_struct->Signature2) + format("{:0>8x}", id_struct->Signature1);
                if (name_items_elex1[signatur] == name)
                    return it->StartPtr + sizeof(LONGLONG);
            }
        }
    }
    else if (arr_struct_elex2 != nullptr) {
        for (auto it = name_items_elex2.begin(); it != name_items_elex2.end(); it++) {
            if (it->second == name) {
                signatur = it->first;
                break;
            }
        }
        if (signatur != "") {
            for (auto it = arr_struct_elex2->begin(); it != arr_struct_elex2->end(); it++) {
                ReadProcessMemory(hHandl, (LPCVOID*)it->ChangeAddres, id_struct, sizeof(Ids), lpNumOfBytes);
                signatur = format("{:0>8x}", id_struct->Signature4) + format("{:0>8x}", id_struct->Signature3) + format("{:0>8x}", id_struct->Signature2) + format("{:0>8x}", id_struct->Signature1);
                if (name_items_elex2[signatur] == name)
                    return it->StartPtr + sizeof(LONGLONG);
            }
        }
    }
    return -1;
}

LONGLONG GetСhangeAddr(HANDLE hHandl, vector<Inventar_items_elex1>* arr_struct_elex1, vector<Inventar_items_elex2>* arr_struct_elex2) {
    string signatur, str;
    SIZE_T* lpNumOfBytes = new SIZE_T;
    Ids* id_struct = new Ids;
    if (arr_struct_elex1 != nullptr) {
        if (arr_struct_elex1->size() == NULL)
            return -1;
        int i = 0;
        for (auto it = arr_struct_elex1->begin(); it != arr_struct_elex1->end(); it++) {
            ReadProcessMemory(hHandl, (LPCVOID*)it->ChangeAddres, id_struct, sizeof(Ids), lpNumOfBytes);
            signatur = format("{:0>8x}", id_struct->Signature4) + format("{:0>8x}", id_struct->Signature3) + format("{:0>8x}", id_struct->Signature2) + format("{:0>8x}", id_struct->Signature1);
            if (name_items_elex1.count(signatur) == 1)
                cout << i << " [ " << name_items_elex1[signatur] << " ]" << " number of item " << it->nums << '\n';
            else
                cout << i << " Item in inventory, number of item " << it->nums << '\n';
            i++;
        }
    m3:
        cout << "Select the item to exchange, enter the item number: ";
        cin >> str;
        try {
            i = stoi(str);
        }
        catch (invalid_argument) {
            goto m3;
        }
        catch (out_of_range) {
            goto m3;
        }
        if (i >= 0 && i < arr_struct_elex1->size())
            return arr_struct_elex1->data()[i].StartPtr + sizeof(LONGLONG);
        else
            goto m3;
    }
    else if (arr_struct_elex2 != nullptr) {
        if (arr_struct_elex2->size() == NULL)
            return -1;
        int i = 0;
        for (auto it = arr_struct_elex2->begin(); it != arr_struct_elex2->end(); it++) {
            ReadProcessMemory(hHandl, (LPCVOID*)it->ChangeAddres, id_struct, sizeof(Ids), lpNumOfBytes);
            signatur = format("{:0>8x}", id_struct->Signature4) + format("{:0>8x}", id_struct->Signature3) + format("{:0>8x}", id_struct->Signature2) + format("{:0>8x}", id_struct->Signature1);
            if (name_items_elex2.count(signatur) == 1)
                cout << i << " [ " << name_items_elex2[signatur] << " ]" << " number of item " << it->nums << '\n';
            else
                cout << i << " Item in inventory, number of item " << it->nums << '\n';
            i++;
        }
    m4:
        cout << "Select the item to exchange, enter the item number: ";
        cin >> str;
        try {
            i = stoi(str);
        }
        catch (invalid_argument) {
            goto m4;
        }
        catch (out_of_range) {
            goto m4;
        }
        if (i >= 0 && i < arr_struct_elex2->size())
            return arr_struct_elex2->data()[i].StartPtr + sizeof(LONGLONG);
        else
            goto m4;
    }
    return -1;
}

void SearchForInGameInventoryItems(string mode) {
    int number_of_items;
    LONGLONG AddrInventar, СhangeAddress = NULL, Block1_Head, Block2_Head, StructGetInvetarHead, offset;
    PROCESS_MEMORY_COUNTERS ppsmemCounters;
    vector<Inventar_items_elex1> arr_struct_elex1;
    vector<Inventar_items_elex2> arr_struct_elex2;
    set<long long> size_page;
    string yes_or_no;
    DWORD pid = FindPidElex(mode);
    if (pid == -1) {
        cout << "Game process not found!" << '\n';
        return;
    }
    if (mode == "ELEX2.exe") {
        Block1_Head = ELEX2_BLOCK1_HEAD;
        Block2_Head = ELEX2_BLOCK2_HEAD;
        number_of_items = NUMBER_OF_ITEMS_ELEX2;
        size_page = size_page_elex2;
        StructGetInvetarHead = ELEX2_STRUCT_GET_INVENTAR_HEAD;
        offset = OFFSET_ELEX2;
    }
    else if (mode == "ELEX.exe") {
        Block1_Head = ELEX1_BLOCK1_HEAD;
        Block2_Head = ELEX1_BLOCK2_HEAD;
        number_of_items = NUMBER_OF_ITEMS_ELEX1;
        size_page = size_page_elex1;
        StructGetInvetarHead = ELEX1_STRUCT_GET_INVENTAR_HEAD;
        offset = OFFSET_ELEX1;
    }
    else {
        return;
    }
    HANDLE hHandl = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hHandl) {
        cout << "Handle not found. Try restarting the program as administrator" << '\n';
        return;
    }
    GetProcessMemoryInfo(hHandl, &ppsmemCounters, sizeof(PROCESS_MEMORY_COUNTERS));
    AddrInventar = FindInventar(hHandl, ppsmemCounters, StructGetInvetarHead, offset);
    if (AddrInventar == -1) {
        cout << "Error: Inventar not faund!" << '\n';
        return;
    }
m2:
    cout << "Enter '1' if you want to change item ['Small Healling Potion']" << '\n'
         << "Enter '2' if you want to select another inventory item" << '\n' << " Your choice: ";
    if (mode == "ELEX2.exe") {
        cin >> yes_or_no;
        if (yes_or_no == "1") {
            arr_struct_elex2 = FindItemsInInventarElex2(hHandl, AddrInventar, Block1_Head, Block2_Head);
            if (arr_struct_elex2.size() == NULL) {
                cout << "Error: Inventar not faund!" << '\n';
                return;
            }
            СhangeAddress = GetСhangeAddrOneNameItem(hHandl, nullptr, &arr_struct_elex2, "Small Healling Potion");
            if (СhangeAddress == -1) {
                cout << "Error: Make sure 'Small Healing Potion' is in inventory" << '\n';
                return;
            }
        }
        else if (yes_or_no == "2") {
            arr_struct_elex2 = FindItemsInInventarElex2(hHandl, AddrInventar, Block1_Head, Block2_Head);
            if (arr_struct_elex2.size() == NULL) {
                cout << "Error: Inventar not faund!" << '\n';
                return;
            }
            СhangeAddress = GetСhangeAddr(hHandl, nullptr, &arr_struct_elex2);
            if (СhangeAddress == -1) {
                cout << "Error: GetChangeAddr not working" << '\n';
                return;
            }
        }
        else {
            goto m2;
        }
        GetInGameItems(hHandl, ppsmemCounters, Block1_Head, Block2_Head, СhangeAddress, size_page, mode, number_of_items);
    }
    else if (mode == "ELEX.exe") {
        cin >> yes_or_no;
        if (yes_or_no == "1") {
            arr_struct_elex1 = FindItemsInInventarElex1(hHandl, AddrInventar, Block1_Head, Block2_Head);
            if (arr_struct_elex1.size() == NULL) {
                cout << "Error: Inventar not faund!" << '\n';
                return;
            }
            СhangeAddress = GetСhangeAddrOneNameItem(hHandl, &arr_struct_elex1, nullptr, "Small Healling Potion");
            if (СhangeAddress == -1) {
                cout << "Error: Make sure 'Small Healing Potion' is in inventory" << '\n';
                return;
            }
        }
        else if (yes_or_no == "2") {
            arr_struct_elex1 = FindItemsInInventarElex1(hHandl, AddrInventar, Block1_Head, Block2_Head);
            if (arr_struct_elex1.size() == NULL) {
                cout << "Error: Inventar not faund!" << '\n';
                return;
            }
            СhangeAddress = GetСhangeAddr(hHandl, &arr_struct_elex1, nullptr);
            if (СhangeAddress == -1) {
                cout << "Error: GetChangeAddr not working" << '\n';
                return;
            }
        }
        else {
            goto m2;
        }
        GetInGameItems(hHandl, ppsmemCounters, Block1_Head, Block2_Head, СhangeAddress, size_page, mode, number_of_items);
    }
}

void AboutProgram() {
    cout << "/**********************************************************************************************************" << '\n'
         << "ELEX-ELEX2-Geting-All-In-Game-Items Version 1.0. A program for geting all inventory items of" << '\n'
         << "the game ELEX 1 and 2. Used to enumerate all in-game inventory items and replace the old" << '\n'
         << "inventory item with the new item received." << '\n'
         << '\n'
         << "Copyright(C) 2023  Maxim Shershavikov" << '\n'
         << "This file is part of ELEX-ELEX2-Geting-All-In-Game-Items." << '\n'
         << '\n'
         << "ELEX-ELEX2-Geting-All-In-Game-Items is free software: you can redistribute it and/or modify" << '\n'
         << "it under the terms of the GNU General Public License as published by the Free Software Foundation," << '\n'
         << "either version 3 of the License, or (at your option) any later version." << '\n'
         << '\n'
         << "ELEX-ELEX2-Geting-All-In-Game-Items is distributed in the hope that it will be useful," << '\n'
         << "but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or" << '\n'
         << "FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details." << '\n'
         << '\n'
         << "You should have received a copy of the GNU General Public License along with this program." << '\n'
         << "If not, see <https://www.gnu.org/licenses/>. Email m.shershavikov@yandex.ru" << '\n'
         << '\n'
         << "To read a copy of the GNU General Public License in a file COPYING.txt, to do this, enter 3 at" << '\n'
         << "the beginning of the program." << '\n'
         << "**********************************************************************************************************/" << '\n';
    ShellExecute(NULL, L"open", L"COPYING.txt", NULL, NULL, SW_SHOWNORMAL);
}

void main() {
    while (true) {
        string mode;
        cout << '\n' << "-------------[ Search for in-game items in the inventory of the game ELEX and ELEX 2 ]-------------" << '\n' << '\n';
        cout << "Select part of ELEX:" << '\n'
             << "Enter '1' if you play ELEX 1" << '\n'
             << "Enter '2' if you play ELEX 2" << '\n'
             << "Enter '3' if you want information about the program" << '\n'
             << " Your choice: ";
        cin >> mode;
        if (mode == "1")
            SearchForInGameInventoryItems("ELEX.exe");
        else if (mode == "2")
            SearchForInGameInventoryItems("ELEX2.exe");
        else if (mode == "3")
            AboutProgram();
    }
}
