#include "flag.h"

volatile int64_t *_flag_ctx()
{
    static volatile int64_t db[256] = {0};

    return db;
}

int64_t flag_set(uint8_t key, int64_t value)
{
    return _atomic_store(_flag_ctx()+key, value);
}

int64_t flag_get(uint8_t key)
{
    return _atomic_load(_flag_ctx()+key);
}
