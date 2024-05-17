#define F_CPU 1000000UL
#include <mega16a.h>
#include <stdint.h>
#include <delay.h>

void init_ADC(void)
{
  ADMUX |= 1 << REFS0; // Опорное напряжение от внешнего источника питания на ножке AREF
  ADMUX &= ~(0x1F);    // Сравниваем ADC0 с внешним источником опорного напряжения

  ADCSRA |= (1 << ADPS1) | (1 << ADPS2); // Установка предделителя на 64 (125kHz)
  ADCSRA |= (1 << ADEN);                 // Включение АЦП
}

void main(void)
{
  DDRC = 0xFF;  // PORTC на вывод
  DDRD |= 0x03; // PORTD частично на вывод

  init_ADC();

  while (1)
  {
    while ((PINB & (1 << 0)) != 0)
      ;                  // Ожидание нажатия кнопки
    ADCSRA |= 1 << ADSC; // Запуск АЦП

    while ((ADCSRA & 1 << 0) != 0)
      ;                  // Ожидаем конец преобразовния
    ADCSRA |= 1 << ADIF; // Сброс флага готовности данных
    PORTC = ADCL;        // Запись младшего регистра
    PORTD = ADCH;        // Запись старшего регистра
  }
}
