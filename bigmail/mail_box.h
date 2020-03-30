#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define offset(of, by) ((void *)((char *)(of) + (int)(by)))

typedef struct {
    int content_sizeof;
    uint16_t lagging;
    uint16_t _Atomic leading;
} mail_box_MailBoxHead;

typedef struct {
    _Atomic bool live;
} mail_box_MailBoxEntryHead;

void mail_box_create(int content_sizeof,
                     mail_box_MailBoxHead **out_mailbox);

void mail_box_incoming_open(mail_box_MailBoxHead *mailbox,
                            void **out_content);

void mail_box_incoming_shut(mail_box_MailBoxHead *mailbox,
                            void **content);

void mail_box_outgoing_open(mail_box_MailBoxHead *mailbox,
                            void **out_content);

void mail_box_outgoing_shut(mail_box_MailBoxHead *mailbox,
                            void **content);

void mail_box_nth_entry(mail_box_MailBoxHead *mailbox,
                        int n,
                        mail_box_MailBoxEntryHead **out_entry);

void mail_box_nth_content(mail_box_MailBoxHead *mailbox,
                          int n,
                          void **out_content);


void mail_box_create(int content_sizeof,
                     mail_box_MailBoxHead **out_mailbox)
{
    *out_mailbox = calloc(1, sizeof(mail_box_MailBoxHead)
        + ((uint16_t)~0 + 1) * (content_sizeof + sizeof(mail_box_MailBoxEntryHead)));
    (*out_mailbox)->content_sizeof = content_sizeof;
}

void mail_box_incoming_open(mail_box_MailBoxHead *mailbox,
                            void **out_content)
{
    mail_box_MailBoxEntryHead *entry;
    mail_box_nth_entry(mailbox, mailbox->lagging, &entry);

    *out_content = NULL;
    if (entry->live)
        *out_content = offset(entry, sizeof(mail_box_MailBoxEntryHead));

    entry->live = false;
    ++mailbox->lagging;
}

void mail_box_incoming_shut(mail_box_MailBoxHead *mailbox,
                            void **content)
{
    /* This is only here for symmetry with outgoing operations. */
}

void mail_box_outgoing_open(mail_box_MailBoxHead *mailbox,
                            void **out_content)
{
    uint16_t n = __atomic_add_fetch(&mailbox->leading, 1, __ATOMIC_RELAXED) - 1;
    mail_box_nth_content(mailbox, n, out_content);
}

void mail_box_outgoing_shut(mail_box_MailBoxHead *mailbox,
                            void **content)
{
    mail_box_MailBoxEntryHead *entry
        = offset(*content, -sizeof(mail_box_MailBoxEntryHead));
    entry->live = true;
}

void mail_box_nth_entry(mail_box_MailBoxHead *mailbox,
                        int n,
                        mail_box_MailBoxEntryHead **out_entry)
{
    *out_entry = offset(mailbox, sizeof(mail_box_MailBoxHead)
        + n * (sizeof(mail_box_MailBoxEntryHead) + mailbox->content_sizeof));
}

void mail_box_nth_content(mail_box_MailBoxHead *mailbox,
                          int n,
                          void **out_content)
{
    *out_content = offset(mailbox, sizeof(mail_box_MailBoxHead)
        + n * (sizeof(mail_box_MailBoxEntryHead) + mailbox->content_sizeof)
        + sizeof(mail_box_MailBoxEntryHead));
}