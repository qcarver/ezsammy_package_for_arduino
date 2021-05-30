/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "variant.h"
#include "Arduino.h"

const PinDescription g_APinDescription[] = {

/* 
TCC and TC are timers
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 | 00         | D0               |  PA22  |                 |  *06   |     |     | X10 |     |   3/00  |   5/00  |* TC4/0 | TCC0/4 |          | GCLK_IO6 |
 | 01         | D1               |  PA23  |                 |  *07   |     |     | X11 |     |   3/01  |   5/01  |* TC4/1 | TCC0/5 | USB/SOF  | GCLK_IO7 |
 | 02         | D2               |  PA10  |                 |   10   | *18 |     | X02 |     |   0/02  |   2/02  |*TCC1/0 | TCC0/2 | I2S/SCK0 | GCLK_IO4 |
 | 03         | D3               |  PA11  |                 |   11   | *19 |     | X03 |     |   0/03  |   2/03  |*TCC1/1 | TCC0/3 | I2S/FS0  | GCLK_IO5 |
 | 04         | D4               |  PB10  |                 |  *10   |     |     |     |     |         |   4/02  |* TC5/0 | TCC0/4 | I2S/MCK1 | GCLK_IO4 |
 | 05         | D5               |  PB11  |                 |  *11   |     |     |     |     |         |   4/03  |* TC5/1 | TCC0/5 | I2S/SCK1 | GCLK_IO5 |
 | 06         | D6               |  PA20  | LED_BUILTIN     |  *04   |     |     | X08 |     |   5/02  |   3/02  |        |*TCC0/6 | I2S/SCK0 | GCLK_IO4 |
 | 07         | D7               |  PA21  |                 |  *05   |     |     | X09 |     |   5/03  |   3/03  |        |*TCC0/7 | I2S/FS0  | GCLK_IO5 |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 */
  { PORTA, 22, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM4_CH0,   TC4_CH0,      EXTERNAL_INT_6    },
  { PORTA, 23, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM4_CH1,   TC4_CH1,      EXTERNAL_INT_7    },
  { PORTA, 10, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel18,  PWM1_CH0,   TCC1_CH0,     EXTERNAL_INT_NONE },
  { PORTA, 11, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel19,  PWM1_CH1,   TCC1_CH1,     EXTERNAL_INT_NONE },
  { PORTB, 10, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM5_CH0,   TC5_CH0,      EXTERNAL_INT_10   },
  { PORTB, 11, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM5_CH1,   TC5_CH1,      EXTERNAL_INT_11   },
  { PORTA, 20, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH6,   TCC0_CH6,     EXTERNAL_INT_4    },
  { PORTA, 21, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH7,   TCC0_CH7,     EXTERNAL_INT_5    },

/*
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 |            |       SPI        |        |                 |        |     |     |     |     |         |         |        |        |          |          |
 | 08         | MOSI             |  PA16  |                 |  *00   |     |     | X04 |     |  *1/00  |   3/00  |*TCC2/0 | TCC0/6 |          | GCLK_IO2 |
 | 09         | SCK              |  PA17  |                 |  *01   |     |     | X05 |     |  *1/01  |   3/01  | TCC2/1 | TCC0/7 |          | GCLK_IO3 |
 | 10         | MISO             |  PA19  |                 |   03   |     |     | X07 |     |  *1/03  |   3/03  |* TC3/1 | TCC0/3 | I2S/SD0  | AC/CMP1  |
 +------------+------------------+--------+-----------------+--------------------+-----+-----+---------+---------+--------+--------+----------+----------+
 |            |       Wire       |        |                 |        |     |     |     |     |         |         |        |        |          |          |
 | 11         | SDA              |  PA08  |                 |   NMI  | *16 |     | X00 |     |  *0/00  |   2/00  | TCC0/0 | TCC1/2 | I2S/SD1  |          |
 | 12         | SCL              |  PA09  |                 |   09   | *17 |     | X01 |     |  *0/01  |   2/01  | TCC0/1 | TCC1/3 | I2S/MCK0 |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 |            |      Serial1     |        |                 |        |     |     |     |     |         |         |        |        |          |          |
 | 13         | RX               |  PB23  |                 |   07   |     |     |     |     |         |  *5/03  |        |        |          | GCLK_IO1 |
 | 14         | TX               |  PB22  |                 |   06   |     |     |     |     |         |  *5/02  |        |        |          | GCLK_IO0 |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 */
                                                                                                                                               // DIPO=3 DOPO=0
  { PORTA, 16, PIO_SERCOM,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM2_CH0,   TCC2_CH0,     EXTERNAL_INT_0    }, // MOSI: SERCOM1/PAD[0]
  { PORTA, 17, PIO_SERCOM,  (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1    }, // SCK:  SERCOM1/PAD[1]
  { PORTA, 19, PIO_SERCOM,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM3_CH1,   TC3_CH1,      EXTERNAL_INT_NONE }, // MISO: SERCOM1/PAD[3]

                                                                                                                                               // PINOUT=0
  { PORTA,  8, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL                            ), ADC_Channel16,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NMI  }, // SDA:  SERCOM2/PAD[0]
  { PORTA,  9, PIO_SERCOM_ALT,  (PIN_ATTR_DIGITAL                            ), ADC_Channel17,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SCL:  SERCOM2/PAD[1]

                                                                                                                                               // RXPO=3 TXPO=1
  { PORTB, 23, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL                             ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // RX:   SERCOM5/PAD[3]
  { PORTB, 22, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL                             ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // TX:   SERCOM5/PAD[2]


/*
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 | 15         | A0 / DAC0        |  PA02  |                 |   02   | *00 |     | Y00 | OUT |         |         |        |        |          |          |
 | 16         | A1               |  PB02  |                 |  *02   | *10 |     | Y08 |     |         |   5/00  |        |        |          |          |
 | 17         | A2               |  PB03  |                 |  *03   | *11 |     | Y09 |     |         |   5/01  |        |        |          |          |
 | 18         | A3               |  PA04  |                 |   04   | *04 |  00 | Y02 |     |         |   0/00  |*TCC0/0 |        |          |          |
 | 19         | A4               |  PA05  |                 |   05   | *05 |  01 | Y03 |     |         |   0/01  |*TCC0/1 |        |          |          |
 | 20         | A5               |  PA06  |                 |   06   | *06 |  02 | Y04 |     |         |   0/02  | TCC1/0 |        |          |          |
 | 21         | A6               |  PA07  |                 |   07   | *07 |  03 | Y05 |     |         |   0/03  | TCC1/1 |        | I2S/SD0  |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 */
  { PORTA,  2, PIO_ANALOG,  (PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG /*DAC*/        ), ADC_Channel0,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTB,  2, PIO_ANALOG,  (PIN_ATTR_DIGITAL                                ), ADC_Channel10,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2    },
  { PORTB,  3, PIO_ANALOG,  (PIN_ATTR_DIGITAL                                ), ADC_Channel11,  NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3    },
  { PORTA,  4, PIO_ANALOG,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel4,   PWM0_CH0,   TCC0_CH0,     EXTERNAL_INT_NONE },
  { PORTA,  5, PIO_ANALOG,  (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), ADC_Channel5,   PWM0_CH1,   TCC0_CH1,     EXTERNAL_INT_NONE },
  { PORTA,  6, PIO_ANALOG,  (PIN_ATTR_DIGITAL                                ), ADC_Channel6,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  7, PIO_ANALOG,  (PIN_ATTR_DIGITAL                                ), ADC_Channel7,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

/*
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 |            |       USB        |        |                 |        |     |     |     |     |         |         |        |        |          |          |
 | 22         |                  |  PA24  | USB N           |   12   |     |     |     |     |   3/02  |   5/02  |  TC5/0 | TCC1/2 | USB/DM   |          |
 | 23         |                  |  PA25  | USB P           |   13   |     |     |     |     |   3/03  |   5/03  |  TC5/1 | TCC1/3 | USB/DP   |          |
 | 24         |                  |  PA18  | USB ID          |   02   |     |     | X06 |     |   1/02  |   3/02  |  TC3/0 | TCC0/2 |          | AC/CMP0  |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 | 25         | AREF             |  PA03  |                 |   03   |  01 |     | Y01 |     |         |         |        |        |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 */
  { PORTA, 24, PIO_COM,     (PIN_ATTR_NONE                                   ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DM
  { PORTA, 25, PIO_COM,     (PIN_ATTR_NONE                                   ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DP
  { PORTA, 18, PIO_DIGITAL, (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  { PORTA,  3, PIO_DIGITAL, (PIN_ATTR_DIGITAL                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // DAC/VREFP

/*
 +------------+------------------+--------+-----------------+--------+-----------------------+---------+---------+--------+--------+----------+----------+
 | Pin number |  MKR  Board pin  |  PIN   | Notes           | Peri.A |     Peripheral B      | Perip.C | Perip.D | Peri.E | Peri.F | Periph.G | Periph.H |
 |            |                  |        |                 |   EIC  | ADC |  AC | PTC | DAC | SERCOMx | SERCOMx |  TCCx  |  TCCx  |    COM   | AC/GLCK  |
 |            |                  |        |                 |(EXTINT)|(AIN)|(AIN)|     |     | (x/PAD) | (x/PAD) | (x/WO) | (x/WO) |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 |            | WiFi SPI         |        |                 |        |     |     |     |     |         |         |        |        |          |          |
 | 26         |                  |  PA12  | NINA_MOSI       |   12   |     |     |     |     |  *2/00  |   4/00  | TCC2/0 | TCC0/6 |          | AC/CMP0  |
 | 27         |                  |  PA13  | NINA_MISO       |   13   |     |     |     |     |  *2/01  |   4/01  | TCC2/1 | TCC0/7 |          | AC/CMP1  |
 | 28         |                  |  PA14  | NINA_CS         |   14   |     |     |     |     |   2/02  |   4/02  |  TC3/0 | TCC0/4 |          | GCLK_IO0 |
 | 29         |                  |  PA15  | NINA_SCK        |   15   |     |     |     |     |  *2/03  |   4/03  |  TC3/1 | TCC0/5 |          | GCLK_IO1 |
 | 30         |                  |  PA27  | NINA_GPIO0      |  *15   |     |     |     |     |         |         |        |        |          | GCLK_IO0 |
 | 31         |                  |  PB08  | NINA_RESETN     |   08   |  02 |     | Y14 |     |         |   4/00  |  TC4/0 |        |          |          |
 | 32         |                  |  PB09  | ADC_VBAT        |  *09   |  03 |     | Y15 |     |         |   4/01  |  TC4/1 |        |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 |            | 32768Hz Crystal  |        |                 |        |     |     |     |     |         |         |        |        |          |          |
 | 33         |                  |  PA00  | XIN32           |   00   |     |     |     |     |         |   1/00  | TCC2/0 |        |          |          |
 | 34         |                  |  PA01  | XOUT32          |   01   |     |     |     |     |         |   1/01  | TCC2/1 |        |          |          |
 +------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
 | 35         |                  |  PA28  | NINA_ACK        |   01   |     |     |     |     |         |   1/01  | TCC2/1 |        |          |          |
+------------+------------------+--------+-----------------+--------+-----+-----+-----+-----+---------+---------+--------+--------+----------+----------+
*/
                                                                                                                                               // DIPO=3 DOPO=0
  { PORTA, 12, PIO_SERCOM_ALT, (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MOSI: SERCOM4/PAD[0]
  { PORTA, 13, PIO_SERCOM_ALT, (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SCK:  SERCOM4/PAD[1]
  { PORTA, 14, PIO_DIGITAL,    (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SS:   as GPIO
  { PORTA, 15, PIO_SERCOM_ALT, (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MISO: SERCOM4/PAD[3]
  { PORTA, 27, PIO_DIGITAL,    (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15 },
  
  { PORTB,  8, PIO_DIGITAL,    (PIN_ATTR_DIGITAL|PIN_ATTR_ANALOG             ), ADC_Channel2,   NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTB,  9, PIO_ANALOG,     (PIN_ATTR_PWM|PIN_ATTR_TIMER                  ), ADC_Channel3,   PWM4_CH1,   TC4_CH1,      EXTERNAL_INT_9    },

  { PORTA,  0, PIO_DIGITAL,    (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
  { PORTA,  1, PIO_DIGITAL,    (PIN_ATTR_NONE                                ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },

  { PORTA, 28, PIO_DIGITAL,    (PIN_ATTR_DIGITAL                             ), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE },
};

extern "C" {
    unsigned int PINCOUNT_fn() {
        return (sizeof(g_APinDescription) / sizeof(g_APinDescription[0]));
    }
}

const void* g_apTCInstances[TCC_INST_NUM + TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 };

// Multi-serial objects instantiation
SERCOM sercom0(SERCOM0);
SERCOM sercom1(SERCOM1);
SERCOM sercom2(SERCOM2);
SERCOM sercom3(SERCOM3);
SERCOM sercom4(SERCOM4);
SERCOM sercom5(SERCOM5);

#if defined(USE_BQ24195L_PMIC)

#include "wiring_private.h"

#define PMIC_ADDRESS  0x6B
#define PMIC_REG01    0x01
#define PMIC_REG07    0x07

static inline void enable_battery_charging() {
  PERIPH_WIRE.initMasterWIRE(100000);
  PERIPH_WIRE.enableWIRE();
  pinPeripheral(PIN_WIRE_SDA, g_APinDescription[PIN_WIRE_SDA].ulPinType);
  pinPeripheral(PIN_WIRE_SCL, g_APinDescription[PIN_WIRE_SCL].ulPinType);

  PERIPH_WIRE.startTransmissionWIRE( PMIC_ADDRESS, WIRE_WRITE_FLAG );
  PERIPH_WIRE.sendDataMasterWIRE(PMIC_REG01);
  PERIPH_WIRE.sendDataMasterWIRE(0x1B); // Charge Battery + Minimum System Voltage 3.5V
  PERIPH_WIRE.prepareCommandBitsWire(WIRE_MASTER_ACT_STOP);

  PERIPH_WIRE.disableWIRE();
}

static inline void disable_battery_fet(bool disabled) {
  PERIPH_WIRE.initMasterWIRE(100000);
  PERIPH_WIRE.enableWIRE();
  pinPeripheral(PIN_WIRE_SDA, g_APinDescription[PIN_WIRE_SDA].ulPinType);
  pinPeripheral(PIN_WIRE_SCL, g_APinDescription[PIN_WIRE_SCL].ulPinType);

  PERIPH_WIRE.startTransmissionWIRE( PMIC_ADDRESS, WIRE_WRITE_FLAG );
  PERIPH_WIRE.sendDataMasterWIRE(PMIC_REG07);
  // No D+/D– detection + Safety timer not slowed by 2X during input DPM or thermal regulation +
  // BAT fet disabled/enabled + charge and bat fault INT
  PERIPH_WIRE.sendDataMasterWIRE(0x0B | (disabled ? 0x20 : 0x00));
  PERIPH_WIRE.prepareCommandBitsWire(WIRE_MASTER_ACT_STOP);

  PERIPH_WIRE.disableWIRE();
}

#endif

void initVariant() {
#if defined(USE_BQ24195L_PMIC)
  pinMode(ADC_BATTERY, OUTPUT);
  digitalWrite(ADC_BATTERY, LOW);
  delay(10);
  pinMode(ADC_BATTERY, INPUT);
  delay(100);

  bool batteryPresent = analogRead(ADC_BATTERY) > 600;
  if (batteryPresent) {
    enable_battery_charging();
  }
  disable_battery_fet(!batteryPresent);
#endif

  // NINA - SPI boot
  pinMode(NINA_GPIO0, OUTPUT);
  digitalWrite(NINA_GPIO0, HIGH);

  // disable NINA
  pinMode(NINA_RESETN, OUTPUT);
  digitalWrite(NINA_RESETN, HIGH);
}

// Serial1
Uart Serial1(&sercom5, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX);

void SERCOM5_Handler()
{
  Serial1.IrqHandler();
}

// Serial2
Uart Serial2(&sercom4, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX, PIN_SERIAL2_RTS, PIN_SERIAL2_CTS);

void SERCOM4_Handler()
{
  Serial2.IrqHandler();
}

#ifdef 0
/* Types used for the table below
typedef struct _PinDescription
{
  EPortType       ulPort ;
  uint32_t        ulPin ;
  EPioType        ulPinType ;
  uint32_t        ulPinAttribute ;
  EAnalogChannel  ulADCChannelNumber ; /* ADC Channel number in the SAM device */
  EPWMChannel     ulPWMChannel ;
  ETCChannel      ulTCChannel ;
  EExt_Interrupts ulExtInt ;
} PinDescription ;*/

/*ATSAMS70N2 https://www.microchip.com/wwwproducts/en/ATSAMS70N20#additional-features*/
PORT J6
G03  GPIO       PD26    –                   – PWMC0_PWML2   O TD                O UTXD2         O UTXD1         O
K01  GPIO_AD    PD30    AFE0_AD0(5)         I UTXD3         O –                 – –             – ISI_D10       I
F01  GPIO_AD    PA19    AFE0_AD8/WKUP9(6)   I –             – PWMC0_PWML0       O A15           O I2SC1_MCK     –
G01  GPIO_AD    PA17    AFE0_AD6(5)         I QIO2          ÷ PCK1              O PWMC0_PWMH3   O –             –
G04  GPIO_AD    PD24    –                   – PWMC0_PWML0   O RF                ÷ TCLK11        I ISI_HSYNC     I
K09  GPIO_AD    PA10    PIODC4(2)           I UTXD0         O PWMC0_PWMEXTRG0   I RD            I –             –

{ PORTD, 26, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM4_CH0,   TC4_CH0,      EXTERNAL_INT_6    },

J8  
B2   GPIO_AD    PB13    DAC0(11)            O PWMC0_PWML2   O PCK0              O SCK0          ÷ –             –
???  GPIO_AD    PD00    DAC1(11)            I GTXCK         I PWMC1_PWML0       O SPI1_NPCS1    ÷ DCD0          I
B09  GPIO_MLB   PB04    TDI(9)              I TWD1          ÷ PWMC0_PWMH2       O MLBCLK        I TXD1          ÷
J01  GPIO_AD    PA21    AFE0_AD1/PIODCEN2(8)I RXD1          I PCK1              O PWMC1_PWMFI0  I –             –
K07  GPIO_AD    PA24    –                   – RTS1          O PWMC0_PWMH1       O A20           O ISI_ PCK      I
C10  GPIO_AD    PA01    WKUP1(1)            I PWMC0_PWML0   O TIOB0             ÷ A18           O I2SC0_CK      –
H02  GPIO_AD    PB03    AFE0_AD2/WKUP12(6)  I CANRX0        I PCK2              O RTS0          O ISI_D2        I
H01  GPIO       PB02    AFE0_AD5(5)         I CANTX0 O      – –                 - CTS0          I SPI0_NPCS0    ÷
PORT J7  /* Types used for the table below
typedef struct _PinDescription
{
  EPortType       ulPort ;
  uint32_t        ulPin ;
  EPioType        ulPinType ;
  uint32_t        ulPinAttribute ;
  EAnalogChannel  ulADCChannelNumber ; /* ADC Channel number in the SAM device */
  EPWMChannel     ulPWMChannel ;
  ETCChannel      ulTCChannel ;
  EExt_Interrupts ulExtInt ;
} PinDescription ;*/

/*ATSAMS70N2 https://www.microchip.com/wwwproducts/en/ATSAMS70N20#additional-features*/
PORT J6
G03  GPIO       PD26    –                   – PWMC0_PWML2   O TD                O UTXD2         O UTXD1         O
K01  GPIO_AD    PD30    AFE0_AD0(5)         I UTXD3         O –                 – –             – ISI_D10       I
F01  GPIO_AD    PA19    AFE0_AD8/WKUP9(6)   I –             – PWMC0_PWML0       O A15           O I2SC1_MCK     –
G01  GPIO_AD    PA17    AFE0_AD6(5)         I QIO2          ÷ PCK1              O PWMC0_PWMH3   O –             –
G04  GPIO_AD    PD24    –                   – PWMC0_PWML0   O RF                ÷ TCLK11        I ISI_HSYNC     I
K09  GPIO_AD    PA10    PIODC4(2)           I UTXD0         O PWMC0_PWMEXTRG0   I RD            I –             –

{ PORTD, 26, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER    ), No_ADC_Channel, PWM4_CH0,   TC4_CH0,      EXTERNAL_INT_6    },

J8  
B2   GPIO_AD    PB13    DAC0(11)            O PWMC0_PWML2   O PCK0              O SCK0          ÷ –             –
???  GPIO_AD    PD00    DAC1(11)            I GTXCK         I PWMC1_PWML0       O SPI1_NPCS1    ÷ DCD0          I
B09  GPIO_MLB   PB04    TDI(9)              I TWD1          ÷ PWMC0_PWMH2       O MLBCLK        I TXD1          ÷
J01  GPIO_AD    PA21    AFE0_AD1/PIODCEN2(8)I RXD1          I PCK1              O PWMC1_PWMFI0  I –             –
K07  GPIO_AD    PA24    –                   – RTS1          O PWMC0_PWMH1       O A20           O ISI_ PCK      I
C10  GPIO_AD    PA01    WKUP1(1)            I PWMC0_PWML0   O TIOB0             ÷ A18           O I2SC0_CK      –
H02  GPIO_AD    PB03    AFE0_AD2/WKUP12(6)  I CANRX0        I PCK2              O RTS0          O ISI_D2        I
H01  GPIO       PB02    AFE0_AD5(5)         I CANTX0 O      – –                 - CTS0          I SPI0_NPCS0    ÷
PORT J7  
H10  GPIO       PA04    WKUP3/PIODC1(3)     I TWCK0         O TCLK0             I UTXD1         O –             –
F09  GPIO_AD    PA03    PIODC0(2)           I TWD0          ÷ LONCOL1           I PCK2          O –             –
     ADVREF     
J04  GPIO_AD    PD22    –                   – PWMC0_PWMH2   O SPI0_SPCK         O TIOB11        ÷ ISI_D0        I
K03  GPIO       PD20    –                   – PWMC0_PWMH0   O SPI0_MISO         ÷ GTSUCOMP–     O –             –
H03  GPIO_AD    PD25    –                   – PWMC0_PWML1   O SPI0_NPCS1        ÷ URXD2         I ISI_VSYNC     I
E10  GPIO_AD    PD12    –                   – GRX3          I CANTX1            O SPI0_NPCS2    O ISI_D6        I
J10  GPIO_AD    PD17    –                   – GTXER         O SCK2              ÷ CAS           O –             –
PORT J9                  
D09  GPIO_AD    PD11    –                   – GRX2          I PWMC0_PWMH0       O GTSUCOMP      O ISI_D5        I
???                 
H04  GPIO_AD    PD27    –                   – PWMC0_PWML3   O SPI0_NPCS3        O TWD2          O ISI_D8        I            
C09  GPIO_MLB   PD10    –                   – GCRS          I PWMC0_PWML0       O TD            O MLBSIG        ÷
H09  GPIO_AD    PA05    WKUP4/PIODC2(3)     I PWMC1_PWML3   O ISI_D4            I URXD1         I –             –
     PD30 again
J07  GPIO_AD    PD28    WKUP5(1) URXD3      I CANRX1        I TWCK2             O ISI_D9 I
PORT J11
E02  GPIO       PB01    AFE1_AD0/RTCOUT1(7) I PWMC0_PWMH1   O GTSUCOMP–         O TXD0          ÷ TK            ÷
E01  GPIO       PB00    AFE0_AD10/RTCOUT0(7)I PWMC0_PWMH0   O –                 – RXD0          I TF            ÷
G09  GPIO_AD    PD16    –                   – GTX3 O TXD2   ÷ RAS               O –             –               
K04  GPIO_AD    PD19    –                   – NCS3 O CTS2   I UTXD4             O –             –
K06  GPIO_AD    PD18    –                   – NCS1/SDCS     O RTS2              O URXD4         I –             –
     PD27 again
     PD28 again
PORT J14 PCMIA
C07  GPIO       PA30 ÷ WKUP11(1)            I PWMC0_PWML2   O PWMC1_PWMEXTRG0   I MCDA0         ÷ I2SC0_D0      –
A07  GPIO_AD    PA31 ÷ –                    – SPI0_NPCS1    ÷ PCK2              O MCDA1         ÷ PWMC1_PWMH2   O
K08  GPIO       PA26 ÷ –                    – DCD1          I TIOA2             O MCDA2         ÷ PWMC1_PWMFI1  I
H07  GPIO_AD    PA25 ÷ –                    – CTS1          I PWMC0_PWMH2       O A23           O MCCK          O
A09  GPIO       PA28 ÷ –                    – DSR1          I TCLK1             I MCCDA         ÷ PWMC1_PWMFI2  I
? goes to card detect
PORT J10 
     Target Reset
     PD22 again
     PD20 again
H05  GPIO_AD    PD21 ÷ –                  – PWMC0_PWMH1     O SPI0_MOSI         ÷ TIOA11        ÷ ISI_D1        I

//how does HSDM relate to a port and pin?
A04  USBHS      HSDM ÷       
B04  USBHS      HSDP ÷

unused?
D10  GPIO       PA02 ÷ WKUP2(1) I PWMC0_PWMH1 O – – DATRG I – –
J03  GPIO_AD    PA22 ÷ PIODCCLK(2) I RK ÷ PWMC0_PWMEXTRG1 I NCS2 O – –
B10  GPIO_AD    PD15 ÷ – – GTX2 O RXD2 I NWR1/NBS1 O – –
D08  GPIO_AD    PA00 ÷ WKUP0(1) I PWMC0_PWMH0 O TIOA0 ÷ A17/BA1 O I2SC0_MCK –
J02  CLOCK      PA07 ÷ XIN32(4) I – – PWMC0_PWMH3 – – – – – PIO, HiZ
K02  CLOCK      PA08 ÷ XOUT32(4) O PWMC1_PWMH3 O AFE0_ADTRG I – – – – PIO, HiZ
J09  GPIO_AD    PA09 ÷ WKUP6/PIODC3(3)I URXD0 I ISI_D3 I PWMC0_PWMFI0 I – –
J08  GPIO_AD    PA11 ÷ WKUP7/PIODC5(3)I QCS O PWMC0_PWMH0 O PWMC1_PWML0 O – –
K10  GPIO_AD    PA12 ÷ PIODC6(2) I QIO1 ÷ PWMC0_PWMH1 O PWMC1_PWMH0 O – –
G05  GPIO_AD    PA13 ÷ PIODC7(2) I QIO0 ÷ PWMC0_PWMH2 O PWMC1_PWML1 O – –
H06  GPIO_CLK   PA14 ÷ WKUP8/PIODCEN1(3) I QSCK O PWMC0_PWMH3 O PWMC1_PWMH1 O – –
J06  GPIO_AD    PA15 ÷ – I D14 ÷ TIOA1 ÷ PWMC0_PWML3 O I2SC0_WS –
J05  GPIO_AD    PA16 ÷ – I D15 ÷ TIOB1 ÷ PWMC0_PWML2 O I2SC0_DI –
G02  GPIO_AD    PA18 ÷ AFE0_AD7(5) I PWMC1_PWMEXTRG1 I PCK2 O A14 O – –
F02  GPIO_AD    PA20 ÷ AFE0_AD9/WKUP10(6)I – – PWMC0_PWML1 O A16/BA0 O I2SC1_CK –
K05  GPIO_AD    PA23 ÷ – – SCK1 ÷ PWMC0_PWMH0 O A19 O PWMC1_PWML2 O
H08  GPIO_AD    PA27 ÷ – – DTR1 O TIOB2 ÷ MCDA3 ÷ ISI_D7
C08  GPIO_MLB   PB05 ÷ TDO/TRACESWO/WKUP13(9) O TWCK1 O PWMC0_PWML0 O MLBDAT– ÷– TD O O, PU
G08  GPIO       PB06 ÷ SWDIO/TMS(9) I – – – – – – – – PIO,I,ST
E09  GPIO       PB07 ÷ SWCLK/TCK(9) I – – – – – – – – PIO,I,ST
F08  GPIO       PB12 ÷ ERASE(9) I PWMC0_PWML1 O GTSUCOMP– O – – PCK0 O PIO, I, PD, ST
E03  GPIO       PD02 ÷ – – GTX0 O PWMC1_PWML1 O SPI1_NPCS3 ÷ DSR0 I
B05  GPIO       PD03 ÷ – – GTX1 O PWMC1_PWMH1 O UTXD4 O RI0 I
A05  GPIO_CLK   PD04 ÷ – – GRXDV I PWMC1_PWML2 O TRACED0 O DCD2 I
D05  GPIO_CLK   PD05 ÷ – – GRX0 I PWMC1_PWMH2 O TRACED1 O DTR2 O
B06  GPIO_CLK   PD06 ÷ – – GRX1 I PWMC1_PWML3 O TRACED2 O DSR2 I
A08  GPIO_CLK   PD07 ÷ – – GRXER I PWMC1_PWMH3 O TRACED3 O RI2 I
B07  GPIO_CLK   PD08 ÷ – – GMDC O PWMC0_PWMFI1 I – – TRACECLK O
B08  GPIO_CLK   PD09 ÷ – – GMDIO ÷ PWMC0_PWMFI2 AFE1_ADTRG I – O
E08  GPIO_AD    PD13 ÷ – – GCOL I – – SDA10 O – –
F10  GPIO_AD    PD14 ÷ – – GRXCK I – – SDCKE O – –
G10  RST        NRST I – – – – – – – – – – PIO, I, PU


D03 D2 VDDIO GPIO PD1 ÷ – – GTXEN O PWMC1_PWMH0 O SPI1_NPCS2 ÷ DTR0 O
C01 B1 VDDIO GPIO_AD PD31 ÷ – – QIO3 ÷ UTXD3 O PCK2 O ISI_D11 I
H10  GPIO       PA04    WKUP3/PIODC1(3)     I TWCK0         O TCLK0             I UTXD1         O –             –
F09  GPIO_AD    PA03    PIODC0(2)           I TWD0          ÷ LONCOL1           I PCK2          O –             –
     ADVREF     
J04  GPIO_AD    PD22    –                   – PWMC0_PWMH2   O SPI0_SPCK         O TIOB11        ÷ ISI_D0        I
K03  GPIO       PD20    –                   – PWMC0_PWMH0   O SPI0_MISO         ÷ GTSUCOMP–     O –             –
H03  GPIO_AD    PD25    –                   – PWMC0_PWML1   O SPI0_NPCS1        ÷ URXD2         I ISI_VSYNC     I
E10  GPIO_AD    PD12    –                   – GRX3          I CANTX1            O SPI0_NPCS2    O ISI_D6        I
J10  GPIO_AD    PD17    –                   – GTXER         O SCK2              ÷ CAS           O –             –
PORT J9                  
D09  GPIO_AD    PD11    –                   – GRX2          I PWMC0_PWMH0       O GTSUCOMP      O ISI_D5        I
???                 
H04  GPIO_AD    PD27    –                   – PWMC0_PWML3   O SPI0_NPCS3        O TWD2          O ISI_D8        I            
C09  GPIO_MLB   PD10    –                   – GCRS          I PWMC0_PWML0       O TD            O MLBSIG        ÷
H09  GPIO_AD    PA05    WKUP4/PIODC2(3)     I PWMC1_PWML3   O ISI_D4            I URXD1         I –             –
     PD30 again
J07  GPIO_AD    PD28    WKUP5(1) URXD3      I CANRX1        I TWCK2             O ISI_D9 I
PORT J11
E02  GPIO       PB01    AFE1_AD0/RTCOUT1(7) I PWMC0_PWMH1   O GTSUCOMP–         O TXD0          ÷ TK            ÷
E01  GPIO       PB00    AFE0_AD10/RTCOUT0(7)I PWMC0_PWMH0   O –                 – RXD0          I TF            ÷
G09  GPIO_AD    PD16    –                   – GTX3 O TXD2   ÷ RAS               O –             –               
K04  GPIO_AD    PD19    –                   – NCS3 O CTS2   I UTXD4             O –             –
K06  GPIO_AD    PD18    –                   – NCS1/SDCS     O RTS2              O URXD4         I –             –
     PD27 again
     PD28 again
PORT J14 PCMIA
C07  GPIO       PA30 ÷ WKUP11(1)            I PWMC0_PWML2   O PWMC1_PWMEXTRG0   I MCDA0         ÷ I2SC0_D0      –
A07  GPIO_AD    PA31 ÷ –                    – SPI0_NPCS1    ÷ PCK2              O MCDA1         ÷ PWMC1_PWMH2   O
K08  GPIO       PA26 ÷ –                    – DCD1          I TIOA2             O MCDA2         ÷ PWMC1_PWMFI1  I
H07  GPIO_AD    PA25 ÷ –                    – CTS1          I PWMC0_PWMH2       O A23           O MCCK          O
A09  GPIO       PA28 ÷ –                    – DSR1          I TCLK1             I MCCDA         ÷ PWMC1_PWMFI2  I
? goes to card detect
PORT J10 
     Target Reset
     PD22 again
     PD20 again
H05  GPIO_AD    PD21 ÷ –                  – PWMC0_PWMH1     O SPI0_MOSI         ÷ TIOA11        ÷ ISI_D1        I

//how does HSDM relate to a port and pin?
A04  USBHS      HSDM ÷       
B04  USBHS      HSDP ÷

unused?
D10  GPIO       PA02 ÷ WKUP2(1) I PWMC0_PWMH1 O – – DATRG I – –
J03  GPIO_AD    PA22 ÷ PIODCCLK(2) I RK ÷ PWMC0_PWMEXTRG1 I NCS2 O – –
B10  GPIO_AD    PD15 ÷ – – GTX2 O RXD2 I NWR1/NBS1 O – –
D08  GPIO_AD    PA00 ÷ WKUP0(1) I PWMC0_PWMH0 O TIOA0 ÷ A17/BA1 O I2SC0_MCK –
J02  CLOCK      PA07 ÷ XIN32(4) I – – PWMC0_PWMH3 – – – – – PIO, HiZ
K02  CLOCK      PA08 ÷ XOUT32(4) O PWMC1_PWMH3 O AFE0_ADTRG I – – – – PIO, HiZ
J09  GPIO_AD    PA09 ÷ WKUP6/PIODC3(3)I URXD0 I ISI_D3 I PWMC0_PWMFI0 I – –
J08  GPIO_AD    PA11 ÷ WKUP7/PIODC5(3)I QCS O PWMC0_PWMH0 O PWMC1_PWML0 O – –
K10  GPIO_AD    PA12 ÷ PIODC6(2) I QIO1 ÷ PWMC0_PWMH1 O PWMC1_PWMH0 O – –
G05  GPIO_AD    PA13 ÷ PIODC7(2) I QIO0 ÷ PWMC0_PWMH2 O PWMC1_PWML1 O – –
H06  GPIO_CLK   PA14 ÷ WKUP8/PIODCEN1(3) I QSCK O PWMC0_PWMH3 O PWMC1_PWMH1 O – –
J06  GPIO_AD    PA15 ÷ – I D14 ÷ TIOA1 ÷ PWMC0_PWML3 O I2SC0_WS –
J05  GPIO_AD    PA16 ÷ – I D15 ÷ TIOB1 ÷ PWMC0_PWML2 O I2SC0_DI –
G02  GPIO_AD    PA18 ÷ AFE0_AD7(5) I PWMC1_PWMEXTRG1 I PCK2 O A14 O – –
F02  GPIO_AD    PA20 ÷ AFE0_AD9/WKUP10(6)I – – PWMC0_PWML1 O A16/BA0 O I2SC1_CK –
K05  GPIO_AD    PA23 ÷ – – SCK1 ÷ PWMC0_PWMH0 O A19 O PWMC1_PWML2 O
H08  GPIO_AD    PA27 ÷ – – DTR1 O TIOB2 ÷ MCDA3 ÷ ISI_D7
C08  GPIO_MLB   PB05 ÷ TDO/TRACESWO/WKUP13(9) O TWCK1 O PWMC0_PWML0 O MLBDAT– ÷– TD O O, PU
G08  GPIO       PB06 ÷ SWDIO/TMS(9) I – – – – – – – – PIO,I,ST
E09  GPIO       PB07 ÷ SWCLK/TCK(9) I – – – – – – – – PIO,I,ST
F08  GPIO       PB12 ÷ ERASE(9) I PWMC0_PWML1 O GTSUCOMP– O – – PCK0 O PIO, I, PD, ST
E03  GPIO       PD02 ÷ – – GTX0 O PWMC1_PWML1 O SPI1_NPCS3 ÷ DSR0 I
B05  GPIO       PD03 ÷ – – GTX1 O PWMC1_PWMH1 O UTXD4 O RI0 I
A05  GPIO_CLK   PD04 ÷ – – GRXDV I PWMC1_PWML2 O TRACED0 O DCD2 I
D05  GPIO_CLK   PD05 ÷ – – GRX0 I PWMC1_PWMH2 O TRACED1 O DTR2 O
B06  GPIO_CLK   PD06 ÷ – – GRX1 I PWMC1_PWML3 O TRACED2 O DSR2 I
A08  GPIO_CLK   PD07 ÷ – – GRXER I PWMC1_PWMH3 O TRACED3 O RI2 I
B07  GPIO_CLK   PD08 ÷ – – GMDC O PWMC0_PWMFI1 I – – TRACECLK O
B08  GPIO_CLK   PD09 ÷ – – GMDIO ÷ PWMC0_PWMFI2 AFE1_ADTRG I – O
E08  GPIO_AD    PD13 ÷ – – GCOL I – – SDA10 O – –
F10  GPIO_AD    PD14 ÷ – – GRXCK I – – SDCKE O – –
G10  RST        NRST I – – – – – – – – – – PIO, I, PU


D03 D2 VDDIO GPIO PD1 ÷ – – GTXEN O PWMC1_PWMH0 O SPI1_NPCS2 ÷ DTR0 O
C01 B1 VDDIO GPIO_AD PD31 ÷ – – QIO3 ÷ UTXD3 O PCK2 O ISI_D11 I
#endif
