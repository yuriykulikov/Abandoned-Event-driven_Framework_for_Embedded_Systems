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
#ifndef HANDLER_H_
#define HANDLER_H_

#include "QueueWrapper.h"
#include "Looper.h"

typedef struct MESSAGE Message;

/**
 * Contains an utility called handler. It is used to post messages to be handled by the task
 * immediately or with a delay. A high-priority task, like command line interpreter, or an ISR
 * should post messages to the handler. Subclass it and override handleMessage(Message msg);
 */
class Handler {
private:
    /** Queue on which handler posts messages */
    Queue *messageQueue;
public:
    Handler(Looper *looper);
    virtual void handleMessage(Message msg) =0;
    bool sendMessage(Message msg);
    bool sendMessage(char what);
    bool sendMessage(char what, char arg1, char arg2);
    bool sendMessage(char what, char arg1, char arg2, void *ptr);
    bool sendMessageFromISR(Message msg);
    bool sendMessageFromISR(char what);
    bool sendMessageFromISR(char what, char arg1, char arg2);
    bool sendMessageFromISR(char what, char arg1, char arg2, void *ptr);
};

struct MESSAGE {
    /** Handler responsible for handling this message */
    Handler *handler;
    /** What message is about */
    char what;
    /** First argument */
    char arg1;
    /** First argument */
    char arg2;
    /** Pointer to the allocated memory. Handler should cast to the proper type,
     * according to the message.what */
    void *ptr;
};

#endif /* HANDLER_H_ */
