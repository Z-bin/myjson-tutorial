#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h>

// 枚举json数据类型
typedef enum {
    LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT
} lept_type;

typedef struct lept_value lept_value;
typedef struct lept_member lept_member;

// 声明 JSON 的数据结构
struct lept_value{
    union {
        struct { char *s; size_t len; }s;        // 字符串
        struct { lept_value *e; size_t size; }a; // 数组
        struct { lept_member* m; size_t size; }o;// 对象
        double n;      // 数字
    }u;

    lept_type type;
};

struct lept_member {
    char* k; size_t klen;   /* member key string, key string length */
    lept_value v;           /* member value */
};

enum {
    LEPT_PARSE_OK = 0,              // 无错误
    LEPT_PARSE_EXPECT_VALUE,        // 若一个 JSON 只含有空白
    LEPT_PARSE_INVALID_VALUE,       // 若一个值之后，在空白之后还有其他字符
    LEPT_PARSE_ROOT_NOT_SINGULAR,   // 若值不是那三种字面值
    LEPT_PARSE_NUMBER_TOO_BIG,      // 数字溢出
    LEPT_PARSE_MISS_QUOTATION_MARK, // 引号
    LEPT_PARSE_INVALID_STRING_ESCAPE, // 无效转译
    LEPT_PARSE_INVALID_STRING_CHAR, // 无效字符串
    LEPT_PARSE_INVALID_UNICODE_HEX,
    LEPT_PARSE_INVALID_UNICODE_SURROGATE,
    LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET,
    LEPT_PARSE_MISS_KEY,
    LEPT_PARSE_MISS_COLON,
    LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET
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

size_t lept_get_array_size(const lept_value* v);
lept_value* lept_get_array_element(const lept_value* v, size_t index);

size_t lept_get_object_size(const lept_value* v);
const char* lept_get_object_key(const lept_value* v, size_t index);
size_t lept_get_object_key_length(const lept_value* v, size_t index);
lept_value* lept_get_object_value(const lept_value* v, size_t index);

#endif /* LEPTJSON_H__ */


