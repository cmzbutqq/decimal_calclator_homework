#include "decimal.h"

list<uint8_t>::iterator step_back(list<uint8_t>::iterator it)
{
    // 输入一个迭代器，返回它的上一个迭代器
    // 由于反向迭代器与正向迭代器无法互相比较，因此有了这个函数
    // 反向迭代器的.base()方法会产生偏移，所以也不行
    list<uint8_t>::iterator res = it;
    return --res;
};
// int main()
//{
//     string temp, op, input1, input2;
//     size_t n;
//     while (cin >> n)
//     {
//         getline(cin, temp);
//         for (size_t i = 0; i < n; ++i)
//         {
//             getline(cin, op);
//             getline(cin, input1);
//             getline(cin, input2);
//             Decimal a(input1), b(input2);
//             switch (op[0])
//             {
//             case '+':
//                 (a + b).print();
//                 break;
//             case '-':
//                 (a - b).print();
//                 break;
//             case '*':
//                 (a * b).print();
//                 break;
//             case '/':
//             {
//                 pair<Decimal, bool> div = a / b;
//                 if (div.second) // 除数<1e-6
//                     cout << "ERROR" << endl;
//                 else // 正常情况
//                     div.first.print();
//                 break;
//             }
//             default:
//                 throw("unknown operator");
//             }
//         }
//     }
//     return 0;
// }

tuple<string, size_t, bool> analyze(string _instr)
{
    // 分析输入的行内容
    // 返回打包的元组：
    // <剥离无关元素后的字符串（只剩下数字），个位所在索引，是否为正数>
    string content = "";
    size_t ones_index;
    bool flag_int = true, positive = true;
    for (auto it = _instr.begin(); it != _instr.end(); ++it)
    {
        // 如果当前字符为逗号，则跳过
        if (*it == ',')
            continue;
        // 如果当前字符为数字，则将其添加到content中
        if (('0' <= *it && *it <= '9'))
            content.push_back(*it);
        // 如果当前字符为负号，则将positive设置为false
        if (*it == '-')
        {
            positive = false;
        }
        // 如果当前字符为小数点，则将flag_int设置为false，并将小数点添加到content中
        if (*it == '.')
        {
            content.push_back(*it);
            flag_int = false;
        }
    }
    // 初始化小数点的位置
    ones_index = content.size();
    --ones_index;
    // 如果flag_int为true(是整数)，则直接返回
    if (flag_int)
        return make_tuple(content, ones_index, positive);
    // 否则，找到小数点的位置，并将小数点字符从content中删除
    else
    {
        while (content[ones_index] != '.')
            --ones_index;
        content.erase(ones_index, 1);
        --ones_index;
        return make_tuple(content, ones_index, positive);
    }
}

void Decimal::input(tuple<string, size_t, bool> _intuple)
{ // 用元组初始化Decimal对象
    digits.clear();
    // 设置符号位
    positive = get<2>(_intuple);
    // 将字符串转换为数字链表
    for (char ch : get<0>(_intuple))
    {
        digits.push_back(ch - '0');
    }
    // 获取个位位置
    size_t target = get<1>(_intuple);
    // 初始化ones_place
    ones_place = digits.begin();
    // 移动ones_place至个位
    for (size_t i = 0; i < target; i++)
        ++ones_place;
    // 删除多余的数字位
    cut_down();
}

void Decimal::input_pow10(int _index)
{ // 初始化为10^n
    // eg n=0
    //->   1
    // eg n=-5
    //->   0.00001
    // eg n=-1
    //->   0.1
    // eg n=5
    //->   100000
    string res = "1";
    if (_index >= 0)
    {
        for (int i = 0; i < _index; i++)
            res.push_back('0');
    }
    else
    {
        for (int i = -1; i > _index; i--)
            res = "0" + res;
        res = "0." + res;
    }
    input(res);
}

string Decimal::print()
{
    string out = "";
    // 输出可能的负号
    if (!positive)
        out.push_back('-');
    // 获取整数部分位数
    long long int int_length = 1;
    for (auto it = digits.begin(); it != ones_place; ++it)
        ++int_length;
    // 打印
    for (auto it = digits.begin(); it != digits.end();)
    {
        out.push_back('0' + int(*it));
        --int_length;
        if ((!(int_length % 3)) && (int_length > 0))
            out.push_back(',');
        if (it == ones_place)
        {
            ++it;
            if (it != digits.end())
                out.push_back('.');
        }
        else
            ++it;
    }
    cout << out << endl;
    return out; // qt版使用
}

