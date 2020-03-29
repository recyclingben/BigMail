#pragma once
#include <stdlib.h>

typedef struct {
    int content_sizeof;
    int content_allot;
} mail_box_MailBoxHead;

mail_box_MailBoxHead *mail_box_create(int content_sizeof);

mail_box_MailBoxHead *mail_box_bytes_zone_1(int content_sizeof);

mail_box_MailBoxHead *mail_box_bytes_zone_2(int content_sizeof);


mail_box_MailBoxHead *mail_box_create(int content_sizeof)
{
    return calloc(1, sizeof(mail_box_MailBoxHead) + content_sizeof);
}