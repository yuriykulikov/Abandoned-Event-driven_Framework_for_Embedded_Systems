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
#define DEBUG
//#undef DEBUG

extern "C" {
/* Standard includes. */
#include <string.h>
#include <avr/pgmspace.h>
#include "strings.h"
}
/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Utils includes. */
#include "CommandInterpreter.h"
#include "CommandInterpreterThread.h"
#include "Thread.h"
#include "Serial.h"

CommandInterpreterThread::CommandInterpreterThread(CommandInterpreter *interpreter, uint8_t commandInputLen, Serial *serial, const char *name, unsigned short stackDepth, char priority)
:Thread(name, stackDepth, priority){
    commandInputBuffer = (char *) pvPortMalloc( sizeof(char)*commandInputLen);
    this->interpreter = interpreter;
    this->serial = serial;
}

void CommandInterpreterThread::run() {
    char receivedChar='#';
    /* Task loops forever*/
    for (;;) {
        //Empty the string first
        strcpy(commandInputBuffer,"");
        // Wait until the first symbol unblocks the task
        serial->getByte(&receivedChar,portMAX_DELAY);
        strncat(commandInputBuffer,&receivedChar,1);
        //Read string from queue, while data is available and put it into string
        // This loop will be over, when there is either ; or \n is received, or queue is empty for 200 ms
        while (serial->getByte(&receivedChar,200)) {
            if (receivedChar == ';') break;
            if (receivedChar == '\n') break;
            strncat(commandInputBuffer,&receivedChar,1);
        }

        interpreter->processCommand(commandInputBuffer, serial);
    }
}
