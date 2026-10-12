
#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Notification.hpp>

using namespace geode::prelude;

namespace AchievementNotification {
    inline void show(
        std::string const& name,
        std::string const& description
    ) {
        auto notification = Notification::create(
            "Achievement Unlocked: " + name,
            NotificationIcon::Success,
            3.0f
        );

        if (notification) {
            notification->show();
        }
    }
}
