#include <mega8.h>
#include <delay.h>

void CN_out(char port_n)
{
  if (port_n > 6)
    return;
  DDRC |= 1 << port_n;
}

void LED_C_blink(char port_n)
{
  if (port_n > 6)
    return;

  PORTC |= 1 << port_n;
}

void LED_C_off(char port_n)
{
  if (port_n > 6)
    return;

  PORTC &= ~(1 << port_n);
}

void main(void)
{
  CN_out(DDC0);
  while (1)
  {
    LED_C_blink(PORTC0);
    delay_ms(100);
    LED_C_off(PORTC0);
    delay_ms(100);
  }
}
