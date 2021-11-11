# Bare Metal Training 03:  Timers and PWM

Requirements:

1. Need to implement PWM signal generator.
2. Time4 need to be used (this is mandatory).
3. STM32F407 need to be switched for external clock (HSE).
4. 2 buttons would be used to set signal frequency (up and down; +/- 5 kHz step).
5. 2 buttons would be used to set duty cycle (+/- 5% step each button press).
6. Middle button would be used to select signal output (PD15, PD14, PD13, PD12 or no output (disable case)). Cyclic selection scheme.
7. Need to capture signal trace from for outputs with help of signal analyzer to show that all functionality is working fine.