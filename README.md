# Подключаем датчик жестов PAJ7620 (GY-PAJ7620) в Home Assistant через ESPHome и ESP8266

### Добавьте в yaml:

```yaml
external_components:
  - source: github://apaex/PAJ7620-ESPHome

sensor:
  - platform: paj7620
```
    
### Подключите, как [здесь](http://www.esp8266learning.com/paj7620-gesture-sensor-and-esp8266.php):


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


