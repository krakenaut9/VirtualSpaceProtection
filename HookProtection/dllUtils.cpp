#include "dllUtils.h"

bool dllUtils::isDllSafe(const std::wstring& dllName)
{
    PLOGI << L"Checking dll : " << dllName;
    return isNameAllowed(dllName) && isPathAllowed(dllName) && isDigitalSignatureValid(dllName);
}