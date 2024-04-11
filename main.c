#include <mega16a.h>
#include <stdint.h>
#include <delay.h>

void main(void)
{
  uint8_t i;

  DDRC = 0xFF; // Все порты C на вывод

  while (1)
  {
    for (i = 1; i < 128; i = i << 1) // Возводим 2 в степень от 0 до 7 сдвигая бит на каждой итерации
    {
      PORTC = i;
      delay_ms(1000);
    }

    for (i = 128; i > 1; i = i >> 1) // Возводим 2 в степень от 7 до 0 сдвигая бит на каждой итерации
    {
      PORTC = i;
      delay_ms(1000);
    }
  }
}
