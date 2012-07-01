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

#ifndef QUEUE_H_
#define QUEUE_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


class Queue {
private:
    /** Queue on which handler posts messages */
    xQueueHandle messageQueue;
public:
    Queue(uint8_t messageQueueSize, size_t itemSize) {
        messageQueue = xQueueCreate(messageQueueSize, itemSize);
    }
    Queue() {
        messageQueue = 0;
    }
    inline bool send(void *ptr){
        return xQueueSend(messageQueue, ptr, 0);
    }
    inline bool sendFromIsr(void *ptr){
        //isHigherProirityTaskWoken is ignored in this method
        return xQueueSendFromISR(messageQueue, ptr, 0);
    }
    inline bool receive(void *ptr){
        return xQueueReceive(messageQueue, ptr, portMAX_DELAY);
    }
    /**
     *
     * @param ptr
     * @param isHigherProirityTaskWoken
     * @return true if element was successfully fetched
     */
    inline bool receiveFromISR(void *ptr){
        //isHigherProirityTaskWoken is ignored in this method
        return xQueueReceiveFromISR(messageQueue, ptr, 0);
    }
};


#endif /* QUEUE_H_ */
