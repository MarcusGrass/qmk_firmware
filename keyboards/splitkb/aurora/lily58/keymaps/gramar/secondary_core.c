#include "ch.h"
#include "secondary_worker.h"

// Necessary symbols to start core 1, core 0 sets up the qmk-important stuff, so these are pretty much all no-ops
void __c1_cpu_init(void) {

#if CORTEX_MODEL == 7
    SCB_EnableICache();
    SCB_EnableDCache();
#endif
}

void __c1_early_init(void) {}
void __c1_late_init(void) {}
void __c1_default_exit(void) {
    while (true) {}
}

// From chibios rp pico demo
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

    // Launch worker loop
    worker_run();
}
