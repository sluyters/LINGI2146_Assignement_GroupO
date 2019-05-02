#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

#include <time.h>
#include <stdlib.h>

#include "net/rime.h"	

struct node {
	struct node *next;
	rimeaddr_t addr_via;
	uint8_t node_id;
	uint8_t n_hops;
	int timestamp;
};


/**
 * Adds the new node to the @nodes list, or update its data if it is already present
 */
void add_node(struct node **nodes, const rimeaddr_t *addr_via, uint8_t node_id, uint8_t n_hops);

/**
 * Returns the node corresponding to @node_id from @nodes
 */
void remove_node(struct node **nodes, uint8_t node_id);

/**
 * Removes all the expired nodes from @nodes
 */
void remove_expired_nodes(struct node **nodes, int max_elapsed_secs);

/**
 * Returns the node corresponding to |node_id if present in @nodes, NULL otherwise
 */
struct node *get_node(struct node *nodes, uint8_t node_id);