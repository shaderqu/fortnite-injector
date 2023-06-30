#pragma once
#include <cstdint>
#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <psapi.h>
#include "../utils/lazy_importer.h"
#include "../utils/utils.h"
#include "../utils/xor.h"
#include "../driver/driver.h"
#include "../map/inject.h"

class Inject
{
public:
	Inject() {};
	~Inject() {};
	bool inject_module_from_path_to_process_by_name(const wchar_t* module_path, const wchar_t* process_name);

private:

};