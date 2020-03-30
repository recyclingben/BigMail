#pragma once
#include "mail_box.h"
#include "mail_sys.h"

typedef mail_sys_MailSys     mail_MailSys;
typedef mail_box_MailBoxHead mail_MailBox;

#define mailbox_incoming_open(mail_system, content) mail_box_incoming_open(mail_system, (void **)content)
#define mailbox_incoming_shut(mail_system, content) mail_box_incoming_shut(mail_system, (void **)content)
#define mailbox_outgoing_open(mail_system, content) mail_box_outgoing_open(mail_system, (void **)content)
#define mailbox_outgoing_shut(mail_system, content) mail_box_outgoing_shut(mail_system, (void **)content)