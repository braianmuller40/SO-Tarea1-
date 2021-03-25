#include <Arduino_FreeRTOS.h>
#include <semphr.h>

TaskHandle_t Tarea1_Handler;
TaskHandle_t Tarea2_Handler;
TaskHandle_t Tarea3_Handler;

SemaphoreHandle_t xSerialSemaphore;
int Cont;

void Tarea1(void *pvParameters);
void Tarea2(void *pvParameters);
void Tarea3(void *pvParameters);

void setup() {
  
  Serial.begin(9600);
  
  while (!Serial) {
    ;
  }

  if ( xSerialSemaphore == NULL ) 
  {
    xSerialSemaphore = xSemaphoreCreateMutex(); 
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) ); 
  }

  xTaskCreate(
    Tarea1
    ,  "Tarea1"  
    ,  128  
    ,  NULL
    ,  3  
    , &Tarea1_Handler);

  xTaskCreate(
    Tarea2
    ,  "Tarea2"
    ,  128  
    ,  NULL
    ,  2  
    , &Tarea2_Handler );
    
  xTaskCreate(
    Tarea3
    ,  "Tarea3"
    ,  128  
    ,  NULL
    ,  1  
    , &Tarea1_Handler);


}

void loop()
{
  
}

void Tarea1(void* pvParameters) 
{

  for (;;) 
  {Cont++;

    if(Cont == 10){
       vTaskSuspend(Tarea2_Handler); 
      }else if(Cont == 20){
        vTaskResume(Tarea2_Handler);
        }
  
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
           Serial.println(Cont);
          xSemaphoreGive( xSerialSemaphore );
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void Tarea2(void* pvParameters)
{

  for (;;)
  {
    int ValorA0 = analogRead(A0);
    
     if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {     
          Serial.println(ValorA0);
          xSemaphoreGive( xSerialSemaphore );
    } 
    vTaskDelay(3000/portTICK_PERIOD_MS);
  }
 }

void Tarea3(void* pvParameters)
{
  pinMode(13,OUTPUT);
  int ledState = LOW;
  
  for (;;)
  { 
   if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
  }
   digitalWrite(13 , ledState);
   vTaskDelay(2000/portTICK_PERIOD_MS);
   
   if(Cont >= 30){ 
     vTaskDelete(NULL);
     }
 }
}
