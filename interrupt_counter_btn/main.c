#include <mega16a.h>
#include <delay.h>
#include <stdint.h>

#define ANOD0 7 //  Анод первого разряда 7seg
#define ANOD1 6 //  Анод второго разряда 7seg
#define LED 7

uint8_t fire = 0;

void output_n(uint8_t n)
{
  uint8_t i;

  DDRA |= 0x0F;                        // 4 младших бита PORTA на вывод 0000 1111
  DDRD |= (1 << ANOD0) | (1 << ANOD1); // Оба разряда 7seg на выход

  for (i = 0; i < 20; i++) // 20 Магическое число, нужно для того чтобы индикация менялась не быстро
  {
    PORTD |= 1 << ANOD0; // Вкл анод младшего разряда
    PORTA = n % 10;      // Младший разряд числа
    delay_ms(2);
    PORTD &= ~(1 << ANOD0); // Выкл анод младшего разряда
    PORTD |= 1 << ANOD1;    // Вкл анод старшего разряда
    PORTA = n / 10;         // Старший разряд числа
    delay_ms(2);
    PORTD &= ~(1 << ANOD1); // Выкл анод старшего разряда
  }
}

interrupt[EXT_INT0] void isr_INT0(void) // Ф-ция обслуживания прерывания
{
  if (fire)
  {
    PORTB |= 1 << LED;
  }
  else
  {
    PORTB &= ~(1 << LED);
  }

  fire = !fire;
}

void main(void)
{

  uint8_t k = 0;

  DDRB |= 1 << LED;                     // 7 пин PORTB на вывод
  MCUCR |= (1 << ISC00) | (1 << ISC01); // Прерывание по фронту
  GICR |= 1 << INT0;                    // Разрешить прерывание INT0
#asm("sei");                            // Глобальное разрешение прерываний

  for (; k < 100; k++)
  {
    output_n(k);
  }
}
