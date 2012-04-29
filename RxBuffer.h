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
#ifndef RX_BUFFER_H_
#define RX_BUFFER_H_

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/**
 * Represents an RX buffer. This is an abstract class. Implement it's interface with
 * USART, SPI, USB or anything else. Underlying mechanism might be based on a queue or
 * a circular buffer plus semaphore.
 */
class RxBuffer {
protected:
    /** Default ticksToWait value */
    int rxTicksToWait;
public:
    RxBuffer(int defaultTicksToWait);
    /**
     * Get byte from the buffer. Blocking call.
     * @param receivedChar
     * @param ticks
     * @return success
     */
    virtual int8_t getByte(char * receivedChar, int ticks) =0;
    /**
     * Get byte from the buffer. Blocking call. Blocks for this.ticksToWait;
     * @param receivedChar
     * @return success
     */
    int8_t getByte(char * receivedChar);
};

#endif /* RX_BUFFER_H_ */
