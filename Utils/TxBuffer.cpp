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
/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

#include "avr_compiler.h"
extern "C" {
#include <avr/pgmspace.h>
}
#include "TxBuffer.h"

TxBuffer::TxBuffer(int defaultTicksToWait) {
    this->txTicksToWait = defaultTicksToWait;
}

int8_t TxBuffer::putString(const char *string)
{
    //send the whole string
    while (*string) {
        int8_t putByteResult = putByte(*string++);
        if (putByteResult == pdFAIL) return pdFAIL;
    }
    flush();
    return pdPASS;
}

int8_t TxBuffer::putPgmString(const char *progmem_s)
{
    register char c;
    while ( (c = pgm_read_byte(progmem_s++)) ) {
        int8_t putByteResult =  putByte(c);
        if (putByteResult == pdFAIL) return pdFAIL;
    }
    flush();
    return pdPASS;
}

int8_t TxBuffer::putInt(int16_t Int,int16_t radix) {
    // buffer size is 8 + 8 + 1 (termination) bits. Enough to fit a 16-bit int represented with radix = 2.
    char str[17];
    return putString(itoa(Int,str,radix));
}
