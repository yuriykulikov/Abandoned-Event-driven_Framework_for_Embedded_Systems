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

#ifndef COMMAND_INTERPRETER_THREAD_H
#define COMMAND_INTERPRETER_THREAD_H

#include "RxBuffer.h"
#include "TxBuffer.h"
#include "Thread.h"

/**
 * A Thread, which aggregates messages from the RxBuffer input (might be USART, keyboard, etc.)
 * and invokes CommandInterpreter.processCommand(), which leads to sending a message to a
 * registered handler (if found).
 */
class CommandInterpreterThread : public Thread {
public:
    CommandInterpreterThread(CommandInterpreter *interpreter, uint8_t commandInputLen, RxBuffer *rxBuffer,
            TxBuffer *txBuffer, const char *name, unsigned short stackDepth, char priority);
    void run();
private:
    char *commandInputBuffer;
    CommandInterpreter *interpreter;
    RxBuffer *rxBuffer;
    TxBuffer *txBuffer;
};

#endif /* COMMAND_INTERPRETER_THREAD_H */

