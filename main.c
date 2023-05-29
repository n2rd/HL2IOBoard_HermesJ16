// This is firmware for the Hermes Lite 2 IO board designed by Jim Ahlstrom, N2ADR. It is
//   Copyright (c) 2022-2023 James C. Ahlstrom <jahlstr@gmail.com>.
//   It is licensed under the MIT license. See MIT.txt.

// This firmware outputs the band index on connector J4 and the FT817 band voltage on J4 pin 8.

#include "hl2ioboard.h"

// These are the major and minor version numbers for firmware.
uint8_t firmware_version_major=3;
uint8_t firmware_version_minor=0;

static uint64_t current_tx_freq;
#define MAX_FREQ_INDEX 23
#define MAX_HERMES_PIN 7

// Band  137k  500k  160  80  60  40  30  20  17  15  12  10   6   4   2  1.25  70cm  33cm  23cm  13cm  9cm  5cm  3cm
// Index    1     2    3   4   5   6   7   8   9  10  11  12  13  14  15    16    17    18    19    20   21   22   23

typedef int hermes_pin[MAX_FREQ_INDEX][MAX_HERMES_PIN];

hermes_pin transmit_pin = {
        {0,0,0,0,0,0,0},  //1 137K
        {0,0,0,0,0,0,0},  //2 500K
        {0,0,0,0,0,0,0},  //3 160m
        {0,0,0,0,0,0,0},  //4 80m
        {0,0,0,0,0,0,0},  //5 60m
        {0,0,0,0,0,0,0},  //6 40m
        {0,0,0,0,0,0,0},  //7 30m
        {0,0,0,0,0,0,0},  //8 20m
        {0,0,0,0,0,0,0},  //9 17m
        {0,0,0,0,0,0,0},  //10 15m
        {0,0,0,0,0,0,0},  //11 12m
        {0,0,0,0,0,0,0},  //12 10m
        {1,0,0,0,0,0,0},  //13 6m
        {0,0,0,0,0,0,0},  //14 4m
        {0,1,0,0,0,0,0},  //15 2m
        {0,0,1,0,0,0,0},  //16 1.25m
        {0,0,0,1,0,0,0},  //17 70cm
        {0,0,0,0,1,0,0},  //18 33cm
        {0,0,0,0,0,1,0},  //19 23cm
        {0,0,0,0,0,0,1},  //20 13mm
        {0,0,0,0,0,0,0},  //21 90mm
        {0,0,0,0,0,0,0},  //22 50mm
        {0,0,0,0,0,0,0}   //23 30mm
};

int main()
{
	int index;

	stdio_init_all();
	configure_pins(0, 1);
	configure_led_flasher();

	while (1) {	// wait for something to happen
		sleep_ms(1);
		if (current_tx_freq != new_tx_freq) {
			current_tx_freq = new_tx_freq;
			index = tx_freq_to_band(current_tx_freq);
			ft817_band_volts(index);
            gpio_put(GPIO16_Out1, transmit_pin[index-1][0]);
            gpio_put(GPIO19_Out2, transmit_pin[index-1][1]);
            gpio_put(GPIO20_Out3, transmit_pin[index-1][2]);
            gpio_put(GPIO11_Out4, transmit_pin[index-1][3]);
            gpio_put(GPIO10_Out5, transmit_pin[index-1][4]);
            gpio_put(GPIO22_Out6, transmit_pin[index-1][5]);
            gpio_put(GPIO09_Out7, transmit_pin[index-1][6]);
		}
	}
}
