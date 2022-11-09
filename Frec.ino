// Configuracion de nucleos a utilizar 
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else 
  static const BaseType_t app_cpu = 1;
#endif

static const int led_pin = 2;

//Toggle
int rate = 1000; //ms valor default

// Usamos 2 tareas para parpadear el Led y leer la frecuencia

// Tarea para leer frecuencia
void frecuencia(void *parameters){
  char val;
  if(Serial.available() >0) {
    val=Serial.read();
    rate=String(val).toInt();
    }
}

//Tarea para parpadear el LED
void toggleLED(void *parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate / portTICK_PERIOD_MS);
  }
}
 
void setup() {
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("Modificador de frecuencia");
  Serial.println("Escriba la frecuencia deseada en ms ");

  //Task del Led
  xTaskCreatePinnedToCore(toggleLED,
                          "Tarea LED",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);
                          
 //Task frecuencia
  xTaskCreatePinnedToCore(frecuencia,
                          "Tarea LED",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);
}

void loop() {
}
