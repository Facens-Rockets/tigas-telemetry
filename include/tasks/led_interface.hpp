#ifndef INCLUDE_TASKS_LED_INTERFACE_H__
#define INCLUDE_TASKS_LED_INTERFACE_H__
#include "heltec.h"
#include "setup_tasks.hpp"

#define RED_RGB_PIN 36
#define GREEN_RGB_PIN 37
#define BLUE_RGB_PIN 38

void set_rgb_color(uint8_t color);

enum RGB_COLORS {
  RED,
  BLUE,
  GREEN,
  YELLOW
};

void led_interface_code(void* pvParameters) {
  bool any_error = false ;
  uint8_t bme_ok = 0;
  uint8_t sd_ok = 0;
  uint8_t modules_ok = 0;

  pinMode(RED_RGB_PIN, OUTPUT);
  pinMode(GREEN_RGB_PIN, OUTPUT);
  pinMode(BLUE_RGB_PIN, OUTPUT);

  while(true){
    xQueueReceive(led_queue_any_error, &any_error, 1);
    xQueueReceive(led_queue_bme_ok, &bme_ok, 1);
    xQueueReceive(led_queue_sd_ok, &sd_ok, 1);
    modules_ok = bme_ok + sd_ok;

    if (any_error) {
      set_rgb_color(RED);
    }

    switch (modules_ok) {
      case 2:
        set_rgb_color(GREEN);
        break;
      default:
        break;
    }

    vTaskDelay(1);
  }
}

void set_rgb_color(uint8_t color) {
  switch(color) {
    case RED:
      Serial.println("RED");
      digitalWrite(RED_RGB_PIN, HIGH);
      digitalWrite(BLUE_RGB_PIN, LOW);
      digitalWrite(GREEN_RGB_PIN, LOW);
      break;
    case GREEN:
      Serial.println("GREEN");
      digitalWrite(RED_RGB_PIN, LOW);
      digitalWrite(BLUE_RGB_PIN, LOW);
      digitalWrite(GREEN_RGB_PIN, HIGH);
      break;
    case BLUE:
      Serial.println("BLUE");
      digitalWrite(RED_RGB_PIN, LOW);
      digitalWrite(BLUE_RGB_PIN, HIGH);
      digitalWrite(GREEN_RGB_PIN, LOW);
      break;
    case YELLOW:
      Serial.println("YELLOW");
      digitalWrite(RED_RGB_PIN, HIGH);
      digitalWrite(BLUE_RGB_PIN, LOW);
      digitalWrite(GREEN_RGB_PIN, HIGH);
      break;
    
    default:
      break;
  }
}

#endif // INCLUDE_TASKS_LED_INTERFACE_H__
