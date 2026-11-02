#include <modules/config/config.hpp>
#include <modules/gui/gui.hpp>
#include <modules/gui/components/toggle.hpp>
#include <modules/hack/hack.hpp>

#include <Geode/modify/EditorPauseLayer.hpp>

namespace eclipse::hacks::Creator {
    class $hack(ResetPercentOnSave) {
        void init() override {
            auto tab = gui::MenuTab::find("tab.creator");
            tab->addToggle("creator.resetpercentonsave")->handleKeybinds()->setDescription();
        }

        [[nodiscard]] const char* getId() const override { return "Reset Percent on Save"; }
    };

    REGISTER_HACK(ResetPercentOnSave)

    class $modify(ResetPercentEPLHook, EditorPauseLayer) {
        ADD_HOOKS_DELEGATE("creator.resetpercentonsave")

        // saveLevel() itself is inlined on Windows and can no longer be
        // hooked, so hook every button handler that leads to it instead.
        void resetPercentIfEditor() {
            if (m_editorLayer->m_level->m_levelType == GJLevelType::Editor) m_editorLayer->m_level->m_normalPercent = 0;
        }

        void onSave(cocos2d::CCObject* sender) {
            resetPercentIfEditor();
            EditorPauseLayer::onSave(sender);
        }

        void onSaveAndExit(cocos2d::CCObject* sender) {
            resetPercentIfEditor();
            EditorPauseLayer::onSaveAndExit(sender);
        }

        void onSaveAndPlay(cocos2d::CCObject* sender) {
            resetPercentIfEditor();
            EditorPauseLayer::onSaveAndPlay(sender);
        }
    };
}
