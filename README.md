# BigMail
Stupid-simple header-only multi-producer-single-consumer queue system 
for BigWorld (That's a lot of hyphens!). Fast and unsafe.

Sample program for the curious:
```
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "bigmail/mail.h"


typedef struct {
    int a;
    int b;
} Data;


void *produce(void *mail)
{
    Data *o;

    mail_MailBox *outgoing;
    mailsys_outgoing_find(mail, 'A', &outgoing);

    mailbox_outgoing_open(outgoing, &o);
    for (;;) {
        usleep(100);
        o->a = 12;
        o->b = 13;

        mailbox_outgoing_shut(outgoing, &o);
        mailbox_outgoing_open(outgoing, &o);
    }
}

void *consume(void *mail)
{
    Data *i;

    mail_MailBox *incoming;
    mailsys_incoming_find(mail, 'A', &incoming);

    for (;;) {
        usleep(100);

        mailbox_incoming_open(incoming, &i);
        while (i) {
            printf("%d\n", i->a);

            mailbox_incoming_shut(incoming, &i);
            mailbox_incoming_open(incoming, &i);
        }
    }
}

int main()
{
    mail_MailSys *mail;

    mailsys_create(&mail);
    mailsys_define_mailbox(mail, 'A', sizeof(Data));

    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1, NULL, &produce, (void *)mail);
    pthread_create(&thread_2, NULL, &consume, (void *)mail);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
}
```

## Structure
Sets ("Mail Systems") of queues ("Mailboxes") are defined by unique 
characters, and accessed as either producers ("Outgoing"), or consumers
("Incoming"). Outgoing mailboxes can be accessed via multiple threads,
whereas incoming mailboxes should only be accessed through a single
thread.

## Implementation
Mailbox sizes are hardcoded to be 2^16. Content is stored in a single
contiguous area, delimited by boolean values stating whether the 
following element is ready to be read (or, "live") or not ("dead").

When attempting to consume from an incoming mailbox, if the next
element is live then the lagging pointer is incremented and the current
value is consumed. The element is marked as dead later.

When attempting to produce to an outgoing mailbox, the leading pointer
is incremented atomically and the previous index is owned and produced
later. The element is marked as live later as well.
