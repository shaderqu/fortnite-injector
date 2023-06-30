#include "map/inject.h"
#include <string_view>

int main(int argc, char* argv[])
{
    wchar_t** wide_argv = new wchar_t* [argc + 1];
    for (size_t i = 0; i < argc; ++i) {
        size_t length = mbstowcs(nullptr, argv[i], 0);
        wide_argv[i] = new wchar_t[length + 1];
        mbstowcs(wide_argv[i], argv[i], length + 1);
    }
    wide_argv[argc] = nullptr;

    if (argc == 2) {

        Inject* inject = new Inject();
        inject->inject_module_from_path_to_process_by_name(wide_argv[1], xor_w(L"FortniteClient-Win64-Shipping.exe"));
    }
    else if (argc == 3)
    {
        Inject* inject = new Inject();
        inject->inject_module_from_path_to_process_by_name(wide_argv[1], wide_argv[2]);
    }
    return 0;
}