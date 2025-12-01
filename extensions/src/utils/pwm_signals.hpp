#pragma once

#include "pwm_string_view.hpp"

namespace pwm::signals
{

constinit auto static SELECTED = pwm::string_view{ "selected" };
constinit auto static VIEW_CHANGED = pwm::string_view{ "view_changed" };
constinit auto static MAGIC_BOOK_CLICKED = pwm::string_view{ "magic_book_clicked" };
constinit auto static HERO_SELECTED = pwm::string_view{ "hero_selected" };
constinit auto static TEXTURE_ACTIVATED = pwm::string_view{ "texture_activated" };
constinit auto static SKILL_ACTIVATED = pwm::string_view{ "skill_activated" };
constinit auto static PRESSED = pwm::string_view{ "pressed" };

}
