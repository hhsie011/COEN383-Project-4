#ifndef __PAGE_H__
#define __PAGE_H__

typedef struct Page {
    int number;
    int lastUsed; // for LRU
    int numRef; // for LFU and MFU
    struct Page* next;
} Page;

#endif
