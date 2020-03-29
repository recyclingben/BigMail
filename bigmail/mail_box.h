#pragma once
#include <stdlib.h>

typedef struct {
    int content_sizeof;
    int content_allot;
} mail_box_MailBoxHead;

mail_box_MailBoxHead *mail_box_create(int content_sizeof,
                                      int content_allot);

mail_box_MailBoxHead *mail_box_create(int content_sizeof,
                                      int content_allot)
{
    return calloc(1, sizeof(mail_box_MailBoxHead) + content_allot * content_sizeof);
}