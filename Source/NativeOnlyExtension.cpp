#include "NativeOnlyExtension.h"

#include <array>

#include <Windows.h>

namespace
{
    static constexpr auto JS_BABYLON_NAME = "BABYLONX";

    class NativeDevice : public Napi::ObjectWrap<NativeDevice>
    {
        static constexpr auto JS_CLASS_NAME = "NativeDevice";

    public:
        static void Initialize(Napi::Env env)
        {
            Napi::HandleScope scope{ env };

            Napi::Function func = DefineClass(
                env,
                JS_CLASS_NAME,
                {
                    StaticAccessor("Name", &NativeDevice::GetName, nullptr),
                });

            auto global = env.Global();
            auto babylon = global.Get(JS_BABYLON_NAME).As<Napi::Object>();
            if (babylon.IsUndefined())
            {
                babylon = Napi::Object::New(env);
                global.Set(JS_BABYLON_NAME, babylon);
            }
            babylon.Set(JS_CLASS_NAME, func);
        }

        NativeDevice(const Napi::CallbackInfo& info)
            : Napi::ObjectWrap<NativeDevice>(info)
        {
        }

    private:
        static Napi::Value GetName(const Napi::CallbackInfo& info)
        {
            char chars[1024];
            DWORD length;
            GetComputerNameA(chars, &length);
            return Napi::String::New(info.Env(), chars, static_cast<size_t>(length));
        }
    };
}

namespace Babylon::Extensions::NativeOnlyExtension
{
    void Initialize(Napi::Env env)
    {
        NativeDevice::Initialize(env);
    }

    void LoadScripts(ScriptLoader& scriptLoader, const std::string& scriptsRootUrl)
    {
        scriptLoader.LoadScript(scriptsRootUrl + "./NativeOnlyExtension.js");
    }
}
