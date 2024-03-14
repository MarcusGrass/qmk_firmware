//
// Created by gramar on 3/14/24.
//

#ifndef QMK_FIRMWARE_SPLIT_TRANSACTION_H
#define QMK_FIRMWARE_SPLIT_TRANSACTION_H
typedef struct {
    uint8_t kind;
    uint8_t pressed;
} transaction_sync_msg;

void right_side_transaction_handler(uint8_t in_buflen, const void* in_data);
void left_side_submit_shift_transaction(bool pressed);
void left_side_submit_ctrl_transaction(bool pressed);
#endif // QMK_FIRMWARE_SPLIT_TRANSACTION_H
