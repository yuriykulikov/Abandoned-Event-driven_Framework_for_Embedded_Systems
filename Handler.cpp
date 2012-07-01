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

#include "Handler.h"
#include "Looper.h"
#include "QueueWrapper.h"

/**
 * Creates a handler, which has to be bind to the looper task
 * @param looper
 * @param handleMessage
 * @param context
 */
Handler::Handler(Looper *looper) {
    messageQueue = looper->getMessageQueue();
}

/**
 * Post Message
 * @param msg
 * @return true if the item was successfully posted
 */
bool Handler::sendMessage(Message msg) {
    return messageQueue->send(&msg);
}

/**
 * Post message with arguments and a pointer to allocated data
 * @param handler
 * @param what
 * @param arg1
 * @param arg2
 * @param ptr
 * @return true if the item was successfully posted
 */
bool Handler::sendMessage(char what, char arg1, char arg2, void *ptr) {
    Message msg;
    msg.handler = this;
    msg.what = what;
    msg.arg1 = arg1;
    msg.arg2 = arg2;
    msg.ptr = ptr;
    return messageQueue->send(&msg);
}

/**
 * Post empty message
 * @param handler
 * @param what
 * @return true if the item was successfully posted
 */
bool Handler::sendMessage(char what) {
    return sendMessage(what, NULL, NULL, NULL);
}

/**
 * Post message with arguments
 * @param handler
 * @param what
 * @param arg1
 * @param arg2
 * @return true if the item was successfully posted
 */
bool Handler::sendMessage(char what, char arg1, char arg2) {
    return sendMessage(what, arg1, arg2, NULL);
}
/**
 * Post Message
 * @param msg
 * @return true if higher priority task is woken
 */
bool Handler::sendMessageFromISR(Message msg) {
    return messageQueue->sendFromIsr(&msg);
}
/**
 * Post message with arguments and a pointer to allocated data
 * @param handler
 * @param what
 * @param arg1
 * @param arg2
 * @param ptr
 * @return true if higher priority task is woken
 */
bool Handler::sendMessageFromISR(char what, char arg1, char arg2, void *ptr) {
    Message msg;
    msg.handler = this;
    msg.what = what;
    msg.arg1 = arg1;
    msg.arg2 = arg2;
    msg.ptr = ptr;
    return messageQueue->sendFromIsr(&msg);
}

/**
 * Post empty message
 * @param handler
 * @param what
 * @return true if higher priority task is woken
 */
bool Handler::sendMessageFromISR(char what) {
    return sendMessageFromISR(what, NULL, NULL, NULL);
}

/**
 * Post message with arguments
 * @param handler
 * @param what
 * @param arg1
 * @param arg2
 * @return true if higher priority task is woken
 */
bool Handler::sendMessageFromISR(char what, char arg1, char arg2) {
    return sendMessageFromISR(what, arg1, arg2, NULL);
}
