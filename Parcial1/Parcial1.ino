#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t xSerialSemaphore;

void Tarea1();
void Tarea2();
void Tarea3();

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
    ,  2  
    ,  NULL );

  xTaskCreate(
    Tarea2
    ,  "Tarea2"
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );
    
  xTaskCreate(
    Tarea3
    ,  "Tarea3"
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );


}

void loop()
{
  
}

void Tarea1() 
{
int Cont;

  for (;;) 
  {
  Cont++;
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
           Serial.println(Cont);
          xSemaphoreGive( xSerialSemaphore );
    } 
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void Tarea2()
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

void Tarea3()
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
 }
}
