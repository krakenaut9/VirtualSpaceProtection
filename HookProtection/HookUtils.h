#pragma once
#include <Windows.h>
#include <atlbase.h>
#include "plog/Log.h"
#include "mhook.h"


namespace hookUtils
{
    template<typename FnType>
    FnType HookFunc(LPCWSTR ModuleName, LPCSTR TargetFunctionName, FnType HookFunction)
    {
        CHandle Module(GetModuleHandle(ModuleName));
        if (!Module)
        {
            PLOGE << "Module " << ModuleName << " not found. LE : " << GetLastError();
            std::cout << "Module not found : " << ModuleName << std::endl;
            return nullptr;
        }

        FnType realFunction = reinterpret_cast<FnType>(GetProcAddress(reinterpret_cast<HMODULE>(Module.m_h), TargetFunctionName));
        if (!realFunction)
        {
            PLOGE << "Function " << TargetFunctionName << " not found. LE : " << GetLastError();
            std::cout << "Function not found " << TargetFunctionName << std::endl;
            return nullptr;
        }

        BOOL hookSucceeded = Mhook_SetHook(reinterpret_cast<PVOID*>(&realFunction), HookFunction);
        if (!hookSucceeded)
        {
            PLOGE << "Failed to hook function " << TargetFunctionName << ". LE : " << GetLastError();
            std::cout << "Hook failed " << TargetFunctionName << std::endl;
            return nullptr;
        }
        return realFunction;
    }
}