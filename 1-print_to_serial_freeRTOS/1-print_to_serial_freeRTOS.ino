//----------------------------------------------------------
// Print to Serial monitor using 2 tasks
//----------------------------------------------------------

// Include libs
#include <Arduino_FreeRTOS.h>

// Initialize tasks
void Task_Print1(void *param);
void Task_Print2(void *param);

// Initialize tasks handlers
TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Create tasks
  // xTaskCreate params:  Task, task name, task memory (don't worry about it for now), priority, task handler
  // Priority: The highest priority, it will run first
  xTaskCreate(Task_Print1, "Tasks1", 100, NULL, 1, &Task_Handle1);
  xTaskCreate(Task_Print2, "Tasks2", 100, NULL, 1, &Task_Handle2);

}

void loop() {
  // Don't put code right here
}

void Task_Print1(void *param){
  (void) param;

  // Infinite loop
  while(1){
    Serial.println("Task1");
    vTaskDelay(1000/portTICK_PERIOD_MS); // The Arduino will print to serial monitor each 1sec
  }
}

void Task_Print2(void *param){
  (void) param;

  // Infinite loop
  while(1){
    Serial.println("Task2");
    vTaskDelay(1000/portTICK_PERIOD_MS); // The Arduino will print to serial monitor each 1sec
  }
}
