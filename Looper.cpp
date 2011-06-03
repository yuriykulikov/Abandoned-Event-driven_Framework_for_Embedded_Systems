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
#include "queue.h"

#include "Handler.h"
#include "Looper.h"
#include "ExampleHandler.h"
#include "Thread.h"

Looper::Looper(uint8_t messageQueueSize, const char *name, unsigned short stackDepth, char priority)
:Thread(name, stackDepth, priority) {
    messageQueue = xQueueCreate(messageQueueSize, sizeof(Message));
}

void Looper::run() {
    Message msg;
    //Infinite loop
    for (;;) {
        if (xQueueReceive(messageQueue, &msg, portMAX_DELAY)) {
            // Call handleMessage from the handler
            msg.handler->handleMessage(msg);
        }
    }
}

xQueueHandle Looper::getMessageQueue(){
    return messageQueue;
}
