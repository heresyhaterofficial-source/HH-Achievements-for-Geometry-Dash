#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "Achievements.hpp"
#include "AchievementsMenu.hpp"

using namespace geode::prelude;

// Add the button to the main menu.
class $modify(AchievementMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto menu = this->getChildByID("bottom-menu");
        if (!menu)
            return true;

        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("HH"),
            this,
            menu_selector(
                AchievementMenuLayer::onAchievements
            )
        );

        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void onAchievements(CCObject*) {
        AchievementsMenu::open();
    }
};

// Track completed levels.
class $modify(AchievementPlayLayer, PlayLayer) {
    void levelComplete() {
        auto level = m_level;
        int levelID = level ? level->m_levelID : 0;

        PlayLayer::levelComplete();

        if (levelID > 0 &&
            Achievements::isTrackedLevel(levelID)) {
            Achievements::onLevelCompleted(levelID);
        }
    }
};