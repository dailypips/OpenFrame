// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/views/frame/native_browser_frame_factory.h"

#include "chrome/browser/ui/views/frame/browser_frame_ash.h"
#include "chrome/browser/ui/views/frame/desktop_browser_frame_auralinux.h"

#if defined(MOJO_SHELL_CLIENT)
#include "chrome/browser/ui/views/frame/browser_frame_mus.h"
#include "content/public/common/mojo_shell_connection.h"
#endif

NativeBrowserFrame* NativeBrowserFrameFactory::Create(
    BrowserFrame* browser_frame,
    BrowserView* browser_view) {
#if defined(MOJO_SHELL_CLIENT)
  if (content::MojoShellConnection::Get())
    return new BrowserFrameMus(browser_frame, browser_view);
#endif

  if (ShouldCreateForAshDesktop(browser_view))
    return new BrowserFrameAsh(browser_frame, browser_view);

  return new DesktopBrowserFrameAuraLinux(browser_frame, browser_view);
}