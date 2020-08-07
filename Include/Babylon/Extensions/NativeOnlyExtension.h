#pragma once

#include <Babylon/ScriptLoader.h>

#include <napi/env.h>

namespace Babylon::Extensions::NativeOnlyExtension
{
    void Initialize(Napi::Env);

    void LoadScripts(ScriptLoader& scriptLoader, const std::string& scriptsRootUrl);
}
