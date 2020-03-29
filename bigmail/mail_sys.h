#pragma once
#include <stdlib.h>
#include "mail_box.h"

typedef struct {
    mail_box_MailBoxHead *mailboxes[256];
} mail_sys_MailSys;

mail_sys_MailSys *main_system_create();

void mail_system_define_mailbox(mail_sys_MailSys *system,
                                char mailbox_name,
                                int mailbox_content_sizeof,
                                int mailbox_content_allot);


mail_sys_MailSys *mail_system_create()
{
    return calloc(1, sizeof(mail_sys_MailSys));
}

void mail_system_define_mailbox(mail_sys_MailSys *system,
                                char mailbox_name,
                                int mailbox_content_sizeof,
                                int mailbox_content_allot)
{
    system->mailboxes[(int)mailbox_name]
            = mail_box_create(mailbox_content_sizeof, mailbox_content_allot);
}