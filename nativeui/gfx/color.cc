// Copyright 2016 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#include "nativeui/gfx/color.h"

#include <map>
#include <vector>

#include "base/strings/string_number_conversions.h"

namespace nu {

namespace {

// Cached theme colors.
std::map<SystemColor, Color> g_theme_colors;

const uint32_t kColorWhite = 0xFFFFFFFF;

uint32_t ParseHexColor(const std::string& color_string) {
  // Check the string for incorrect formatting.
  if (color_string.empty() || color_string[0] != '#')
    return kColorWhite;

  // Prepend FF if alpha channel is not specified.
  std::string source = color_string.substr(1);
  if (source.size() == 3)
    source.insert(0, "F");
  else if (source.size() == 6)
    source.insert(0, "FF");

  // Convert the string from #FFF format to #FFFFFF format.
  std::string formatted_color;
  if (source.size() == 4) {
    for (size_t i = 0; i < 4; ++i) {
      formatted_color += source[i];
      formatted_color += source[i];
    }
  } else if (source.size() == 8) {
    formatted_color = source;
  } else {
    return kColorWhite;
  }

  // Convert the string to an integer and make sure it is in the correct value
  // range.
  std::vector<uint8_t> bytes;
  if (!base::HexStringToBytes(formatted_color, &bytes))
    return kColorWhite;

  return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) |
         (bytes[3] << 0);
}

}  // namespace

Color::Color(const std::string& hex) : value_(ParseHexColor(hex)) {}

// The platform implementation to get theme color.
Color PlatformGetSystemColor(SystemColor id);

Color GetSystemColor(SystemColor id) {
  auto it = g_theme_colors.find(id);
  if (it != g_theme_colors.end())
    return it->second;
  Color color = PlatformGetSystemColor(id);
  g_theme_colors[id] = color;
  return color;
}

}  // namespace nu
