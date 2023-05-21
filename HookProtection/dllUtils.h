#pragma once
#include "plog/Log.h"

namespace
{
    bool isDigitalSignatureValid(const std::wstring& dllName)
    {
        return true;
    }

    bool isNameAllowed(const std::wstring& dllName)
    {
        return false;
    }

    bool isPathAllowed(const std::wstring& dllName)
    {
        return true;
    }
}

namespace dllUtils
{
    bool isDllSafe(const std::wstring& dllName);
}