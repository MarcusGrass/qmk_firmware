//
// Created by gramar on 3/14/24.
//

#include "secondary_client.h"
#include "split_transaction.h"
#include "transactions.h"

void right_side_transaction_handler(uint8_t in_buflen, const void* in_data) {
    uint8_t len = in_buflen / sizeof(transaction_sync_msg);
    if (len < 1) {
        return;
    }
    const transaction_sync_msg *messages = (const transaction_sync_msg*) in_data;
    for (uint8_t i = 0; i < len; ++i) {
        transaction_sync_msg msg = messages[i];
        switch (msg.kind) {
            case 1:
                worker_submit_shift(msg.pressed);
                break;
            case 2:
                worker_submit_ctrl(msg.pressed);
                break;
        }
    }
}

void left_side_submit_shift_transaction(bool pressed) {
    transaction_sync_msg msg = {1, pressed};
    transaction_rpc_send(OLED_DATA_SYNC, sizeof(msg), &msg);
}

void left_side_submit_ctrl_transaction(bool pressed) {
    transaction_sync_msg msg = {2, pressed};
    transaction_rpc_send(OLED_DATA_SYNC, sizeof(msg), &msg);
}