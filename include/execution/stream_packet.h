#ifndef STREAM_PACKET_H
#define STREAM_PACKET_H

#include <var_mapping.h>

struct stream_packet
{
    // Linked list of var_mappings; should contain one for each variable in
    // stream interface.
    struct var_mapping *args;
    struct stream_packet *next;
};

struct stream_packet *initialize_stream_packet();
struct var_mapping *get_stream_packet_arg(struct stream_packet *pkt, char *name);
void free_stream_packet(struct stream_packet *pkt);

#endif