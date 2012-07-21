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
 * @startuml
 * participant Someone
 * participant Handler as "ConcreteHandler: Handler"
 * participant Handler2 as "ConcreteHandler2: Handler"
 * box "Looper" #LightBlue
 *     participant Looper
 *     participant MessageQueue
 * endbox
 * activate Someone
 * Someone -> Handler : sendMessage(msg1)
 * Handler -> Looper : postMessage(msg1)
 * Looper -> MessageQueue : post(msg1)
 * MessageQueue --> Someone : message was posted, now we return
 * Someone -> Handler2 : sendMessage(msg2)
 * Handler2 -> Looper : postMessage(msg2)
 * Looper -> MessageQueue : post(msg2)
 * MessageQueue --> Someone : message was posted, now we return
 * deactivate Someone
 * MessageQueue ->> Looper : getMessage()
 * activate Looper
 * note over Looper: message contains a pointer to \n the handler it is addressed to
 * Looper -> Handler : handleMessage(msg1)
 * deactivate Looper
 * MessageQueue ->> Looper : getMessage()
 * activate Looper
 * note over Looper: message contains a pointer to \n the handler it is addressed to
 * Looper -> Handler2 : handleMessage(msg2)
 * deactivate Looper
 * @enduml
 */
class Handler {
private:
    /** Queue on which handler posts messages */
    Queue *messageQueue;
public:
    Handler(Looper *looper);
    /**
     * Handle message which was previously set. Override this method in your implementation.
     * @param msg
     */
    virtual void handleMessage(Message msg) =0;
    /**
     * Send message
     * @param msg
     * @return
     */
    bool sendMessage(Message msg);
    /**
     * Send empty message with a specified topic
     * @param what
     * @return
     */
    bool sendMessage(char what);
    /**
     * Send message with a specified topic and arguments
     * @param what
     * @param arg1
     * @param arg2
     * @return
     */
    bool sendMessage(char what, char arg1, char arg2);
    /**
     * Send message with a specified topic, arguments and pointer to something
     * @param what
     * @param arg1
     * @param arg2
     * @param ptr
     * @return
     */
    bool sendMessage(char what, char arg1, char arg2, void *ptr);
    /**
     * Send empty message with a specified topic ISR
     * @param msg
     * @return
     */
    bool sendMessageFromISR(Message msg);
    /**
     * Send message from ISR
     * @param what
     * @return
     */
    bool sendMessageFromISR(char what);
    /**
     * Send message with a specified topic and arguments from ISR
     * @param what
     * @param arg1
     * @param arg2
     * @return
     */
    bool sendMessageFromISR(char what, char arg1, char arg2);
    /**
     * Send message with a specified topic, arguments and pointer to something from ISR
     * @param what
     * @param arg1
     * @param arg2
     * @param ptr
     * @return
     */
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
