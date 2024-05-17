#define F_CPU 1000000UL
#include <mega8.h>
#include <delay.h>

void garland_setup(void)
{
  DDRD |= 0xFF;
  DDRC |= 0;
  PORTD |= 0;
  PORTC |= 0b1111111;
}

void LED_full_light(void)
{
  PORTD |= 0b11111111;
}

void LED_snake(void)
{
  int cur = 1;
  PORTD &= ~(0b11111111);
  while (cur <= 128)
  {
    PORTD = cur;
    delay_ms(100);
    cur = cur << 1;
  }
}

void main(void)
{
  garland_setup();
  while (1)
  {
    if (PINC == 0b1111100)
    {
      PORTD &= ~(0b11111111);
    }
    else if (PINC == 0b1111110)
    {
      LED_full_light();
    }
    else if (PINC == 0b1111101)
    {
      while (PINC == 0b1111101)
      {
        LED_snake();
      }
    }
    else
    {
      PORTD &= ~(0b11111111);
    }
  }
}
