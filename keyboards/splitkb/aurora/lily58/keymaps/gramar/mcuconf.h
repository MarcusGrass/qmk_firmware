/*
* HAL driver system settings.
*/
#pragma once

#include_next "mcuconf.h"
// Unset default core1 start false, now needs to provide function c1_main
#undef RP_CORE1_START
#define RP_NO_INIT                          FALSE
#define RP_CORE1_START                      TRUE
#define RP_CORE1_VECTORS_TABLE              _vectors
#define RP_CORE1_ENTRY_POINT                _crt0_c1_entry
#define RP_CORE1_STACK_END                  __c1_main_stack_end__
