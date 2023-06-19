#include <shellapi.h>
#include <imgui-cocos.hpp>
#include <chrono>

#include <Geode/modify/OptionsLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/loader/Mod.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;

bool isMenuShown = true;


bool isNoclip = false;

auto isNotHide = Mod::get()->getSavedValue<bool>("isNotHide");
auto isNotShake = Mod::get()->getSavedValue<bool>("isNotShake");
auto isNotDeathEffect = Mod::get()->getSavedValue<bool>("isNotDeathEffect");


class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down) {
        if (down && (key == KEY_Tab GEODE_MACOS(|| key == KEY_Tab))) {
            isMenuShown = !isMenuShown;
            return true;
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
    }
};


class $modify(PlayLayer) {


    void destroyPlayer(PlayerObject* p, GameObject* g) 
    {
        if (!isNoclip)
        {
            PlayLayer::destroyPlayer(p, g);
        }
    }


    void shakeCamera(float p0, float p1, float p2) {
        if (!isNotShake)
        {
            PlayLayer::shakeCamera(p0, p1, p2);
        }
    }

};

class $modify(PlayerObject) {
    void toggleVisibility(bool p0)
    {
        if (!isNotHide)
        {
            PlayerObject::toggleVisibility(p0);
        }
    }

    void playDeathEffect() 
    {
        if (!isNotDeathEffect)
        {
            PlayerObject::playDeathEffect();
        }
    }
};

$on_mod(Loaded) {

    

    ImGuiCocos::get().setup([&] {
        // ImGui Style from https://www.unknowncheats.me/forum/c-and-c-/189635-imgui-style-settings.html
        ImGuiStyle * style = &ImGui::GetStyle();
        
            style->WindowPadding = ImVec2(15, 15);
            style->WindowRounding = 5.0f;
            style->FramePadding = ImVec2(5, 5);
            style->FrameRounding = 4.0f;
            style->ItemSpacing = ImVec2(12, 8);
            style->ItemInnerSpacing = ImVec2(8, 6);
            style->IndentSpacing = 25.0f;
            style->ScrollbarSize = 15.0f;
            style->ScrollbarRounding = 9.0f;
            style->GrabMinSize = 5.0f;
            style->GrabRounding = 3.0f;
        
            style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
            style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
            style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
            style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
            style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
            style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
            style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
            style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
            style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
            style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
            style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
            style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
            style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
            style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
            style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
            style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
            style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
            style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
            style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
            style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
            style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
            style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
            style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
            style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

    }).draw([&] {


        if (isMenuShown) {
            ImGui::Begin("Misc");
            
            if (ImGui::Button("AppData"))
            {
                ShellExecuteA(NULL, "open", CCFileUtils::get()->getWritablePath().c_str(), NULL, NULL, SW_SHOWDEFAULT);
            }

            if (ImGui::Button("Settings"))
            {
                OptionsLayer::addToCurrentScene(false);
            }

            ImGui::End();


            // Cheats and more stuff
            ImGui::Begin("Player");
            
            ImGui::Checkbox("Noclip", &isNoclip);

            ImGui::End();


            // Visual Stuff
            ImGui::Begin("Visual");
            
            if (ImGui::Checkbox("No Camera Shake", &isNotShake))
            {
                Mod::get()->setSavedValue<bool>("isNotShake", isNotDeathEffect);
            }

            if (ImGui::Checkbox("No Death Effect", &isNotDeathEffect))
            {
                Mod::get()->setSavedValue<bool>("isNotDeathEffect", isNotDeathEffect);
            }

            ImGui::Checkbox("No Hide Player", &isNotHide);

            ImGui::End();

        }
    });
}



