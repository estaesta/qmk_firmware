// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku
// generated from users/manna-harbour_miryoku/miryoku.org  -*- buffer-read-only: t -*-

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include QMK_KEYBOARD_H
#include "oled.c"

#define U_NP KC_NO  // key is not present
#define U_NA KC_NO  // present but not available for use
#define U_NU KC_NO  // available but not used

enum layers { BASE, BUTTON, GAMING, QWRT, MEDIA, NAV, MOUSE, SYM, NUM, FUN };

enum my_keycodes {
  MY_TAB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MY_TAB:
      if (record->event.pressed) {
        // Do something when pressed
        SEND_STRING(SS_DOWN(X_TAB));
      } else {
        // Do something else when release
        SEND_STRING(SS_UP(X_TAB));
      }
      return false; // Skip all further processing of this key
    default:
        oled_timer = timer_read();
        oled_on();
      return true; // Process all other keycodes normally
  }
}
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
            return TAPPING_TERM + 50; // Recommended
        case LGUI_T(KC_COLN):
            return TAPPING_TERM + 50; // Recommended
        case LGUI_T(KC_O):
            return TAPPING_TERM + 50; // Recommended
        default:
            return TAPPING_TERM;
    }
}

#if defined MIRYOKU_CLIPBOARD_FUN
#    define U_RDO KC_AGIN
#    define U_PST KC_PSTE
#    define U_CPY KC_COPY
#    define U_CUT KC_CUT
#    define U_UND KC_UNDO
#elif defined MIRYOKU_CLIPBOARD_MAC
#    define U_RDO SCMD(KC_Z)
#    define U_PST LCMD(KC_V)
#    define U_CPY LCMD(KC_C)
#    define U_CUT LCMD(KC_X)
#    define U_UND LCMD(KC_Z)
#elif defined MIRYOKU_CLIPBOARD_WIN
#    define U_RDO C(KC_Y)
#    define U_PST C(KC_V)
#    define U_CPY C(KC_C)
#    define U_CUT C(KC_X)
#    define U_UND C(KC_Z)
#else
#    define U_RDO KC_AGIN
#    define U_PST S(KC_INS)
#    define U_CPY C(KC_INS)
#    define U_CUT S(KC_DEL)
#    define U_UND KC_UNDO
#endif
#ifdef OLED_ENABLE

void oled_task_user(void) {
    if (is_oled_on()) {
        if (timer_elapsed(oled_timer) < 30000) {
            render_animation((timer_read()/240) % 4);
        } else {
            /* oled_timer = 0; */
            oled_off();
        }
    } else {

    }

    switch (get_highest_layer(layer_state)) {
        case BASE:
//            oled_write_raw_P(my_logo, sizeof(my_logo));
            oled_write_P(PSTR("colemak-dh\n"), false);
            break;
        case BUTTON:
            oled_write_P(PSTR("Button\n"), false);
            break;
        case GAMING:
            oled_write_P(PSTR("Gaming\n"), false);
            break;
        case QWRT:
            oled_write_P(PSTR("qwerty\n"), false);
            break;
        case MEDIA:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case NAV:
            oled_write_P(PSTR("Nav\n"), false);
            break;
        case MOUSE:
            oled_write_P(PSTR("Mouse\n"), false);
            break;
        case SYM:
            oled_write_P(PSTR("Symbol\n"), false);
            break;
        case NUM:
            oled_write_P(PSTR("Number\n"), false);
            break;
        case FUN:
            oled_write_P(PSTR("Fun\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

#endif
