#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#define GET_BIT(reg, bit)   ((reg>>bit) & 1)
#define GET_REG(reg)        (reg & 0xff)

#define SET(reg, val)        reg |= val
#define SET_BIT(reg, val)    reg |= (1<<val)

#define CLR(reg, val)        reg &= ~val
#define CLR_BIT(reg, val)    reg &= ~(1<<val)

#endif
