#pragma once
#include <stdint.h>
#include <stdlib.h>

#define offset(of, by) ((void *)((char *)(of) + (by)))

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
    uint16_t lagging;
    uint16_t _Atomic leading;
} mail_box_MailBoxHead;

void mail_box_create(int content_sizeof,
                     mail_box_MailBoxHead **out_mailbox);

void mail_box_incoming_open(mail_box_MailBoxHead *mailbox,
                            void **out_content);

void mail_box_incoming_shut(mail_box_MailBoxHead *mailbox);


void mail_box_create(int content_sizeof,
                     mail_box_MailBoxHead **out_mailbox)
{
    int mailbox_sizeof = 0;
    mailbox_sizeof += content_sizeof + sizeof(mail_box_MailBoxEntryHead);
    mailbox_sizeof *= (uint16_t)~0;
    mailbox_sizeof += sizeof(mail_box_MailBoxHead);

    *out_mailbox = calloc(1, mailbox_sizeof);
    (*out_mailbox)->content_sizeof = content_sizeof;
}

void mail_box_incoming_open(mail_box_MailBoxHead *mailbox,
                            void **out_content)
{
    int content_offset = sizeof(mail_box_MailBoxEntryHead) + mailbox->content_sizeof;
    content_offset *= mailbox->lagging;
    content_offset += sizeof(mail_box_MailBoxHead);

    mail_box_MailBoxEntryHead *entry
            = offset(mailbox, content_offset - sizeof(mail_box_MailBoxEntryHead));

    *out_content = NULL;
    if (entry->state == mail_box_ENTRY_LIVE)
        *out_content = offset(mailbox, content_offset);
}

void mail_box_incoming_shut(mail_box_MailBoxHead *mailbox)
{
    ++mailbox->lagging;
}