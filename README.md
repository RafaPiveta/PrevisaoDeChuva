Algoritmo desenvolvido no Arduino IDE utilizando C++ durante a faculdade! 

O objetivo desse trabalho foi criar um aplicativo de previsão de chuva, o trabalho foi feito utilizando as tecnologias a seguir:
1. esp32 - Uma placa programável assim como o Arduino
2. Relé - Um switch ON / OFF que seria conectado a um circuito já existente
3. OpenWeatherMap API - Uma API cujo foi utilizada para obtenção de dados de previsão
4. Internet Of Things (Iot)

Ao final do projeto, a placa seria colocada juntamente a um sistema de coleta de água de chuva para que de acordo com a previsão, fosse possível fechar a valvúla
de água da Sanepar (Companhia de Água da região de Curitiba) e assim, econimizar dinheiro. Foram realizados testes em dias com previsão de chuva e dias sem previsão
de chuva e, ao final, o algoritmo identificou de maneira correta se iria ou não chover.

![image](https://github.com/RafaPiveta/PrevisaoDeChuva/assets/105398921/1ea8f140-bd55-4e49-b597-2d889db68d76)

![image](https://github.com/RafaPiveta/PrevisaoDeChuva/assets/105398921/4f145bc6-86a3-4069-aaae-aee4b913d237)

Para visualizar o projeto completo acesse meu LinkedIn: https://www.linkedin.com/in/rafael-olivare-piveta/

Para testá-lo:

1. Clone esse repositório usando: git clone git@github.com:RafaPiveta/PrevisaoDeChuva.git
2. Abra o Arduino IDE e baixe as bibliotecas a seguir:
3. - Arduino_JSON by Arduino
4. - ESP8266 and ESP32 OLED driver for SSD1306 displays by ThingPluse, Fabrice Weinberg
5. Selecione Ferramentas -> Placas e baixe a placa WEMOS LOLIN32
7. Tome certeza de que o esp32 está conectado na porta COM correta
8. Rode o código
