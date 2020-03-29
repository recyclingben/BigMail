#pragma once
#include <stdlib.h>

typedef struct {
    int content_sizeof;
    int content_allot;
} mail_box_MailBoxHead;

void mail_box_create(int content_sizeof,
                     mail_box_MailBoxHead **out_mailbox);


void mail_box_create(int content_sizeof,
                     mail_box_MailBoxHead **out_mailbox)
{
    *out_mailbox = calloc(1, sizeof(mail_box_MailBoxHead) + content_sizeof);
}