#include <mega8.h>

void main(void)
{
  DDRD |= (1 << 4);
  DDRB = 0b11111111;
  PORTB = 0;

  TCCR0 |= (1 << CS01) | (1 << CS02); // TC0 реагирует на спад
  TCNT0 = 0;                          // Обнуляем счетчик

  while (1)
  {
    PORTB = TCNT0; // Прост пишем в PORTD значение TCNT0 и смотрим на диоды
  }
}
