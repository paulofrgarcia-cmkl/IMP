#ifndef STREAM_QUEUE_H
#define STREAM_QUEUE_H

#include <stream_packet.h>

struct stream_queue
{
    struct stream_packet *queue;
};

// Push an element to back of queue; S_COMMIT
void stream_enqueue(struct stream_queue *q, struct stream_packet *pkt);
// Return element from front of queue; S_PULL
struct stream_packet *stream_peek(struct stream_queue *q);
// Delete element from front of queue; S_SINK
void stream_dequeue(struct stream_queue *q);

struct stream_queue *initialize_queue();

#endif