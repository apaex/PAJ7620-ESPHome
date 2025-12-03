#include "sensor_paj7620.h"
#include "paj7620.h"
#include "esphome/core/log.h"
#include <cinttypes>

namespace esphome {
namespace paj7620 {

const char *const TAG = "paj7620";

PAJ7620::PAJ7620() : PollingComponent(100) {}

void PAJ7620::setup()
{
	uint8_t error = paj7620Init();

	if (error)
	{
		ESP_LOGE(TAG, "Init ERROR, code: %d", error);
		this->mark_failed();
		return;
	}

	ESP_LOGD(TAG, "Init OK");
}


void PAJ7620::update() {
	uint8_t data = 0;

	uint8_t error = paj7620ReadReg(0x43, 1, &data);
	if (error) {
		ESP_LOGE(TAG, "Read ERROR, code: %d", error);
		return;
	}

	if (data == state_)
		return;

	state_ = data;
	const char* text_state = gestureToString(state_);
	this->publish_state(text_state);
	ESP_LOGD(TAG, "Get gesture: '%s'", text_state);
}

float PAJ7620::get_setup_priority() const { return setup_priority::DATA; }

void PAJ7620::dump_config() {
    ESP_LOGCONFIG(TAG, "PAJ7620:");
//    LOG_I2C_DEVICE(this);
	if (this->is_failed()) {
		ESP_LOGE(TAG, ESP_LOG_MSG_COMM_FAIL);
	}
	LOG_TEXT_SENSOR("  ", "PAJ7620" , this);
  	LOG_UPDATE_INTERVAL(this);
}

const char* PAJ7620::gestureToString(uint8_t guesture)
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
		case 0: 						return "none";
		default: 						return "unknown";
	}
}

}}
