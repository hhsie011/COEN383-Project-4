#ifndef __PAGE_H__
#define __PAGE_H__

typedef struct Page {
    int lastUsed; // for LRU
    int hits; // for LFU and MFU
    struct Page* next;
} Page;

#endif
