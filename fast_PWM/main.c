#define F_CPU 1000000UL
#include <mega16a.h>
#include <stdint.h>
#include <delay.h>

#define PWMQ 3

void init_PWM(void)
{
  DDRB |= 1 << PWMQ;                    // PORTB на вывод
  TCCR0 |= (1 << WGM00) | (1 << WGM01); // Установка режима fast PWM
  TCCR0 |= (1 << COM01);                // Установка прямого сигнала PWM
  TCCR0 |= (1 << CS00);                 // Установка частоты без предделителя
}

void main(void)
{
  uint8_t i = 4;

  init_PWM();

  while (1)
  {
    for (; i < 250; i++)
    {
      OCR0 = i;
      delay_ms(2);
    }
    for (; i > 4; i--)
    {
      OCR0 = i;
      delay_ms(2);
    }
  }
}
