#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
//#include "esphome/components/i2c/i2c.h"


namespace esphome {
namespace paj7620 {

class PAJ7620 : public text_sensor::TextSensor, PollingComponent/*, public i2c::I2CDevice*/ {
	public:
		PAJ7620();

  		void setup() override;
      	void dump_config() override;

		float get_setup_priority() const override;
		void update() override;

	protected:
		const char* gestureToString(uint8_t guesture);
};

}}
