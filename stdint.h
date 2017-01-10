#ifdef _MSC_VER
typedef _int8 int8_t;
typedef unsigned _int8 uint8_t;
typedef _int16 int16_t;
typedef unsigned _int16 uint16_t;
typedef _int32 int32_t;
typedef unsigned _int32 uint32_t;
typedef _int64 int64_t;
typedef unsigned _int64 uint64_t;
#else 
#include <stdint.h>
#endif