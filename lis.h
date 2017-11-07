/* Copyright 2011 David Irvine
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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $Rev: 127 $
 * $Author: irvined $
 * $Date: 2012-04-09 10:20:42 +0200 (Mon, 09 Apr 2012) $
 *
*/

#define LR_MAX_TRIES 12

#define LR_CTRL_REG1 0x20
#define LR_CTRL_REG2 0x21
#define LR_CTRL_REG3 0x22
#define LR_CTRL_REG4 0x23
#define LR_CTRL_REG5 0x24
#define LR_HP_FILTER_RESET 0x25
#define LR_REFERENCE 0x26
#define LR_STATUS_REG 0x27
#define LR_OUT_X_L 0x28
#define LR_OUT_X_H 0x29
#define LR_OUT_Y_L 0x2A
#define LR_OUT_Y_H 0x2B
#define LR_OUT_Z_L 0x2C
#define LR_OUT_Z_H 0x2D
#define LR_INT1_CFG 0x30
#define LR_INT1_SOURCE 0x31
#define LR_INT1_THS 0x32
#define LR_INT1_DURATION 0x33
#define LR_INT2_CFG 0x34
#define LR_INT2_SOURCE 0x35
#define LR_INT2_THS 0x36
#define LR_INT2_DURATION 0x37

// Full Scale Modes

#define LR_2G 0b00000000
#define LR_4G 0b00010000
#define LR_8G 0b00110000

#define FS0 4
#define FS1 5

// Power Modes

#define LR_POWER_OFF  0b00000000
#define LR_POWER_NORM 0b00100000
#define LR_POWER_LOW1 0b01000000
#define LR_POWER_LOW2 0b01100000
#define LR_POWER_LOW3 0b10000000

// Data Rates

#define LR_DATA_RATE_50   0b00000000
#define LR_DATA_RATE_100  0b00001000
#define LR_DATA_RATE_400  0b00010000
#define LR_DATA_RATE_1000 0b00011000


// Enable and disable channel.

#define LR_Z_ENABLE  0b00000100
#define LR_Z_DISABLE 0b00000000
#define LR_Y_ENABLE  0b00000010
#define LR_Y_DISABLE 0b00000000
#define LR_X_ENABLE  0b00000001
#define LR_X_DISABLE 0b00000000


