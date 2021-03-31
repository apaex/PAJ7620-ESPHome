# PAJ7620-ESPHome
PAJ7620 gesture sensor and ESPHome

Как добавить датчик жестов GY-PAJ7620 в Home Assistant через ESPHome:

1. Положить paj7620_.h в каталог, где лежит yaml-файл проекта
2. Добавить в yaml-файл 

esphome:
  includes:
    - paj7620_.h
  libraries:
    - "seeed-studio/Gesture PAJ7620"

3. Добавить в yaml-файл 

sensor:
- platform: custom
  lambda: |-
    auto paj7620 = new esphome::paj7620::PAJ7620();
    App.register_component(paj7620);
    return {paj7620->guesture_sensor};

  sensors:
    name: "PAJ7620"
    
4. Попробовать собрать.
5. Зайти в созданный каталог paj7620 и в файл platformio.ini добавить зависимость 

[common]
lib_deps =Wire

6. Ещё раз собрать. 

Всё, можно махать руками.
