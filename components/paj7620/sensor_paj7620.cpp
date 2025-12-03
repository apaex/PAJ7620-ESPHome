#include "sensor_paj7620.h"
#include <arduino.h>
#include "paj7620.h"
#include "esphome/core/log.h"

namespace esphome {
namespace paj7620 {

static const char *const TAG = "paj7620";

PAJ7620::PAJ7620() : PollingComponent(100) {}

void PAJ7620::setup()
{
	uint8_t error = paj7620Init();

	if (error)
		ESP_LOGE(tag, "Init ERROR, code: %d", error);
	else
		ESP_LOGD(tag, "Init OK");
}


void PAJ7620::update() {
	uint8_t data = 0;

	uint8_t error = paj7620ReadReg(0x43, 1, &data);
	if (error) {
		ESP_LOGE(tag, "Read ERROR, code: %d", error);
		return;
	}

	if (data) {
		const char* state = guestureToString(data);

		guesture_sensor->publish_state(state);
		//ESP_LOGD(tag, state);
	}
}

void PAJ7620::dump_config() {
    ESP_LOGCONFIG(TAG, "PAJ7620:");
    //LOG_PIN("  Conf X:  ", this->conf_x_);
}

const char* PAJ7620::guestureToString(uint8_t guesture)
{
	switch (guesture) {
		case GES_UP_FLAG: 				return "up";
		case GES_DOWN_FLAG:				return "down";
		case GES_FORWARD_FLAG:			return "forward";
		case GES_BACKWARD_FLAG:			return "backward";
		case GES_RIGHT_FLAG:			return "right";
		case GES_LEFT_FLAG:				return "left";
		case GES_CLOCKWISE_FLAG:		return "clockwise";
		case GES_COUNT_CLOCKWISE_FLAG: 	return "count_clockwise";
		default: 						return "unknown";
	}
}

}}
