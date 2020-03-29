#pragma once
#include <stdint.h>
#include <stdlib.h>
#include "mail_box.h"

typedef struct {
    mail_box_MailBoxHead *mailboxes[(uint8_t)~0 + 1];
} mail_sys_MailSys;

void mail_system_create(mail_sys_MailSys **out_system);

void mail_system_define_mailbox(mail_sys_MailSys *system,
                                char mailbox_name,
                                int mailbox_content_sizeof);


void mail_system_create(mail_sys_MailSys **out_system)
{
     *out_system = calloc(1, sizeof(mail_sys_MailSys));
}

void mail_system_define_mailbox(mail_sys_MailSys *system,
                                char mailbox_name,
                                int mailbox_content_sizeof)
{
    mail_box_create(mailbox_content_sizeof,
                    &system->mailboxes[(int)mailbox_name]);
}