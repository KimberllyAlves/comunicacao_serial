#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "hardware/timer.h"
#include "inc/matriz_rgb.h"
#include "inc/animacao_contagem.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define LED_BLUE 12 // LED 2 conectado ao pino 12
#define LED_GREEN 11 // LED 3 conectado ao pino 11
const uint button_A = 5; // Botão A = 5, Botão B = 6 
const uint button_B = 6; // Botão A = 5, Botão B = 6

static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
bool estado_led_verde = false;
bool estado_led_azul = false;

// Função de interrupção com debouncing
void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 200000) // 200 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento
        if (gpio == button_A) {
          estado_led_verde = !estado_led_verde;
          gpio_put(LED_GREEN, estado_led_verde);
          printf("Led verde %s \n ", estado_led_verde ? "LIGADO" : "DESLIGADO");
        }
        else if (gpio == button_B) {
          estado_led_azul = !estado_led_azul;
          gpio_put(LED_BLUE, estado_led_azul);
          printf("Led azul %s \n ", estado_led_azul ? "LIGADO" : "DESLIGADO");
            
        }
                             
    }
}

int main()
{
  // Inicializa entradas e saídas.
  stdio_init_all();

  // Inicializa matriz de LEDs NeoPixel.
  npInit(LED_PIN);

  // Inicializa os LEDs
  gpio_init(LED_GREEN);              // Inicializa o pino do LED
  gpio_set_dir(LED_GREEN, GPIO_OUT); // Configura o pino como saída
  gpio_init(LED_BLUE);              // Inicializa o pino do LED
  gpio_set_dir(LED_BLUE, GPIO_OUT); // Configura o pino como saída

  // Inicializa o botão
  gpio_init(button_A);
  gpio_set_dir(button_A, GPIO_IN); // Configura o pino como entrada
  gpio_pull_up(button_A);          // Habilita o pull-up interno

  gpio_init(button_B);
  gpio_set_dir(button_B, GPIO_IN); // Configura o pino como entrada
  gpio_pull_up(button_B);          // Habilita o pull-up interno

  // I2C Initialisation. Using it at 400Khz.
  i2c_init(I2C_PORT, 400 * 1000);

  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
  gpio_pull_up(I2C_SDA); // Pull up the data line
  gpio_pull_up(I2C_SCL); // Pull up the clock line
  ssd1306_t ssd; // Inicializa a estrutura do display
  ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
  ssd1306_config(&ssd); // Configura o display
  ssd1306_send_data(&ssd); // Envia os dados para o display

  // Limpa o display. O display inicia com todos os pixels apagados.
  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);

  // Configuração da interrupção com callback
  gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
  gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

  bool cor = true;

  char c[2];
  while (true)
  {
    cor = !cor;
    // Atualiza o conteúdo do display com animações
    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo

    //Impressão do estado do led verde
    if (estado_led_verde) ssd1306_draw_string(&ssd, "Verde ON", 8, 10); // Desenha uma string
    else ssd1306_draw_string(&ssd, "Verde OFF", 8, 10); // Desenha uma string

    //Impressão estado do led azul
    if (estado_led_azul) ssd1306_draw_string(&ssd, "Azul ON", 8, 25); // Desenha uma string
    else ssd1306_draw_string(&ssd, "Azul OFF", 8, 25); // Desenha uma string
    
    ssd1306_draw_string(&ssd, c, 15, 48); // Impressão dos caracteres digitados      
    ssd1306_send_data(&ssd); // Atualiza o display

    if (stdio_usb_connected()) {
      int get = getchar_timeout_us(1000000); //espera 100ms para receber um caractere
      if (get != PICO_ERROR_TIMEOUT && get != '\n') {
        c[0] = (char)get;
        c[1] = '\0'; //caractere nulo
        animacao_contador(c[0]); //apresentando matriz números
      }
    }

    sleep_ms(50);
  }
  return 0;
}