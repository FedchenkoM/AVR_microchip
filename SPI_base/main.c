#include <mega8.h>
#include <stdint.h>
#include <delay.h>

#define SS PORTB2
#define MOSI PORTB3
#define SCK PORTB5

void SPI_init()
{
  DDRB |= (1 << SS) | (1 << MOSI) | (1 << SCK);
  PORTB |= (1 << SS);

  SPCR |= (1 << SPE);                // Разрешить SPI
  SPCR |= (1 << MSTR);               // режим Master
  SPCR |= (1 << SPR0) | (1 << SPR1); // Частота тактирования /128
}

void spi_send595(uint8_t data)
{
  uint8_t d = data;

  if (d > 9 | d < 1)
    return;

  while (d)
  {
    PORTB &= ~(1 << SS); // Начало отправки

    SPDR = d; // Запись значения в сдвиговый регистр МК

    while (!(SPSR & (1 << SPIF)))
      ; // Ждем флага прерывания SPI МК

    PORTB |= (1 << SS); // Конец отправки

    d -= 1;
    delay_ms(100);
  }
}

void main(void)
{
  SPI_init();
  spi_send595(9);
  while (1)
    ;
}
