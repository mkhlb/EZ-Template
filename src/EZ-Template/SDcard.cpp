/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "main.h"

namespace ez
{
  namespace sd
  {
    const bool IS_SD_CARD = pros::usd::is_installed();


    void init_auton_selector(AutonSelector selector) {
      // If no SD card, return
      if (!IS_SD_CARD)  return;

      // Auton Selector
      FILE* usd_file_read = fopen("/usd/auto.txt", "r");
      char buf[5];
      fread(buf, 1, 5, usd_file_read);
      selector.CurrentAutonPage = std::stoi(buf);
      fclose(usd_file_read);

      if(selector.CurrentAutonPage>selector.AutonCount-1 || selector.CurrentAutonPage<0)
      {
        selector.CurrentAutonPage=0;
        update_auto_sd(selector);
      }
    }

    void update_auto_sd(AutonSelector autoSelector) {
      // If no SD card, return
      if (!IS_SD_CARD) return;

      FILE* usd_file_write = fopen("/usd/auto.txt", "w");
      std::string cp_str = std::to_string(autoSelector.CurrentAutonPage);
      char const *cp_c = cp_str.c_str();
      fputs(cp_c, usd_file_write);
      fclose(usd_file_write);
    }

    void page_up(AutonSelector autoSelector)
    {

      if (autoSelector.CurrentAutonPage == autoSelector.AutonCount - 1)
        autoSelector.CurrentAutonPage = 0;
      else
        autoSelector.CurrentAutonPage++;
      update_auto_sd(autoSelector);
      autoSelector.PrintSelectedAuto();
    }

    void page_down(AutonSelector autoSelector)
    {
      if (autoSelector.CurrentAutonPage == 0)
        autoSelector.CurrentAutonPage = autoSelector.AutonCount - 1;
      else
        autoSelector.CurrentAutonPage--;
      update_auto_sd(autoSelector);
      autoSelector.PrintSelectedAuto();
    }
  } // sd namespace
} // ez namespace
