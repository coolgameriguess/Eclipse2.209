#include <modules/config/config.hpp>
#include <modules/gui/gui.hpp>
#include <modules/gui/components/toggle.hpp>
#include <modules/hack/hack.hpp>

#include <Geode/modify/PlayLayer.hpp>

namespace eclipse::hacks::Level {
    class $hack(NoEndShake) {
        void init() override {
            auto tab = gui::MenuTab::find("tab.level");
            tab->addToggle("level.noendshake")->setDescription()->handleKeybinds();
        }

        [[nodiscard]] const char* getId() const override { return "No End Shake"; }
    };

    REGISTER_HACK(NoEndShake)

    class $modify(NoEndShakePLHook, PlayLayer) {
        ADD_HOOKS_DELEGATE("level.noendshake")

        void showCompleteEffect() {
          auto cameraShakeOffset = m_gameState.m_cameraShakeOffset;
          auto cameraShakeDuration = m_gameState.m_cameraShakeDuration;
          auto cameraShakeInterval = m_gameState.m_cameraShakeInterval;
          auto cameraShakeStrength = m_gameState.m_cameraShakeStrength;
          PlayLayer::showCompleteEffect();
          m_gameState.m_cameraShakeOffset = cameraShakeOffset;
          m_gameState.m_cameraShakeDuration = cameraShakeDuration;
          m_gameState.m_cameraShakeInterval = cameraShakeInterval;
          m_gameState.m_cameraShakeStrength = cameraShakeStrength;
        }
    };
}
