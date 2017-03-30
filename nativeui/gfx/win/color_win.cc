// Copyright 2016 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#include "nativeui/gfx/color.h"

namespace nu {

COLORREF Color::ToCOLORREF() const {
  return RGB(r(), g(), b());
}

Color PlatformGetSystemColor(SystemColor id) {
  int index = 0;
  if (id == SystemColor::Text)
    index = COLOR_WINDOWTEXT;
  DWORD color = ::GetSysColor(index);
  return Color(GetRValue(color), GetGValue(color), GetBValue(color));
}

}  // namespace nu
