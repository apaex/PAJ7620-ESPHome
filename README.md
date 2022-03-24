# Подключаем датчик жестов PAJ7620 (GY-PAJ7620) в Home Assistant через ESPHome и ESP8266

1. Положить [paj7620_.h](https://github.com/apaex/PAJ7620-ESPHome/blob/main/paj7620_.h) в каталог, где лежит yaml-файл проекта
2. Добавить в yaml-файл 

```yaml
esphome:
  includes:
    - paj7620_.h
  libraries:
    - "Wire"
    - "seeed-studio/Gesture PAJ7620"
```

3. Добавить в yaml-файл 

```yaml
text_sensor:
- platform: custom
  lambda: |-
    auto paj7620 = new esphome::paj7620::PAJ7620();
    App.register_component(paj7620);
    return {paj7620->guesture_sensor};

  text_sensors:
    name: "PAJ7620"
    icon: mdi:hand-left
```
    
4. Собрать

5. Подключить всё, как в [этой статье](http://www.esp8266learning.com/paj7620-gesture-sensor-and-esp8266.php):

![Схема подключения](https://i2.wp.com/www.esp8266learning.com/wp-content/uploads/2018/09/esp8266-and-PAJ7620_bb.jpg?w=549 "Схема")

Всё, можно махать руками.)


## Множество состояний сенсора

* left
* right
* up
* down
* forward
* backward
* clockwise
* count_clockwise

## Пример автоматизации

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


