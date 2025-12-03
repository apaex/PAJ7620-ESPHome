# Connecting the PAJ7620 (GY-PAJ7620) gesture sensor to the Home Assistant via ESPHome and ESP8266

### Add it to yaml:

```yaml
external_components:
  - source: github://apaex/PAJ7620-ESPHome

text_sensor:
  - platform: paj7620
    name: "My gesture sensor"
```

### Connect like [here](http://www.esp8266learning.com/paj7620-gesture-sensor-and-esp8266.php):

![Connection diagram](https://i2.wp.com/www.esp8266learning.com/wp-content/uploads/2018/09/esp8266-and-PAJ7620_bb.jpg?w=549 "Connection diagram")

That's it, you can wave your hands.)

## List of sensor states

* left
* right
* up
* down
* forward
* backward
* clockwise
* count_clockwise

## Example of HA automation

```yaml
    - alias: paj7620-up
      trigger:
        - platform: state
          entity_id: sensor.paj7620
          to: 'up'
      condition:
      action:
        - service: switch.turn_on
          entity_id:
            - switch.xxxx

    - alias: paj7620-down
      trigger:
        - platform: state
          entity_id: sensor.paj7620
          to: 'down'
      condition:
      action:
        - service: switch.turn_off
          entity_id:
            - switch.xxxx
```


