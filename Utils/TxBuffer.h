/* This file has been prepared for Doxygen automatic documentation generation.*/
/*
 * Copyright (C) 2012 Yuriy Kulikov
 *      Universitaet Erlangen-Nuernberg
 *      LS Informationstechnik (Kommunikationselektronik)
 *      Support email: Yuriy.Kulikov.87@googlemail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef TX_BUFFER_H_
#define TX_BUFFER_H_

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/**
 * Represents a TX buffer. This is an abstract class. Implement it's interface with
 * USART, SPI, USB or anything else. Underlying mechanism might be based on a queue or
 * a circular buffer plus semaphore.
 */
class TxBuffer {
protected:
    /** Default ticksToWait value */
    int txTicksToWait;
public:
    TxBuffer(int defaultTicksToWait);
    /**
     * Put byte into the buffer. Consequent call to flush() is required to start a transmission
     * @param data
     * @return
     */
    virtual int8_t putByte(uint8_t data) =0;
    /**
     * Start transmission
     */
    virtual void flush() =0;
    /**
     * Puts the string into the buffer. Default implementation uses putByte() and invokes flush()
     * @param string
     * @return
     */
    int8_t putString(const char *string);
    /**
     * Puts the program memory string into the buffer. Default implementation uses putByte() and invokes flush()
     * TODO should depend on ARCHITECTURE_HARVARD being defined
     * @param progmem_s
     * @return
     */
    int8_t putPgmString(const char *progmem_s);
    /**
     * Puts string representation of the number into the buffer. Default implementation uses putString() and itoa().
     * @param Int
     * @param radix
     * @return
     */
    int8_t putInt(int16_t Int,int16_t radix);
};

#endif /* TX_BUFFER_H_ */
