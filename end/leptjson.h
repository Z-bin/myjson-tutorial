#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h>

// 枚举json数据类型
typedef enum {
    LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT
} lept_type;

typedef struct lept_value lept_value;  // 前置声明

// 声明 JSON 的数据结构
struct lept_value {
    union {
        struct {lept_value *e; size_t size; }a; // 数组
        struct { char *s; size_t len; }s; // 字符串
        double n;      // 数字
    }u;

    lept_type type;
};

enum {
    LEPT_PARSE_OK = 0,              // 无错误
    LEPT_PARSE_EXPECT_VALUE,        // 若一个 JSON 只含有空白
    LEPT_PARSE_INVALID_VALUE,       // 若值不是那三种字面值
    LEPT_PARSE_ROOT_NOT_SINGULAR,   // 若一个值之后，在空白之后还有其他字符
    LEPT_PARSE_NUMBER_TOO_BIG,      // 数字溢出
    LEPT_PARSE_MISS_QUOTATION_MARK, // 引号
    LEPT_PARSE_INVALID_STRING_ESCAPE, // 无效转译
    LEPT_PARSE_INVALID_STRING_CHAR, // 无效字符串
    LEPT_PARSE_INVALID_UNICODE_HEX, //  无效Unicode
    LEPT_PARSE_INVALID_UNICODE_SURROGATE, // 只有高代理项而欠缺低代理项，或是低代理项不在合法码点范围
    LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET,// 缺少逗号/方括号的数组
};

// 初始化类型
#define lept_init(v) do { (v)->type = LEPT_NULL; } while(0)

// 解析json
int lept_parse(lept_value* v, const char* json);

// 释放内存
void lept_free(lept_value *v);

// 获取返回类型
lept_type lept_get_type(const lept_value *v);

#define lept_set_null(v) lept_free(v)

int lept_get_boolean(const lept_value *v);
void lept_set_boolean(lept_value *v, int b);

// 是否为数字类型
double lept_get_number(const lept_value *v);
void lept_set_numner(lept_value *v, double n);

const char *lept_get_string(const lept_value *v);
size_t lept_get_string_length(const lept_value *v);
void lept_set_string(lept_value *v, const char *s, size_t len);

// 数组大小
size_t lept_get_array_size(const lept_value *v);
// 获取数组元素
lept_value *lept_get_array_element(const lept_value *v, size_t index);
#endif /* LEPTJSON_H__ */


