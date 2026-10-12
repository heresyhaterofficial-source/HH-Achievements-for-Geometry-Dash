
#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include "Achievements.hpp"

using namespace geode::prelude;

namespace AchievementsMenu {

class AchievementPopup : public geode::Popup {
protected:
    bool init() {
        if (!Popup::init(320.f, 220.f, "GJ_square01.png"))
            return false;

        this->setTitle("Level Achievements");

        auto status = [](std::string const& id) {
            return Achievements::isUnlocked(id)
                ? "UNLOCKED"
                : "LOCKED";
        };


        auto addAchievement = [this](
            const char* name,
            const char* achievementID,
            float y
        ) {
            bool unlocked = Achievements::isUnlocked(achievementID);

            std::string text =
                std::string(unlocked ? "[UNLOCKED] " : "[LOCKED] ")
                + name;

            auto label = CCLabelBMFont::create(
                text.c_str(),
                "bigFont.fnt"
            );

            label->setAnchorPoint({0.f, 0.5f});
            label->setScale(0.45f);
            label->setPosition({160.f, y});

            this->addChild(label);
        };

        addAchievement("Complete Stereotypical \nDashin", "first-contact", 200.f);
        addAchievement("Complete How to 9 Circles L1", "second-wind", 180.f);
        addAchievement("Complete first 2 levels", "the-collection", 160.f);

        auto resetButton = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Reset Achievements"),
            this,
            menu_selector(AchievementPopup::onReset)
        );

        resetButton->setScale(0.7f);
        resetButton->setPosition({160.f, 45.f});
        this->m_buttonMenu->addChild(resetButton);

        return true;
    }

public:
    static AchievementPopup* create() {
        auto ret = new AchievementPopup();

        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    void onReset(CCObject*) {
        geode::createQuickPopup(
            "Reset Achievements",
            "Are you sure you want to reset all achievements?",
            "Cancel",
            "Reset",
            [](FLAlertLayer*, bool confirmed) {
                if (!confirmed)
                    return;

                Achievements::resetAll();

                FLAlertLayer::create(
                    "Achievements Reset",
                    "All achievements have been reset. "
                    "Close and reopen the menu to refresh it.",
                    "OK"
                )->show();
            }
        );
    }
};

inline void open() {
    AchievementPopup::create()->show();
}

}