void Decimal::cut_down()
{ // 删除开头除个位外的所有零
    // 删除末尾小数点后的所有零
    // eg:    -001234.5600
    // ->     -  1234.56
    //         0000.00560000
    // ->         0.0056
    //         0000.0000000
    // ->         0

    for (auto it = digits.begin(); it != ones_place;)
    {
        if (*it == 0)
        {
            ++it;
            digits.pop_front();
        }
        else
            break;
    }
    auto it = digits.end();
    --it;
    for (; it != ones_place;)
    {
        if (*it == 0)
        {
            --it;
            digits.pop_back();
        }
        else
            break;
    }
}

void Decimal::align(Decimal &other)
{ // 自动在 *this,other 的头尾补充0
    // 使得 *this,other 位数相等且对齐
    // eg:  001234.56
    //           0.123456000
    // ->   001234.560000000
    //      000000.123456000

    for (auto it_this = ones_place, it_other = other.ones_place;
         it_this != digits.begin() || it_other != other.digits.begin();
         --it_this, --it_other)
    { // 头部对齐
        if (it_this == digits.begin())
            digits.push_front(0);
        if (it_other == other.digits.begin())
            other.digits.push_front(0);
    }

    for (auto it_this = ones_place, it_other = other.ones_place;
         it_this != step_back(digits.end()) || it_other != step_back(other.digits.end());
         ++it_this, ++it_other)
    { // 尾部对齐
        if (it_this == step_back(digits.end()))
            digits.push_back(0);
        if (it_other == step_back(other.digits.end()))
            other.digits.push_back(0);
    }
}

Decimal Decimal::get_opposite()
{ // 返回相反数，注意返回的是右值对象
    Decimal result;
    result.copy(*this);
    result.positive = !result.positive;
    return result;
}

Decimal Decimal::operator+(Decimal &other)
{ // 左值+左值，输出右值
    Decimal res;
    align(other);
    align(res);
    other.align(res);
    res.digits.push_front(0);

    if (positive == other.positive)
    {
        //+++,-+-
        auto it_this = step_back(digits.end()),
             it_other = step_back(other.digits.end()),
             it_res = step_back(res.digits.end());
        bool carry = false; // 是否进位
        uint8_t val = 0;
        for (; it_this != step_back(digits.begin());
             --it_this, --it_other, --it_res)
        {
            val = *it_this + *it_other + (carry ? 1 : 0);
            carry = val > 9;
            *it_res = val % 10;
        }
        if (carry)
        {
            *it_res = 1;
        }
        res.positive = positive;
    }
    else
    {
        //++-,-++ -> +-+,---
        Decimal opposite = move(other.get_opposite());
        res = move(*this - opposite);
    }

    // 去除多余的0
    cut_down();
    other.cut_down();
    res.cut_down();
    //-0 -> +0
    bool is_zero = true;
    for (auto it = res.digits.begin(); it != res.digits.end(); ++it)
    {
        if (*it != 0)
        {
            is_zero = false;
            break;
        }
    }
    if (is_zero)
        res.positive = true;
    // 返回
    return res;
}

Decimal Decimal::operator-(Decimal &other)
{ // 左值-左值，输出右值
    Decimal res;
    align(other);
    align(res);
    other.align(res);

    if (positive == other.positive)
    {
        //+-+,---
        auto it_this = step_back(digits.end()),
             it_other = step_back(other.digits.end()),
             it_res = step_back(res.digits.end());
        bool borrow = false; // 是否借位
        int8_t val = 0;
        for (;
             it_this != step_back(digits.begin());
             --it_this, --it_other, --it_res)
        {
            val = *it_this - *it_other - (borrow ? 1 : 0);
            borrow = val < 0;
            val = borrow ? 10 + val : val;
            *it_res = val;
        }
        if (!borrow)
            res.positive = this->positive; // 大-小
        else
        {
            // 小-大 需要减去补码 提出负号后变成-(大减小)
            // eg
            //     037
            //  -  189
            // --------
            //     848
            //  - 1000
            // = -(1000-848)=-(大减小)

            Decimal complement;
            res.align(complement);
            complement.digits.push_front(1);
            res = complement - res;
            res.positive = !this->positive;
        }
    }
    else
    {
        //+--,--+ -> +++,-+-
        Decimal opposite = move(other.get_opposite());
        res = move(*this + opposite);
    }

    // 去除多余的0
    cut_down();
    other.cut_down();
    res.cut_down();
    //-0 -> +0
    bool is_zero = true;
    for (auto it = res.digits.begin(); it != res.digits.end(); ++it)
    {
        if (*it != 0)
        {
            is_zero = false;
            break;
        }
    }
    if (is_zero)
        res.positive = true;
    // 返回
    return res;
}

