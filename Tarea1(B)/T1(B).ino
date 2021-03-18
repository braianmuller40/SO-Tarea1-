#include <Arduino_FreeRTOS.h>
 int p =10;
// Initialize tasks
void LED(void *param);
void PRINT(void *param);

// Initialize tasks handlers
TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;

void setup() {
  // put your setup code here, to run once:
  pinMode(p,INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  // Create tasks
  // xTaskCreate params:  Task, task name, task memory (don't worry about it for now), priority, task handler
  // Priority: The highest priority, it will run first
  xTaskCreate(LED, "Tasks1", 100, NULL, 1, &Task_Handle1);
  xTaskCreate(PRINT, "Tasks2", 100, NULL, 1, &Task_Handle2);

}

void loop() {
  // Don't put code right here
}

void LED(void *param){
  (void) param;
 
  
  while(1){
    if(digitalRead(p) == HIGH){
    digitalWrite(13, LOW); // Turn off led
    while(digitalRead(p) == HIGH);
  }else digitalWrite(13, HIGH); // Turn on led
  }
}

void PRINT(void *param){
  (void) param;

  // Infinite loop
  while(1){
    Serial.println("PINTLN");
    vTaskDelay(1000/portTICK_PERIOD_MS); // The Arduino will print to serial monitor each 1sec
  }
}
