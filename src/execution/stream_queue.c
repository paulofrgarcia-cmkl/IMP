#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stream_queue.h>

// "head" of queue (last in)

struct stream_queue *initialize_queue()
{
    struct stream_queue *new_queue = malloc(sizeof(struct stream_queue));
    new_queue->queue = NULL;
    return new_queue;
}

/**
 * @brief Insert a stream_packet at the end of the queue.
 *
 * The "head" of the queue, i.e. the last element in and first out, is pointed
 * to by stream_queue->queue. So, to enqueue, traverse the linked list of
 * packets and append the new element at the end.
 *
 * @param q The queue to append to.
 * @param pkt The packet to append.
 */
void stream_enqueue(struct stream_queue *q, struct stream_packet *pkt)
{
    struct stream_packet *curr = q->queue;
    // If queue has no entries, simply assign this one
    if (curr == NULL)
    {
        // curr = pkt;
        q->queue = pkt;
    }
    // Otherwise, traverse to the end of the packet list and append there.
    else
    {
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = pkt;
    }
}

/**
 * @brief Get the head of the queue, without modifying the queue.
 *
 * @param q The queue to peek at.
 * @return The element at the head of the queue (NULL if queue is empty).
 */
struct stream_packet *stream_peek(struct stream_queue *q)
{
    return q->queue;
}

/**
 * @brief Remove the head element of the queue.
 *
 * FIXME: we do not yet free() the orphaned element, as it's not certain what
 * is done with used elements yet. Potential leak.
 *
 * @param q The queue to remove an element from.
 */
void stream_dequeue(struct stream_queue *q)
{
    if (q->queue != NULL)
    {
        q->queue = q->queue->next;
    }
}
