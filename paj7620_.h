#pragma once

#include "esphome.h"
#include <paj7620.h>

namespace esphome {
namespace paj7620 {

class PAJ7620 : public PollingComponent {
	private:
		const char* tag = "paj7620";
	public:		
		text_sensor::TextSensor *guesture_sensor = new text_sensor::TextSensor();

		PAJ7620() : PollingComponent(100) {}

		float get_setup_priority() const override { return esphome::setup_priority::IO; }

		void setup() override {
			
			uint8_t error = paj7620Init();
			
			if (error) 
				ESP_LOGE(tag, "Init ERROR, code: %d", error);
			else
				ESP_LOGD(tag, "Init OK");
		}

		void update() override {
			uint8_t data = 0;

			uint8_t error = paj7620ReadReg(0x43, 1, &data);
			if (error) {
				ESP_LOGE(tag, "Read ERROR, code: %d", error);
				return;
			}

			if (data) {
				const char* state = guestureToString(data);
				
				guesture_sensor->publish_state(state);
			}
		}
		
	protected:
		const char* guestureToString(uint8_t guesture)
		{
			switch (guesture) {
				case GES_UP_FLAG: 		return "up";
				case GES_DOWN_FLAG:		return "down";
				case GES_FORWARD_FLAG:		return "forward";
				case GES_BACKWARD_FLAG:		return "backward";
				case GES_RIGHT_FLAG:		return "right";
				case GES_LEFT_FLAG:		return "left";
				case GES_CLOCKWISE_FLAG:	return "clockwise";
				case GES_COUNT_CLOCKWISE_FLAG: 	return "count_clockwise";
				default: 			return "unknown";
			}		
		}
};

}}
