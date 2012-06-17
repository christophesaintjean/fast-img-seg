#include "unionfind.h"
#include "image.h"
#include "oracle.h"

#ifndef _SEG_H
#define _SEG_H
Forest SegIter(Image*, Oracle *);
Forest SegIter2(Image*, Oracle *);
Forest SegRec(Image*, Oracle *);
Image * colorize(Node **, size_t, size_t);
#endif
