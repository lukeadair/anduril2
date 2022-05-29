/*
 * tint-ramping.c: Tint ramping functions for Anduril.
 *
 * Copyright (C) 2017 Selene Scriven
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TINT_RAMPING_C
#define TINT_RAMPING_C

#include "tint-ramping.h"

uint8_t tint_ramping_state(Event event, uint16_t arg) {
	
    // click, click, hold: change the tint
    if (event == EV_3clicks) {
        ///// tint-toggle mode
        // toggle once on first frame; ignore other frames
        if (tint_style) {
            // only respond on first frame
            if (arg) return EVENT_NOT_HANDLED;

            // force tint to be 1 or 254
            if (tint != 254) { tint = 1; }
            // invert between 1 and 254
            tint = tint ^ 0xFF;
            set_level(actual_level);

			// remember tint after battery change
	        save_config();

            return EVENT_HANDLED;
        }

        return EVENT_HANDLED;
    }

    return EVENT_NOT_HANDLED;
}


#endif
