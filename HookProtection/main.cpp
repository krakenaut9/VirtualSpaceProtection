#include <Windows.h>
#include <iostream>
#include "HookUtils.h"
#include "dllUtils.h"
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

static decltype(::LoadLibraryA)* g_loadLibraryA = nullptr;
static decltype(::LoadLibraryW)* g_loadLibraryW = nullptr;
   
//�� ������� ���������������, ���� �������� ������� ������� LoadLibraryA
//�� ���� ��������� ������������� ��'� �������� ����� �� �������������
//��� �������� �������, �� ����� ���� ��������
HMODULE WINAPI LoadLibraryA_Hook(_In_ LPCSTR lpLibFileName)
{
    if (!dllUtils::isDllSafe(std::wstring(lpLibFileName, lpLibFileName + std::strlen(lpLibFileName))))
    {
        PLOGW << "Attempt to load unknown Dll. Name : " << lpLibFileName;
        return nullptr;
    }

    return g_loadLibraryA(lpLibFileName);
}

//�� ������� ���������������, ���� �������� ������� ������� LoadLibraryW
//�� ���� ��������� ������������� ��'� �������� ����� �� �������������
//��� �������� �������, �� ����� ���� ��������
HMODULE WINAPI LoadLibraryW_Hook(_In_ LPCWSTR lpLibFileName)
{
    if (!dllUtils::isDllSafe(lpLibFileName))
    {
        PLOGW << "Attempt to load unknown Dll. Name : " << lpLibFileName;
        return nullptr;
    }

    return g_loadLibraryW(lpLibFileName);
}


int wmain(int argc, wchar_t** argv)
{
    plog::init(plog::debug, L"C:\\Users\\User\\Desktop\\HookProtection.log");

    g_loadLibraryA = hookUtils::HookFunc(L"kernel32.dll", "LoadLibraryA", LoadLibraryA_Hook);
    g_loadLibraryW = hookUtils::HookFunc(L"kernel32.dll", "LoadLibraryW", LoadLibraryW_Hook);

    std::cout << "Hello world";
    system("pause");
    return 0;
}