Decimal Decimal::operator*(Decimal &other)
{ // 左值*左值，输出右值
    Decimal res;
    align(other);
    align(res);
    other.align(res);

    // res的头部加0
    for (auto it_this = ones_place;
         it_this != step_back(digits.begin());
         --it_this)
        res.digits.push_front(0);

    // res的尾部加0
    for (auto it_this = ones_place;
         it_this != step_back(digits.end());
         ++it_this)
        res.digits.push_back(0);
    // 确定正负
    res.positive = (positive == other.positive);
    // 乘法实现
    auto last_this = step_back(digits.end()),
         last_other = step_back(other.digits.end()),
         last_res = step_back(res.digits.end()),
         boundary_this = step_back(digits.begin()),
         boundary_other = step_back(other.digits.begin());
    int carry = 0; // 进位
    uint8_t val = 0;
    for (auto it_this = last_this, tail_res = last_res;
         it_this != boundary_this; --it_this, --tail_res)
    { // 遍历this每一位
        auto it_other = last_other, write_res = tail_res;
        for (;
             it_other != boundary_other; --it_other, --write_res)
        { // 遍历other每一位
            val = (*it_this) * (*it_other) + carry;
            carry = val / 10;
            val %= 10;
            *write_res += val;
            carry += *write_res / 10;
            *write_res %= 10;
        }
        if (carry)
        {
            *write_res += carry;
            carry = 0;
        }
    }
    // 去除多余的0
    cut_down();
    other.cut_down();
    res.cut_down();
    // 返回
    return res;
}

pair<Decimal, bool> Decimal::operator/(Decimal &other)
{ // pair<value,if_infinite>
    // 左值/左值，输出右值
    Decimal res;

    // detect if other<10e-(div_eps)
    Decimal eps(-div_eps);
    if ((!(other - eps).positive) && (other + eps).positive)
        return make_pair(move(res), true);

    // 左右两数转换为正整数
    // eg:this: 1000
    //   other:   -0.009
    //    left: 1000 000
    //   right: 0000 009
    Decimal left, right;
    left.copy(*this);
    right.copy(other);
    left.align(right);
    left.ones_place = step_back(left.digits.end());
    right.ones_place = step_back(right.digits.end());

    // res的开头结尾加0
    for (auto it = left.digits.begin(); it != left.ones_place; ++it)
        res.digits.push_front(0);
    for (size_t i = 0; i < 11; ++i)
        res.digits.push_back(0);
    left.positive = true;
    right.positive = true;

    // 除法实现
    int index = left.digits.size() - 1;
    list<uint8_t>::iterator write = res.digits.begin();

    for (; index >= -(div_precision + 1); --index, ++write)
    { // 遍历res的每一位
        Decimal weight(index);
        Decimal minus;
        minus = move(right * weight);

        // 一个个试 直到找到这一位应该填入的数
        int to_write = 0;
        for (; to_write < 10; ++to_write)
        {
            left = move(left - minus);
            if (left.positive)
                continue;
            else
            {
                left = move(left + minus);
                break;
            }
        }
        *write = to_write;
    }

    // 四舍五入
    auto it = step_back(step_back(res.digits.end()));
    if (res.digits.back() >= 5)
        *it += 1;
    res.digits.pop_back();

    while (*it >= 10)
    {
        *it -= 10;
        --it;
        *it += 1;
    }

    // 判断正负
    res.positive = (positive == other.positive);

    // 去除多余的0
    cut_down();
    other.cut_down();
    res.cut_down();
    // 返回
    return make_pair(move(res), false);
}

void Decimal::copy(Decimal &other)
{
    // 只接受左值变量
    // 复制该Decimal变量并重新生成ones_place
    // 要复制右值Decimal变量 请使用以下做法：
    //  Decimal dec;dec=move(Decimal &&_in); // move() 没必要加 不过为了可读性还是加上了

    positive = other.positive;
    digits.clear();

    // 将other的digits中的元素复制到当前的digits中
    for (auto _it = other.digits.begin(); _it != other.digits.end(); ++_it)
        digits.push_back(*_it);

    // 初始化ones_place
    ones_place = digits.begin();

    // 将ones_place的位置对应到other的ones_place
    for (auto _it = other.digits.begin(); _it != other.ones_place; ++_it)
        ++ones_place;
}
