// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file defines a utility function to get the full path of a module.

#ifndef CHROME_INSTALLER_UTIL_MODULE_UTIL_WIN_H_
#define CHROME_INSTALLER_UTIL_MODULE_UTIL_WIN_H_

#include "base/files/file_path.h"
#include "base/strings/string16.h"
#include "base/strings/string_piece.h"

namespace installer {

// Returns the full path to |module_name|. Both dev builds (where |module_name|
// is in the current executable's directory) and proper installs (where
// |module_name| is in a versioned sub-directory of the current executable's
// directory) are suported. In the latter case, |version| is populated with the
// name of the versioned sub-directory (i.e., the current executable's
// version). Returns an empty path if the current executable appears to reside
// in a proper install but version information is missing. The identified file
// is not guaranteed to exist.
base::FilePath GetModulePath(base::StringPiece16 module_name,
                             base::string16* version);

}  // namespace installer

#endif  // CHROME_INSTALLER_UTIL_MODULE_UTIL_WIN_H_
