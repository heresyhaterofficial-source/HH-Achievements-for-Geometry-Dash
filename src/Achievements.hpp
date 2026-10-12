#pragma once

#include <Geode/Geode.hpp>
#include <set>
#include "AchievementNotification.hpp"

namespace Achievements {
    inline constexpr int LEVEL_ONE = 150220072;
    inline constexpr int LEVEL_TWO = 150361303;

    inline bool isUnlocked(std::string const& id) {
        return geode::Mod::get()->getSavedValue<bool>(
            "achievement-" + id, false
        );
    }

    inline bool unlock(std::string const& id) {
        if (isUnlocked(id))
            return false;

        geode::Mod::get()->setSavedValue(
            "achievement-" + id, true
        );
        return true;
    }

    inline bool isTrackedLevel(int levelID) {
        return levelID == LEVEL_ONE ||
               levelID == LEVEL_TWO;
    }

    inline void onLevelCompleted(int levelID) {
        if (levelID == LEVEL_ONE &&
            unlock("first-contact")) {
            AchievementNotification::show(
                "First Contact",
                "Complete Stereotypical Dashin."
            );
        }

        if (levelID == LEVEL_TWO &&
            unlock("second-wind")) {
            AchievementNotification::show(
                "Second Wind",
                "Complete How to 9 Circles L1."
            );
        }

        if (isUnlocked("first-contact") &&
            isUnlocked("second-wind") &&
            unlock("the-collection")) {
            AchievementNotification::show(
                "The Collection",
                "Complete both levels."
            );
        }
    }
    
    inline void resetAll() {
        auto mod = geode::Mod::get();

        mod->setSavedValue<bool>("achievement-first-contact", false);
        mod->setSavedValue<bool>("achievement-second-wind", false);
        mod->setSavedValue<bool>("achievement-the-collection", false);
    }

}