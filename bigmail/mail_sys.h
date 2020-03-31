#pragma once
#include <stdint.h>
#include <stdlib.h>
#include "mail_box.h"

typedef struct {
    mail_box_MailBoxHead *mailboxes[(uint8_t)~0 + 1];
} mail_sys_MailSys;

static inline void mail_system_create(mail_sys_MailSys **out_system);

static inline void mail_system_define_mailbox(mail_sys_MailSys *system,
                                              char mailbox_name,
                                              int mailbox_content_sizeof);

static inline void mail_system_get_incoming(mail_sys_MailSys *system,
                                            char mailbox_name,
                                            mail_box_MailBoxHead **out_mailbox);

static inline void mail_system_get_outgoing(mail_sys_MailSys *system,
                                            char mailbox_name,
                                            mail_box_MailBoxHead **out_mailbox);


static inline void mail_system_create(mail_sys_MailSys **out_system)
{
     *out_system = calloc(1, sizeof(mail_sys_MailSys));
}

static inline void mail_system_define_mailbox(mail_sys_MailSys *system,
                                              char mailbox_name,
                                              int mailbox_content_sizeof)
{
    mail_box_create(mailbox_content_sizeof,
                    &system->mailboxes[(int)mailbox_name]);
}

static inline void mail_system_get_incoming(mail_sys_MailSys *system,
                                            char mailbox_name,
                                            mail_box_MailBoxHead **out_mailbox)
{
    *out_mailbox = system->mailboxes[(int)mailbox_name];
}

static inline void mail_system_get_outgoing(mail_sys_MailSys *system,
                                            char mailbox_name,
                                            mail_box_MailBoxHead **out_mailbox)
{
    *out_mailbox = system->mailboxes[(int)mailbox_name];
}