#pragma once
#include <stdlib.h>

typedef enum {
    mail_box_ENTRY_DEAD = 0,
    mail_box_ENTRY_LIVE = 1,
    mail_box_ENTRY_LOCK = 2
} mail_box_MailBoxEntryState;

typedef struct {
    _Atomic mail_box_MailBoxEntryState state;
} mail_box_MailBoxEntryHead;

typedef struct {
    int content_sizeof;
    mail_box_MailBoxEntryHead *_Atomic lagging;
    mail_box_MailBoxEntryHead *_Atomic leading;
} mail_box_MailBoxHead;

void mail_box_create(int content_sizeof,
                     mail_box_MailBoxHead **out_mailbox);


void mail_box_create(int content_sizeof,
                     mail_box_MailBoxHead **out_mailbox)
{
    *out_mailbox = calloc(1, sizeof(mail_box_MailBoxHead) + content_sizeof);
    (*out_mailbox)->lagging = (mail_box_MailBoxEntryHead *)(*out_mailbox + 1);
    (*out_mailbox)->leading = (mail_box_MailBoxEntryHead *)(*out_mailbox + 1);
}