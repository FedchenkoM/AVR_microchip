#define F_CPU 1000000UL
#include <mega8.h>
#include <delay.h>

void setup_7seg(void)
{
  DDRD |= 0b00001111;
}

void setup_7seg_ctrl()
{
  DDRB |= 0b00000000;
  PORTB |= 0b00000011;
}

void set_n(int n)
{
  delay_ms(50); // Костыль от дребезга

  if ((n > 9) | (n < 0))
  {
    return;
  }

  PORTD = n;
}

void main(void)
{
  int n = 0;

  setup_7seg();
  setup_7seg_ctrl();
  while (1)
  {
    if (PINB == 0b00000010)
    {
      n++;

      if (n > 9)
      {
        n = 0;
      }

      set_n(n);
    }
    else if (PINB == 0b00000001)
    {
      n--;

      if (n < 0)
      {
        n = 9;
      }

      set_n(n);
    }
  }
}
