#ifndef TEST_MACRO_H
#define TEST_MACRO_H

/**
 * @brief 返回旧值
 * 
 */
#define _atomic_load(ptr)  __sync_and_and_fetch((ptr), *(ptr))

/**
 * @brief 设置新值
 * 
 */
#define _atomic_store(ptr, newval)  __sync_val_compare_and_swap((ptr), *(ptr), (newval))

/**
 * @brief 比较两个值
 * 
 */
#define _atomic_compare(ptr, oldval)  __sync_bool_compare_and_swap((ptr), (oldval), *(ptr))

/**
 * @brief 比较两个值，相同则用新值替换旧值
 * 
 */
#define _atomic_compare_and_swap(ptr, oldval, newval)  __sync_bool_compare_and_swap((ptr), (oldval), newval)

/**
 * @brief 加法，返回旧值
 * 
 */
#define _atomic_fetch_and_add(ptr, val)  __sync_fetch_and_add(ptr, val)

#endif  // TEST_MACRO_H