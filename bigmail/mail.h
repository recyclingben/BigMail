#pragma once
#include "mail_box.h"
#include "mail_sys.h"

typedef mail_sys_MailSys     mail_MailSys;
typedef mail_box_MailBoxHead mail_MailBox;

#define mailsys_create(out_mail_system) mail_system_create(out_mail_system);
#define mailsys_define_mailbox(mail_system, mailbox_name, content_sizeof) mail_system_define_mailbox(mail_system, mailbox_name, content_sizeof);
#define mailsys_incoming_find(mail_system, mailbox_name, out_incoming) mail_system_get_incoming(mail_system, mailbox_name, out_incoming)
#define mailsys_outgoing_find(mail_system, mailbox_name, out_outgoing) mail_system_get_outgoing(mail_system, mailbox_name, out_outgoing)
#define mailbox_incoming_open(mail_system, content) mail_box_incoming_open(mail_system, (void **)content)
#define mailbox_outgoing_open(mail_system, content) mail_box_outgoing_open(mail_system, (void **)content)
#define mailbox_incoming_shut(mail_system, content) mail_box_incoming_shut(mail_system, (void **)content)
#define mailbox_outgoing_shut(mail_system, content) mail_box_outgoing_shut(mail_system, (void **)content)