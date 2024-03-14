/*
ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "ch.h"
#include "oled_impl.h"

void __c1_cpu_init(void) {

#if CORTEX_MODEL == 7
    SCB_EnableICache();
    SCB_EnableDCache();
#endif
}

void __c1_early_init(void) {}
void __c1_late_init(void) {}
void __c1_default_exit(void) {
    /*lint -restore*/

    while (true) {
    }
}
/**
* Core 1 entry point.
 */
void c1_main(void) {

    /*
* Starting a new OS instance running on this core, we need to wait for
* system initialization on the other side.
     */
    chSysWaitSystemState(ch_sys_running);
    chInstanceObjectInit(&ch1, &ch_core1_cfg);

    /* It is alive now.*/
    chSysUnlock();

    /*
* Normal main() thread activity, in this demo it does nothing except
* sleeping in a loop (re)spawning a shell.
     */
    oled_worker_run();
}
