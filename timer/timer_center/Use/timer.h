#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C"{
#endif
#include "main.h"

extern void timer_init(void);
extern void timer_call_back(void);
extern void timer_compare(u16 a);
extern void timer_start(void);
extern void timer_stop(void);

#ifdef __cplusplus
}
#endif
#endif
