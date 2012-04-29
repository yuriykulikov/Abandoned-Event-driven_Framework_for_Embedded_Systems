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
    for(InputListItem *entry = list; entry != NULL; entry = entry->pxNextEntry ) {
        if( strcmp_P( ( const char * ) pcCommandInput, ( const char * ) entry->pcCommand ) == 0 ) {
        /* The command has been found, the loop can exit so the command
           can be executed. */
            entry->handler->sendMessage(entry->what, 0, 0, txBuffer);
            return;
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

