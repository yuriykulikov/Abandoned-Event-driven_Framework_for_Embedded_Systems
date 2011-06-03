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

/* Compiler definitions include file. */
extern "C" {
#include "avr_compiler.h"
#include <string.h>
}
/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Task header file */
#include "Handler.h"
#include "Looper.h"

/**
 * Creates a handler, which has to be bind to the looper task
 * @param looper
 * @param handleMessage
 * @param context
 */
Handler::Handler(Looper *looper) {
    messageQueue = looper->getMessageQueue();
}

bool Handler::sendMessage(Message msg) {
    return xQueueSend(messageQueue, &msg, 0);
}

/**
 * Post message with arguments and a pointer to allocated data
 * @param handler
 * @param what
 * @param arg1
 * @param arg2
 * @param ptr
 */
bool Handler::sendMessage(char what, char arg1, char arg2, void *ptr) {
    Message msg;
    msg.handler = this;
    msg.what = what;
    msg.arg1 = arg1;
    msg.arg2 = arg2;
    msg.ptr = ptr;
    return xQueueSend(messageQueue, &msg, 0);
}

/**
 * Post empty message
 * @param handler
 * @param what
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
 */
bool Handler::sendMessage(char what, char arg1, char arg2) {
    return sendMessage(what, arg1, arg2, NULL);
}

