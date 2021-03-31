#pragma once

#include "esphome.h"
#include <paj7620.h>

namespace esphome {
namespace paj7620 {

class PAJ7620 : public PollingComponent {
	private:
		const char* tag = "paj7620";
	public:		
	
		Sensor *guesture_sensor = new Sensor();

		PAJ7620() : PollingComponent(100) {}

		float get_setup_priority() const override { return esphome::setup_priority::IO; }

		void setup() override {
			
			uint8_t error = paj7620Init();			// initialize Paj7620 registers
			
			if (error) 
				ESP_LOGD(tag, "INIT ERROR, CODE: %d", error);
			else
				ESP_LOGD(tag, "INIT OK");
		}

		void update() override {
			uint8_t data = 0; // Read Bank_0_Reg_0x43/0x44 for gesture result.

			uint8_t error = paj7620ReadReg(0x43, 1, &data);
			if (error) {
				ESP_LOGD(tag, "READ ERROR, CODE: %d", error);
				return;
			}

			if (data) {
			   guesture_sensor->publish_state(data);
  			   ESP_LOGD(tag, guestureToString(data));
			}
		}
		
	protected:
		const char* guestureToString(uint8_t guesture)
		{
			switch (guesture) {
				case GES_UP_FLAG: 		return "GES_UP_FLAG";
				case GES_DOWN_FLAG:		return "GES_DOWN_FLAG";
				case GES_FORWARD_FLAG:	return "GES_FORWARD_FLAG";
				case GES_BACKWARD_FLAG:	return "GES_BACKWARD_FLAG";
				case GES_RIGHT_FLAG:	return "GES_RIGHT_FLAG";
				case GES_LEFT_FLAG:		return "GES_LEFT_FLAG";
				case GES_CLOCKWISE_FLAG:		return "GES_CLOCKWISE_FLAG";
				case GES_COUNT_CLOCKWISE_FLAG: 	return "GES_COUNT_CLOCKWISE_FLAG";
				default: return "";
			}		
		}
};

}}