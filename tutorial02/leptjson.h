#ifndef LEPTJSON_H__
#define LEPTJSON_H__

// 枚举json数据类型
typedef enum {
    LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT
} lept_type;

// 声明 JSON 的数据结构
typedef struct {
    double n;
    lept_type type;
}lept_value;

enum {
    LEPT_PARSE_OK = 0,              // 无错误
    LEPT_PARSE_EXPECT_VALUE,        // 若一个 JSON 只含有空白
    LEPT_PARSE_INVALID_VALUE,       // 若一个值之后，在空白之后还有其他字符
    LEPT_PARSE_ROOT_NOT_SINGULAR,   // 若值不是那三种字面值
    LEPT_PARSE_NUMBER_TOO_BIG,      // 数字溢出
};

// 解析json
int lept_parse(lept_value* v, const char* json);

// 获取返回类型
lept_type lept_get_type(const lept_value *v);

// 是否为数字类型
double lept_get_number(const lept_value *v);


#endif /* LEPTJSON_H__ */


