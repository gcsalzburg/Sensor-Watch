#include <stdio.h>
#include <string.h>
#include "watch.h"

// data_byte is the byte we just read in
// index should be which byte are we doing, i.e. 0..8
static void render_display_byte(uint8_t data_byte, uint8_t index){

	// Work out where to start from for this data byte
	uint8_t pixel_index = index*8;
	
	for(uint8_t i=0; i<8; i++){
		// Check each bit to see if we should set it or not
		if((data_byte>>i) & 1){
			watch_set_pixel( (pixel_index/24), (pixel_index%24) );
		}

		// Increment pixel to set
		pixel_index++;
	}
}

// Grab the next 9 bytes from UART for a display update
static void read_in_uart_display_bytes(){

	// Clear everything first
	watch_clear_display();

	// Now fetch the next 9 bytes and render one by one 
	for(uint8_t i=0; i<9; i++){
		render_display_byte(watch_uart_getc(), i);
	}
}

// ////////////////////////////////////
// Button press/release handling below

char button_pressed = 0;
char button_direction = 0;

static void cb_mode_pressed(void) {
    button_pressed = 'M';
	 button_direction = watch_get_pin_level(BTN_MODE) ? 'p' : 'r';
}
static void cb_light_pressed(void) {
    button_pressed = 'L';
	 button_direction = watch_get_pin_level(BTN_LIGHT) ? 'p' : 'r';
}
static void cb_alarm_pressed(void) {
    button_pressed = 'A';
	 button_direction = watch_get_pin_level(BTN_ALARM) ? 'p' : 'r';
}

static void process_led(char led){
	switch(led){
		case 'R':
			watch_set_led_red();
			break;
		case 'G':
			watch_set_led_green();
			break;
		case 'Y':
			watch_set_led_yellow();
			break;
		case '0':
			watch_set_led_off();
			break;
	}
}

void app_init(void) {}

void app_wake_from_backup(void) {}

void app_setup(void) {
	watch_enable_display();
	watch_enable_buzzer();
	
	watch_enable_external_interrupts();
	watch_register_interrupt_callback(BTN_MODE, cb_mode_pressed, INTERRUPT_TRIGGER_BOTH);
	watch_register_interrupt_callback(BTN_LIGHT, cb_light_pressed, INTERRUPT_TRIGGER_BOTH);
	watch_register_interrupt_callback(BTN_ALARM, cb_alarm_pressed, INTERRUPT_TRIGGER_BOTH);

	watch_enable_uart(A2, A1, 19200);
}

void app_prepare_for_standby(void) {}
void app_wake_from_standby(void) {}


bool app_loop(void) {

	// ///////////////////////////////////////////
	// TX: Check for and send out msg for button presses

	char send_buffer[5];
	memset(send_buffer, 0, sizeof send_buffer);

	if (button_pressed) {
		send_buffer[0] = 'b';
		send_buffer[1] = button_pressed;
		send_buffer[2] = button_direction;
		send_buffer[3] = '.';
		watch_uart_puts(send_buffer);
		button_pressed = 0;
		button_direction = 0;
	}

	// ///////////////////////////////////////////
	// RX: Handle incoming messages

	char char_received = watch_uart_getc();
	if (char_received) {
		switch (char_received) {

			case 'b':

				// Start / stop buzzer effects
				// TODO...
				break;

			case 'l':

				// Set one of the LEDs to something
				process_led(watch_uart_getc());
				break;

			case 'd':

				// receive a display update?
				read_in_uart_display_bytes();
				break;

			default:

				// Discard anything else
				break;
		}
	}

   return false;
}
