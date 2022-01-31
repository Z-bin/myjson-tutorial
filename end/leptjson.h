#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h>

// 枚举json数据类型
typedef enum {
    LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT
} lept_type;

// 声明 JSON 的数据结构
typedef struct {
    union {
        struct {       // 字符串
            char *s;
            size_t len;
        }s;
        double n;      // 数字
    }u;

    lept_type type;
}lept_value;

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

#endif /* LEPTJSON_H__ */


