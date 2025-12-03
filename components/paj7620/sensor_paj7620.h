#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"


namespace esphome {
namespace paj7620 {

class PAJ7620 : public PollingComponent {
	public:
		PAJ7620();

		void setup() override;
      	void dump_config() override;

		float get_setup_priority() const override { return esphome::setup_priority::IO; }
		void update() override;

	protected:
		const char* guestureToString(uint8_t guesture);

	  	text_sensor::TextSensor *guesture_sensor{nullptr};
};

}}
