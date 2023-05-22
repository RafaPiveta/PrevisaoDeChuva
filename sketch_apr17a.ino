// Aluno: Rafael Olivare Piveta
// Curso: Engenharia da Computação

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "SSD1306.h" // Biblioteca para o display OLED incorporado ao ESP32

const char* ssid = "Sua WiFi";
const char* password = "Sua senha da WiFi";

SSD1306 display(0x3c, 5, 4); // Endereçamento do display no barramento serial I2C

String openWeatherMapApiKey = "Sua chave da OpenWeather"; 

// Cidade e país
String city = "Curitiba";
String countryCode = "BR";

// Intervalo de tempo entre as consultas (em milissegundos)
unsigned long timerDelay = 10000; // 10 segundos

//Porta ligada ao pino IN1 do modulo
int porta_rele = "Porta do seu Relé";

String jsonBuffer;

void setup() {
  Serial.begin(115200);
  display.init(); // Inicializa o display
  display.clear(); // Limpa o display

  WiFi.begin(ssid, password);
  Serial.println("Conectando...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado à rede WiFi com endereço IP: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer configurado para 10 segundos (variável timerDelay), levará 10 segundos para publicar a primeira leitura.");

  //Define pino do relé como saída
  pinMode(porta_rele, OUTPUT); 
}

void loop() {
  // Faz uma solicitação HTTP GET
  static unsigned long lastTime = 0;
  if ((millis() - lastTime) > timerDelay) {
    // Verificar o status da conexão WiFi
    if(WiFi.status() == WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
  
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Falha ao analisar o objeto JSON!");
        return;
      }
      
      // Pega a temperatura pela OpenWeatherMap API
      int temperatura_Kelvin = myObject["main"]["temp"];
      Serial.print("Temperatura: ");
      Serial.print(temperatura_Kelvin - 273.15);
      Serial.println("°C");
      double temperatura_Celsius = temperatura_Kelvin - 273.15;
      // Pega a umidade pela OpenWeatherMap API
      int umidade = myObject["main"]["humidity"];
      Serial.print("Umidade: ");
      Serial.print(umidade);
      Serial.println("%");      
      // Pega a pressão atmosférica pela OpenWeatherMap API
      int pressao = myObject["main"]["pressure"];
      Serial.print("Pressão: ");
      Serial.print(pressao);
      Serial.println("hPa"); // Unidade comum de pressão (Hecta Pascal)
      

      // Diz se irá chover com base numa humidade alta e uma pressão mínima
      if (umidade > 80 && pressao < 1018) { // A pressão em Curitiba varia entre 1018hPa e 1028hPa
        Serial.println("Chuva certa");
        digitalWrite(porta_rele, HIGH);  //Liga o relé
        delay(2000);

        // Mostra no display do esp32
        display.clear();
        display.drawRect(1, 1, 127, 60);
        display.setFont(ArialMT_Plain_10);
        display.drawString(5, 5, "Temperatura: "+(String)temperatura_Celsius+" °C");
        display.drawString(5, 19, "Umidade: "+(String)umidade+" %");
        display.drawString(5, 33, "Pressão: "+(String)pressao+" hPa");
        display.drawString(5, 47, "Chuva certa, Relé ON!");
        display.flipScreenVertically();
        display.display();
        delay(500);  
      } 
      else {
        Serial.println("Não irá chover");
        digitalWrite(porta_rele, LOW);  //Desliga o relé
        delay(2000);

        // Mostra no display do esp32
        display.clear();
        display.drawRect(1, 1, 127, 60);
        display.setFont(ArialMT_Plain_10);
        display.drawString(5, 5, "Temperatura: "+(String)temperatura_Celsius+" °C");
        display.drawString(5, 19, "Umidade: "+(String)umidade+" %");
        display.drawString(5, 33, "Pressão: "+(String)pressao+" hPa");
        display.drawString(5, 47, "Não irá chover, relé OFF!");
        display.flipScreenVertically();
        display.display();
        delay(500);  
      }

      // Função interna do esp32 para contar os milisegundos
      lastTime = millis();
    }
    else {
      digitalWrite(porta_rele, LOW);  //Desliga o relé
      delay(2000);

      // Mostra no display do esp32 que o WiFi não está conectado
      Serial.println("Erro de conexão WiFi.");
      display.clear();
      display.drawRect(1, 1, 127, 60);
      display.setFont(ArialMT_Plain_10);
      display.drawString(5, 5, "WiFi não conectado!");
      display.flipScreenVertically();
      display.display();
      delay(500);  
      }
    }
  }

  // Função para fazer uma solicitação HTTP GET
  String httpGETRequest(const char* serverName) {
  HTTPClient httpClient;
  httpClient.begin(serverName);
  int httpResponseCode = httpClient.GET();

  String payload = "";
  if (httpResponseCode > 0) {
  payload = httpClient.getString();
  }

  httpClient.end();
  return payload;
}
