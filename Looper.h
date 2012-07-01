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

#ifndef LOOPER_H_
#define LOOPER_H_

#include "Thread.h"
#include "QueueWrapper.h"

/**
 * Looper is a thread which is used for Event Dispatch Thread  (EDT) model.
 * Looper contains a queue, to which messages are posted. These messages are later popped from
 * the queue and are handled with an appropriate Handler (specified in the message itself).
 * Looper invokes Handler.handlerMessage() from the Handler.
 */
class Looper: public Thread {
private:
    /** Queue on which handler posts messages */
    Queue messageQueue;
public:
    Looper(uint8_t messageQueueSize, const char *name, unsigned short stackDepth, char priority);
    Queue * getMessageQueue();
    void run();
};

#endif /* LOOPER_H_ */
