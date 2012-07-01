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

#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include "TxBuffer.h"
#include "Handler.h"

typedef struct InputListItem {
//public:
    /* The command that causes pxCommandInterpreter to be executed.  For example "help".  Must be all lower case. */
    char *pcCommand;
    /* String that describes how to use the command.  Should start with the command itself, and end with "\r\n".
     * For example "help: Returns a list of all the commands\r\n". */
    char *pcHelpString;
    Handler *handler;
    char what;
    InputListItem *pxNextEntry;
} InputListItem;

/**
 * Class contains a mapping between registered commands and handlers. If CommandInterpreter was able to
 * map an incoming command to a handler, this handler gets a message.
 */
class CommandInterpreter {
public:
    CommandInterpreter();
    void registerCommand(char *pgm_Cmd, char *pgm_CmdDesc, Handler *handler, char what);
    void processCommand(char *pcCommandInput, TxBuffer *txBuffer);
private:
    InputListItem *list;
};

#endif /* COMMAND_INTERPRETER_H */

