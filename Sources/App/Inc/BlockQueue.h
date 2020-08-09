#ifndef BLOCKQUEUE_H
#define BLOCKQUEUE_H

#include <stdlib.h>

class Block;

class BlockQueue 
{
    // friend classes
    friend class Planner;
    friend class Conveyor;
    
public:
    
    BlockQueue();
    
    BlockQueue(unsigned int length);

    ~BlockQueue();

    /*
     * direct accessors
     */
    Block& head();
    Block& tail();
    /*
     * pointer accessors
     */
    Block* head_ref();
    Block* tail_ref();

    void  produce_head(void);
    void  consume_tail(void);

    /*
     * queue status
     */
    bool is_empty(void) const;
    bool is_full(void) const;
    void flush_now();

    /*
     * resize
     *
     * returns true on success, or false if queue is not empty or not enough memory available
     */
    bool resize(unsigned int new_size);

protected:
    /*
     * these functions are protected as they should only be used internally
     * or in extremely specific circumstances
     */
    Block& item(unsigned int i);
    
    Block* item_ref(unsigned int i);

    unsigned int next(unsigned int item) const;
    unsigned int prev(unsigned int item) const;

    /*
     * buffer variables
     */
    unsigned int length;

    volatile unsigned int head_i;
    volatile unsigned int tail_i;
    volatile unsigned int isr_tail_i;

private:
    Block* ring;
};

#endif
