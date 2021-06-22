# Logic-Analyzer
A Logic analyzer built around the MC9S08SH8 microprocessor.

The PCB was desgned with Kicad, and and firmware was written with Processor Expert.

An interrupt is triggered every time the signal line goes high, incrementing a counter. Each second this counter is read and reset, and the baud is calculated from that reading.

### TODO
Current version functions through use of interrupt pin, future version will use of a fast sample rate to handle higher baud rates better. A faster microprocessor will be required for this.

Future versions will also use the smallest bit in the received signal to calculate the baud, so almost any signal will be able to be used to calculate the baud rate(for example 00001000 or 11111110). This also ensures that the line being high or low for over one tick won't trip it up.
