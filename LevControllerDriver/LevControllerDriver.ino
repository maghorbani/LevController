/*
add the following function to the file:
{Arduino Install DIR}/hardware/arduino/avr/cores/arduino/HardwareSerial.h

inline bool _dataAvailable() {return _rx_buffer_head != _rx_buffer_tail; }
inline byte _peekData() { return _rx_buffer[_rx_buffer_tail]; }
inline void _discardByte() { _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE; }
*/

#include <avr/sleep.h>
#include <avr/power.h>

#define N_PORTS 10
#define N_DIVS 10

//ports A C L B K F H D G J

#define APPLY_COMMAND 0b00000000

#define ALTER_GPIO(pointer, d)      \
  PORTA = pointer[d * N_PORTS + 0]; \
  PORTC = pointer[d * N_PORTS + 1]; \
  PORTL = pointer[d * N_PORTS + 2]; \
  PORTB = pointer[d * N_PORTS + 3]; \
  PORTK = pointer[d * N_PORTS + 4]; \
  PORTF = pointer[d * N_PORTS + 5]; \
  PORTH = pointer[d * N_PORTS + 6]; \
  PORTD = pointer[d * N_PORTS + 7]; \
  PORTG = pointer[d * N_PORTS + 8]; \
  PORTJ = pointer[d * N_PORTS + 9]

static byte bufferA[N_DIVS * N_PORTS];
static byte bufferB[N_DIVS * N_PORTS];

void setup()
{
  //set as output ports A C L B K F H D G J
  DDRA = DDRC = DDRL = DDRB = DDRK = DDRF = DDRH = DDRD = DDRG = DDRJ = 0xFF;
  //low signal on all of them
  PORTA = PORTC = PORTL = PORTB = PORTK = PORTF = PORTH = PORTD = PORTG = PORTJ = 0x00;

  //initial value
  for (int i = 0; i < (N_DIVS * N_PORTS); ++i)
  {
    bufferA[i] = 0xFF;
    bufferB[i] = 0;
  }

  // generate a sync signal of 40khz in pin 2
  pinMode(2, OUTPUT);
  noInterrupts();                                 // disable all interrupts
  TCCR3A = bit(WGM10) | bit(WGM11) | bit(COM1B1); // fast PWM, clear OC1B on compare
  TCCR3B = bit(WGM12) | bit(WGM13) | bit(CS10);   // fast PWM, no prescaler
  OCR3A = (F_CPU / 40000L) - 5;                   //should only be -1 but fine tunning with the scope determined that -5 gave 40kHz almost exactly
  OCR3B = (F_CPU / 40000L) / 2;
  interrupts(); // enable all interrupts

  //sync in signal at pin 3
  pinMode(3, INPUT_PULLUP); //please connect pin3 to pin 2

  // disable everything that we do not need
  ADCSRA = 0; // ADC
  power_adc_disable();
  power_spi_disable();
  power_twi_disable();
  power_timer0_disable();
  power_usart1_disable();
  power_usart2_disable();

  Serial.begin(115200);

  byte bReceived = 0;
  bool byteReady = false;
  bool isSwitch = false;
  bool isSendingData = false;
  int writtingIndex = 0;

  bool emittingA = true;
  byte *emittingPointer = &bufferA[0];
  byte *readingPointer = &bufferB[0];

LOOP:
  while (PINE & 0b00100000)
    ; //wait for pin 3 (E5 Sync In) to go low

  ALTER_GPIO(emittingPointer, 0);
  byteReady = Serial._dataAvailable();
  ALTER_GPIO(emittingPointer, 1);
  bReceived = Serial._peekData();
  ALTER_GPIO(emittingPointer, 2);
  isSwitch = bReceived == APPLY_COMMAND;
  ALTER_GPIO(emittingPointer, 3);
  isSendingData = (bReceived & 0b00001111) == 1;
  ALTER_GPIO(emittingPointer, 4);
  ALTER_GPIO(emittingPointer, 5);
  ALTER_GPIO(emittingPointer, 6);
  ALTER_GPIO(emittingPointer, 7);
  ALTER_GPIO(emittingPointer, 8);
  ALTER_GPIO(emittingPointer, 9);

  if (byteReady)
  {
    if (isSwitch)
    {
      emittingA = !emittingA;
      if (emittingA)
      {
        emittingPointer = &bufferA[0];
        readingPointer = &bufferB[0];
      }
      else
      {
        emittingPointer = &bufferB[0];
        readingPointer = &bufferA[0];
      }
      writtingIndex = 0;
    }
    else if (isSendingData)
    {
      if (writtingIndex % 2 == 0)
      {
        readingPointer[writtingIndex / 2] = bReceived & 0xF0;
      }
      else
      {
        readingPointer[writtingIndex / 2] |= (bReceived >> 4);
      }
      ++writtingIndex;
    }
    Serial._discardByte();
  }

  goto LOOP;
}

void loop() {}
