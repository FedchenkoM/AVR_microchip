- _Исходный код написан в IDE CodeVisionAVR v. 4.02 Evaluation_
- _Для визуализации использовался Proteus 8_
- _Микроконтроллер Atmega 16A_

В программе модулируется ШИМ
На 3 выводе **PORTB** изначально логическая "1". В цикле на каждой итерации модулируется скважность равная "i"
Далее при совпадении **TCNT0** c **OCR0** вывод **OC0** сбрасывается в ноль.
![Screen Recording](https://github.com/FedchenkoM/AVR_microchip/assets/73774460/ada5d059-2076-4865-b983-75e879014649)
