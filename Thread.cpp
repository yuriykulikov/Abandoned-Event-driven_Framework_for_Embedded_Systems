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
/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

#include "Thread.h"

extern "C" void pvTaskCode(void *pvParameters) {
    (static_cast<Thread*>(pvParameters))->run();
}

Thread::Thread(const char *name, unsigned short stackDepth, char priority, bool suspendsGracefully) {
    this->suspendsGracefully = suspendsGracefully;
    suspending = false;
    xTaskCreate(pvTaskCode, (const signed char *) name, stackDepth, (void*) this, priority, &taskHandle);
}

Thread::Thread(const char *name, unsigned short stackDepth, char priority) {
    this->suspendsGracefully = false;
    suspending = false;
    xTaskCreate(pvTaskCode, (const signed char *) name, stackDepth, (void*) this, priority, &taskHandle);
}

void Thread::suspend() {
    if (suspendsGracefully) {
        suspending = true;
    } else {
        vTaskSuspend(taskHandle);
    }
}

void Thread::resume() {
    vTaskResume(taskHandle);
}

void Thread::checkForSuspendRequest() {
    if (suspending) {
        suspending = false;
        vTaskSuspend(taskHandle);
    }
}
