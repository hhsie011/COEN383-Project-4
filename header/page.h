#ifndef __PAGE_H__
#define __PAGE_H__

typedef struct Page {
    int number;
    int assignTime; // for FIFO
    int lastUsed; // for LRU
    int refCnt; // for LFU and MFU
    struct Page* next;
} Page;

#endif
