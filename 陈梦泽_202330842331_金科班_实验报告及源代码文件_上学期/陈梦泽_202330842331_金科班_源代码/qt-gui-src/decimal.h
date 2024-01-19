#ifndef DECIMAL_H
#define DECIMAL_H



#include <iostream>
#include <list>  //链表
#include <tuple> //数据打包
#include <string>
const int div_precision = 10; // 精确到小数点后div_precision位
const int div_eps = 6;        // 除数小于1e-(div_eps)时报错
using namespace std;

list<uint8_t>::iterator step_back(list<uint8_t>::iterator it);
tuple<string, size_t, bool> analyze(string _instr);

struct Decimal
{
    // eg:
    // 代表的数字：-123.456
    // positive:  false
    // digits:    123 456
    // ones_place:  ↑
    bool positive;
    list<uint8_t> digits;
    list<uint8_t>::iterator ones_place;

    // 初始化 输入 输出
    Decimal() : Decimal("0") {} // 默认值为0
    Decimal(string _input) { input(_input); }
    Decimal(int _index) { input_pow10(_index); }
    void input(string _input) { input(analyze(_input)); } // 用字符串初始化Decimal对象
    void input(tuple<string, size_t, bool>);              // 中间函数
    void input_pow10(int _index);                         // 初始化为10^n
    string print();

    // 运算
    void cut_down();
    void align(Decimal &other);
    Decimal get_opposite();
    Decimal operator+(Decimal &other);
    Decimal operator-(Decimal &other);
    Decimal operator*(Decimal &other);
    pair<Decimal, bool> operator/(Decimal &other);
    void copy(Decimal &other); // 只接受左值 右值(比如表达式)不行
};



#endif // DECIMAL_H
