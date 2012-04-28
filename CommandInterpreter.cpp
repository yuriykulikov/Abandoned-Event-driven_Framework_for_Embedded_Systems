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
#include "Handler.h"

CommandInterpreter::CommandInterpreter() {
    list = (InputListItem*) pvPortMalloc(sizeof(InputListItem));
    list->pxNextEntry = NULL;
}

void CommandInterpreter::registerCommand(char *pgm_Cmd, char *pgm_CmdDesc, Handler *handler, char what) {
    /* Create a new list item that will reference the command being registered. */
    InputListItem *pxNewListItem = (InputListItem*) pvPortMalloc(sizeof(InputListItem));
    // this will be the last element
    pxNewListItem->pxNextEntry = NULL;
    // now populate the entry from input parameters
    pxNewListItem->pcCommand = pgm_Cmd;
    pxNewListItem->pcHelpString = pgm_CmdDesc;
    pxNewListItem->handler = handler;
    pxNewListItem->what = what;
    InputListItem *entry = list;
    //find last element
    while (entry->pxNextEntry!=NULL) {
        entry = entry->pxNextEntry;
    }
    // Now store pointer to this new element to the last element
    entry->pxNextEntry = pxNewListItem;
}

void CommandInterpreter::processCommand(char *pcCommandInput, TxBuffer *txBuffer) {
    // Search for the command string in the list of registered commands starting with the second entry (first is emtpy)
    for(InputListItem *entry = list->pxNextEntry; entry != NULL; entry = entry->pxNextEntry ) {
        //we move cursor to the end of the string, and stop if condition is met
        char *inputCursor = pcCommandInput;
        char *entryCursor = entry->pcCommand;
        char inputChar;
        char entryChar;
        //parse command
        while (true) {
            inputChar = *inputCursor++;
            //TODO #ifdef HARVARD
            entryChar = pgm_read_byte(entryCursor++);
            //now we can have different situations and we have to handle them all!
            if (inputChar == 0x00 && entryChar != 0x00 ) {
                //command incomplete, proceed to the next command
                break;
            }
            //entry ended, input not - parse args
            if (entryChar == 0x00) {
                //TODO optimize sometime
                uint8_t arg[2] = {0, 0};
                for (uint8_t args = 0; args<2; args++) {
                    //str will be used to hold HEX args, so it has to be 4 bits
                    char str[4] = {0, 0, 0, 0};
                    //eat whitespace
                    while (*inputCursor == ' ') {
                        inputCursor++;
                    }
                    if (*inputCursor == 0x00) break;;
                    //parse arg
                    for (uint8_t i = 0; i<4; i++) {
                        inputChar = *inputCursor++;
                        if (inputChar == 0x00) break;
                        if (inputChar == ' ') break;
                        str[i] = inputChar;
                    }
                    arg[args] = atoi(str);
                }
#ifdef DEBUG
                txBuffer->putString("sending msg, args:");
                txBuffer->putInt(arg[0], 16);
                txBuffer->putString(", ");
                txBuffer->putInt(arg[1], 16);
                txBuffer->putString("\n");
#endif
                entry->handler->sendMessage(entry->what, arg[0], arg[1], txBuffer);
                //command found, return
                return;
            }
            //no match - no match
            if (inputChar != entryChar) {
                //strings differ, proceed to the next command
                break;
            }
        }
    }
    // No matches were found, maybe it was a help command?
    if (strcmp_P( ( const char * ) pcCommandInput, ( const char * ) Strings_HelpCmd ) == 0) {
        txBuffer->putPgmString(Strings_HelpCmdDesc);
        // Search for the command string in the list of registered commands starting with the second entry (first is emtpy)
        for(InputListItem *entry = list->pxNextEntry; entry != NULL; entry = entry->pxNextEntry ) {
            txBuffer->putPgmString(entry->pcCommand);
            txBuffer->putPgmString(Strings_colon);
            txBuffer->putPgmString(Strings_space);
            txBuffer->putPgmString(entry->pcHelpString);
        }
    } else {
        txBuffer->putPgmString(Strings_InterpretorError);
    }
}

