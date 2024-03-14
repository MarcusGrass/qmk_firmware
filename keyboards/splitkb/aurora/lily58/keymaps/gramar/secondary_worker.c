//
// Created by gramar on 3/14/24.
//

#include "rp_smp.h"
#include "secondary_worker.h"
#include "oled_impl.h"

void worker_run(void) {
    while(1) {
        render_msg next_msg = await_next_message_on_queue();
        switch (next_msg.kind) {
            case 1:
                return;
            case 2:
                kb_layers layer = (kb_layers)next_msg.msg.df_layer.layer;
                oled_write_default_layer(layer);
            default:
                break;
        }
    }
}
