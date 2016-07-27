// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string>

#include "base/mac/scoped_nsobject.h"
#include "base/memory/scoped_ptr.h"
#include "base/prefs/testing_pref_service.h"
#include "ios/chrome/browser/geolocation/location_manager.h"
#include "ios/chrome/browser/geolocation/omnibox_geolocation_local_state.h"
#include "ios/chrome/test/testing_application_context.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "testing/gtest_mac.h"
#include "testing/platform_test.h"

namespace {

class OmniboxGeolocationLocalStateTest : public PlatformTest {
 protected:
  OmniboxGeolocationLocalStateTest() {
    TestingApplicationContext::GetGlobal()->SetLocalState(&prefs_);
    location_manager_.reset([[LocationManager alloc] init]);
    local_state_.reset([[OmniboxGeolocationLocalState alloc]
        initWithLocationManager:location_manager_]);
    [OmniboxGeolocationLocalState registerLocalState:prefs_.registry()];
  }

  ~OmniboxGeolocationLocalStateTest() override {
    TestingApplicationContext::GetGlobal()->SetLocalState(nullptr);
  }

  TestingPrefServiceSimple prefs_;
  base::scoped_nsobject<LocationManager> location_manager_;
  base::scoped_nsobject<OmniboxGeolocationLocalState> local_state_;
};

TEST_F(OmniboxGeolocationLocalStateTest, LastAuthorizationAlertVersion) {
  EXPECT_TRUE([local_state_ lastAuthorizationAlertVersion].empty());

  std::string expectedVersion("fakeVersion");
  [local_state_ setLastAuthorizationAlertVersion:expectedVersion];
  EXPECT_EQ(expectedVersion, [local_state_ lastAuthorizationAlertVersion]);
}

}  // namespace