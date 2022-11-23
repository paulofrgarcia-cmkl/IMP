#include <stdlib.h>

#include <stream_packet.h>

struct stream_packet *initialize_stream_packet()
{
    struct stream_packet *new_pkt = malloc(sizeof(struct stream_packet));
    new_pkt->args = NULL;
    new_pkt->next = NULL;
    return new_pkt;
}

struct var_mapping *get_stream_packet_arg(struct stream_packet *pkt, char *name)
{
    struct var_mapping *curr_arg = pkt->args;
    while (curr_arg != NULL)
    {
        if (!strcmp(curr_arg->name, name))
        {
            return curr_arg;
        }
        curr_arg = curr_arg->next;
    }
    return NULL;
}

void free_stream_packet(struct stream_packet *pkt)
{
    return;
}