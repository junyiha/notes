#ifndef __FLAG_H
#define __FLAG_H

#include "header.h"
#include "test_macro.h"

__BEGIN_DECLS

#define FLAG_KEY_ZERO  0
#define FLAG_KEY_EXIT  1
#define FLAG_KEY_GPUID 2

/**
 * @brief 设置标记
 * 
 * @param key 
 * @param value 
 * @return int64_t 
 */
int64_t flag_set(uint8_t key, int64_t value);

/**
 * @brief 获取标记
 * 
 * @param key 
 * @return int64_t 
 */
int64_t flag_get(uint8_t key);

__END_DECLS


#endif  // __FLAG_H