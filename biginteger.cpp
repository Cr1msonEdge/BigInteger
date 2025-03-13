#include "biginteger.h"
#include <stdexcept>

const char* MAX_DIGIT_CH = "4294967296"; //2^32 , 10 symbs
const unsigned long long MAX_DIGIT_INT = 4294967296;
const int CELL_SIZE = 10; // number of digits in 2^32
const unsigned int td = 32;

BigInteger::BigInteger()
{
    count_ = 1;
    minus_ = false;
    digits_ = new unsigned int[1];
    digits_[0] = 0;
}

BigInteger::BigInteger(const std::string number)
{
    minus_ = false;
    std::string tmp = number;
    int stSize = number.size();
    if (number[0] == '-')
    {
        minus_ = true;
        stSize -= 1;
        tmp.erase(0, 1); // erasing minus sign

    }
    if (tmp == "")
    {
        throw std::invalid_argument("Wrong argument input.");
    }
    while (tmp[0] == '0' && stSize > 1)
    {
        tmp.erase(0, 1);
    }

    if (tmp[0] == '0' && stSize == 1)
    {
        digits_ = new unsigned int[1];
        minus_ = false;
        count_ = 1;
        digits_[0] = 0;
    }
    for (size_t i = 0; i < tmp.size(); ++i)
    {
        if (!isNumber(tmp[i]))
        {
            throw std::invalid_argument("Wrong argument input.");
        }
    }
    while (tmp != "0")
    {
        divideMAX(tmp);
        ++count_;
    }
    digits_ = new unsigned int[count_];
    tmp = number;
    if (tmp[0] == '-')
    {
        tmp.erase(0, 1);
        minus_ = true;
    }
    for (int i = 0; i < count_; ++i)
    {
        digits_[i] = divideMAX(tmp);
    }
}

BigInteger::BigInteger(long long number)
{
    if (number < 0)
    {
        number *= -1;
        minus_ = true;
    }
    else
    {
        minus_ = false;
    }
    count_ = 1;
    if (number / MAX_DIGIT_INT)
    {
        ++count_;
    }
    digits_ = new unsigned int[count_];
    digits_[0] = number % MAX_DIGIT_INT;
    if (count_ == 2)
    {
        digits_[1] = number / MAX_DIGIT_INT;
    }
}

BigInteger::BigInteger(long number)
{
    if (number < 0)
    {
        number *= -1;
        minus_ = true;
    }
    else
    {
        minus_ = false;
    }
    count_ = 1;
    if (number / MAX_DIGIT_INT)
    {
        ++count_;
    }
    digits_ = new unsigned int[count_];
    digits_[0] = number % MAX_DIGIT_INT;
    if (count_ == 2)
    {
        digits_[1] = number / MAX_DIGIT_INT;
    }
}

BigInteger::BigInteger(unsigned long long number)
{
    minus_ = false;
    count_ = 1;
    if (number / MAX_DIGIT_INT)
    {
        ++count_;
    }
    digits_ = new unsigned int[count_];
    digits_[0] = number % MAX_DIGIT_INT;
    if (count_ == 2)
    {
        digits_[1] = number / MAX_DIGIT_INT;
    }
}

BigInteger::BigInteger(unsigned long number)
{
    minus_ = false;
    count_ = 1;
    if (number / MAX_DIGIT_INT)
    {
        ++count_;
    }
    digits_ = new unsigned int[count_];
    digits_[0] = number % MAX_DIGIT_INT;
    if (count_ == 2)
    {
        digits_[1] = number / MAX_DIGIT_INT;
    }
}

BigInteger::BigInteger(int number)
{
    if (number < 0)
    {
        number *= -1;
        minus_ = true;
    }
    else
    {
        minus_ = false;
    }
    count_ = 1;
    digits_ = new unsigned int[count_];
    digits_[0] = number % MAX_DIGIT_INT;
}

BigInteger::BigInteger(unsigned int number)
{
    minus_ = false;
    count_ = 1;
    digits_ = new unsigned int[count_];
    digits_[0] = number % MAX_DIGIT_INT;
}

BigInteger::~BigInteger()
{
    minus_ = false;
    if (digits_)
    {
        delete[] digits_;
        digits_ = nullptr;
    }
    count_ = 0;
}

BigInteger::BigInteger(const BigInteger& X) : count_(X.count_), minus_(X.minus_)
{
    digits_ = new unsigned int[count_];
    for (int i = 0; i < count_; ++i)
    {
        digits_[i] = X.digits_[i];
    }
}

BigInteger::BigInteger(BigInteger&& X) noexcept
{
    count_ = X.count_;
    minus_ = X.minus_;
    digits_ = X.digits_;
    X.digits_ = nullptr;
    X.count_ = 0;
}

std::ostream& operator<< (std::ostream& out, const BigInteger& digit)
{
    if (digit.minus_)
    {
        out << '-';
    }

    for (int i = digit.count_ - 1; i > -1; --i)
    {
        out << digit.digits_[i] << '\'';
    }
    return out;
}

int size(std::string str)
{
    int i = 0;
    while (str[i])
    {
        ++i;
    }
    return i;
}

int size(const long long a)
{
    int cnt = 0;
    long long copy = a;
    while (copy != 0)
    {
        ++cnt;
        copy /= 10;
    }
    return cnt;
}

bool isNumber(char ch)
{
    if (ch <= '9' && ch >= '0')
    {
        return true;
    }
    return false;
}

unsigned long long sToUI64(std::string str)
{
    int index = 0;
    if (str[0] == '-')
    {
        index = 1;
    }
    unsigned long long result = 0;
    while (str[index])
    {
        result = result * 10 + (str[index] - '0');
        ++index;
    }
    return result;
}

unsigned long long sToUI64(std::string str, int end)  // end - how many digits to take not including sign
{
    int index = 0;
    if (str[0] == '-')
    {
        index = 1;
        ++end;
    }
    unsigned long long result = 0;
    while (str[index] && index < end)
    {
        result = result * 10 + (unsigned long long)(str[index] - '0');
        ++index;
    }
    return result;
}

unsigned int divideMAX(std::string& str)  // saving quotient in str , return remainder
{
    if (str == "" || str == "0")
    {
        str = "0";
        return 0;
    }
    unsigned long long digit = 0;
    int tens = 1, length = 0;
    if (str.size() > CELL_SIZE)
    {
        length = CELL_SIZE;
    }
    else
    {
        length = str.size();
    }
    digit = sToUI64(str, length);
    if (str.size() < CELL_SIZE || (str.size() == CELL_SIZE && digit < MAX_DIGIT_INT))
    {
        str = "0";
        return (unsigned int)digit;
    }
    else if (str.size() == CELL_SIZE) // digit >= MAX_DIGIT_INT
    {
        str = to_string(digit / MAX_DIGIT_INT);
        return (unsigned int)(digit % MAX_DIGIT_INT);
    }
    std::string result = "";

    unsigned long long ost = digit / MAX_DIGIT_INT;
    if (ost)
    {
        result.push_back(ost + '0');
    }
    digit = (digit % MAX_DIGIT_INT) * 10 + (str[CELL_SIZE]) - '0';
    for (int i = CELL_SIZE + 1; i < str.size(); ++i)
    {
        ost = digit / MAX_DIGIT_INT;
        result.push_back(ost + '0');
        digit = (digit % MAX_DIGIT_INT) * 10 + (str[i] - '0');
    }
    ost = digit / MAX_DIGIT_INT;
    result.push_back(ost + '0');
    str = result;
    digit %= MAX_DIGIT_INT;
    return (unsigned int)digit;
}

std::string to_string(const BigInteger& a)
{
    std::string result = "0", factor = MAX_DIGIT_CH, tmp = "";
    result = to_string(a.digits_[0]);
    for (int i = 1; i < a.count_; ++i)
    {
        tmp = multiply(factor, to_string(a.digits_[i]));
        result = sum_strings(result, tmp);
        factor = multiply(factor, (std::string)MAX_DIGIT_CH);
    }
    if (result == "")
    {
        result = "0";
        return result;
    }
    if (a.minus_)
    {
        std::string finish = "-";
        finish += result;
        return finish;
    }
    return result;
}

std::string to_string(const long long a)
{
    std::string str = "", result = "";
    int i = 0;
    long long numb = a;
    if (a < 0)
    {
        str.push_back('-');
        result.push_back('-');
        ++i;
        numb *= -1;
    }
    while (numb != 0)
    {
        str.push_back('0' + numb % 10);
        numb /= 10;
    }
    for (int j = str.size() - 1; j >= i; --j)
    {
        result.push_back(str[j]);
    }
    return result;
}

std::string sum_strings(const std::string& a, const std::string& b)
{
    std::string a1 = a.length() >= b.length() ? a : b;
    std::string b1 = a1 == a ? b : a;
    std::string t = "";

    for (int i = 0; i < a1.length() - b1.length(); ++i)
    {
        t.push_back('0');
    }
    b1 = t + b1;
    t = "";
    int ost = 0;
    for (int i = a1.length() - 1; i > -1; --i)
    {
        t.push_back('0' + (a1[i] + b1[i] + ost - 2 * '0') % 10);
        ost = (a1[i] + b1[i] + ost - 2 * '0') / 10;
    }
    if (ost)
    {
        t.push_back('0' + ost);
    }
    for (int i = 0, j = t.length() - 1; i < j; ++i, --j)
    {
        std::swap(t[i], t[j]);
    }
    return t;
}

std::string multiply(std::string a, std::string b)
{

    if (a == "0" || b == "0")
    {
        return "0";
    }
    if (a == "1")
    {
        return b;
    }
    if (b == "1")
    {
        return a;
    }

    std::string mresult;
    std::string tempresult;
    long long int lena = a.length(), lenb = b.length();
    short int numb;
    long long int coz = 0;
    for (int i = lenb - 1; i >= 0; --i)
    {
        tempresult = "0";
        numb = b[i] - '0';
        for (int j = 0; j < numb; ++j)
        {
            tempresult = sum_strings(tempresult, a);
        }
        for (int k = 0; k < coz; ++k)
        {
            tempresult = tempresult + "0";
        }
        ++coz;

        mresult = sum_strings(mresult, tempresult);
    }

    return no_zeros(mresult);
}

std::string no_zeros(std::string a)
{
    std::string result = "";
    short int flag = 0;
    for (int i = 0; i < a.length(); ++i)
    {

        if (flag == 1)
        {
            result += a[i];
        }
        if (flag == 0 && a[i] != '0')
        {
            flag = 1;
            result += a[i];
        }

    }
    return result;
}

void BigInteger::bitter()
{
    if (minus_ == true)
    {
        for (unsigned int i = 0; i < count_; ++i)
        {
            digits_[i] = ~digits_[i];
        }
        --(*this);
    }
}

void BigInteger::badZeros()  // deleting zeros
{
    bool checker = false;
    unsigned int index = 0;

    for (int i = count_ - 1; i > 0; --i)
    {
        if (!digits_[i])
        {
            checker = true;
            ++index;
        }
        else
        {
            break;
        }
    }
    
    if (checker)
    {
        unsigned int* tmp = new unsigned int[count_ - index];
        for (int i = count_ - index - 1; i > -1; --i)
        {
            tmp[i] = digits_[i];
        }
        delete[] digits_;
        digits_ = tmp;
        count_ -= index;
    }
    if (minus_ && count_ == 1 && digits_[0] == 0)
    {
        minus_ = false;
    }
}

BigInteger& BigInteger::operator= (const BigInteger& a)
{
    if (this != &a)
    {
        minus_ = a.minus_;
        if (digits_)
        {
            delete[] digits_;
        }
        count_ = a.count_;
        digits_ = new unsigned int[count_];
        for (unsigned int i = 0; i < count_; ++i)
        {
            digits_[i] = a.digits_[i];
        }
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////

bool BigInteger::operator== (const BigInteger& a) const
{
    if (count_ == 1 && a.count_ == 1 && digits_[0] == 0 && a.digits_[0] == 0)
    {
        return true;
    }
    if (minus_ != a.minus_)
    {
        return false;
    }
    if (count_ != a.count_)
    {
        return false;
    }
    for (int i = 0; i < count_; ++i)
    {
        if (digits_[i] != a.digits_[i])
        {
            return false;
        }
    }
    return true;
}

bool operator== (long long a, const BigInteger& b)
{
    return ((BigInteger)a == b);
}

bool BigInteger::operator != (const BigInteger& a) const
{
    return !(*this == a);
}

bool BigInteger::operator> (const BigInteger& a)
{
    if (minus_ == false && a.minus_ == true)
    {
        return true;
    }
    else if (minus_ == true && a.minus_ == false)
    {
        return false;
    }
    else if (minus_ == false && a.minus_ == false)
    {
        if (count_ > a.count_)
        {
            return true;
        }
        else if (count_ < a.count_)
        {
            return false;
        }
        else
        {
            for (int i = count_ - 1; i >= 0; --i)
            {
                if (digits_[i] > a.digits_[i])
                {
                    return true;
                }
            }
        }
        return false;  // numbers are equal
    }
    else 
    {
        if (count_ < a.count_)
        {
            return true;
        }
        else if (count_ > a.count_)
        {
            return false;
        }
        else
        {
            for (int i = count_ - 1; i >= 0; --i)
            {
                if (digits_[i] < a.digits_[i])
                {
                    return true;
                }
            }
        }
        return false;  // numbers are equal
    }
}

bool BigInteger::operator< (const BigInteger& a)
{
    if (minus_ == false && a.minus_ == true)
    {
        return false;
    }
    else if (minus_ == true && a.minus_ == false)
    {
        return true;
    }
    else if (minus_ == false && a.minus_ == false)
    {
        if (count_ < a.count_)
        {
            return true;
        }
        else if (count_ < a.count_)
        {
            return false;
        }
        else
        {
            for (int i = count_ - 1; i >= 0; --i)
            {
                if (digits_[i] < a.digits_[i])
                {
                    return true;
                }
            }
        }
        return false; 
    }
    else
    {
        if (count_ < a.count_)
        {
            return false;
        }
        else if (count_ > a.count_)
        {
            return true;
        }
        else
        {
            for (int i = count_ - 1; i >= 0; --i)
            {
                if (digits_[i] > a.digits_[i])
                {
                    return true;
                }
            }
        }
        return false;
    }
}

bool BigInteger::operator<= (const BigInteger& a)
{
    return !(*this > a);
}

bool BigInteger::operator>= (const BigInteger& a)
{
    return !(*this < a);
}

const BigInteger& BigInteger::operator+() const
{
    return *this;
}

BigInteger BigInteger::operator-() const
{
    if (*this == 0)
    {
        return *this;
    }

    BigInteger a = *this;
    a.minus_ = !minus_;
    return a;
}

//////////////////////////////////////////////////////////////////////

BigInteger& BigInteger::operator++()
{
    bool ost = false;
    if (!minus_)
    {
        for (int i = 0; i < count_; ++i)
        {
            if (digits_[i] != MAX_DIGIT_INT - 1)
            {
                ++digits_[i];
                ost = false;
                break;
            }
            else if ((digits_[i] == MAX_DIGIT_INT - 1))
            {
                digits_[i] = 0;
                ost = true;
            }
        }
        if (ost)
        {
            ++count_;
            unsigned int* digits_tmp = new unsigned int[count_];
            for (int i = 0; i < count_ - 1; ++i)
            {
                digits_tmp[i] = 0;
            }
            digits_tmp[count_ - 1] = 1;
            delete[] digits_;
            digits_ = digits_tmp;
        }
    }
    else
    {
        for (int i = 0; i < count_; ++i)
        {
            if (digits_[i] != 0)
            {
                --digits_[i];
                break;
            }
            else if ((digits_[i] == 0))
            {
                digits_[i] = MAX_DIGIT_INT - 1;
                ost = true;
            }
        }
        if (ost)
        {
            --count_;
            unsigned int* digits_tmp = new unsigned int[count_];
            for (int i = 0; i < count_; ++i)
            {
                digits_tmp[i] = MAX_DIGIT_INT - 1;
            }
            delete[] digits_;
            digits_ = digits_tmp;
        }
    }
    if (count_ == 1 && digits_[0] == 0)
    {
        minus_ = false;
    }
    return *this;
}

BigInteger& BigInteger::operator--()
{
    if (count_ == 1 && digits_[0] == 0)
    {
        minus_ = true;
        digits_[0] = 1;
        return *this;
    }
    if (!minus_)
    {
        minus_ = true;
        ++(*this);
        minus_ = false;
    }
    else
    {
        minus_ = false;
        ++(*this);
        minus_ = true;
    }
    return *this;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger tmp = *this;
    ++(*this);
    return tmp;
}

BigInteger BigInteger::operator--(int)
{
    BigInteger tmp(*this);
    --(*this);
    return tmp;
}

BigInteger& BigInteger::sum(const BigInteger& a)
{
    BigInteger copy1 = *this, copy2 = a;
    BigInteger result;
    delete[] result.digits_;
    int j = 0;
    int cnt = 0;
    unsigned int ost = 0;
    if (a.count_ < count_)
    {
        copy2.addZero(count_ - a.count_);
        cnt = count_;
    }
    else if (count_ < a.count_)
    {
        copy1.addZero(a.count_ - count_);
        cnt = a.count_;
    }
    else
    {
        cnt = count_;
    }
    result.count_ = cnt;
    result.digits_ = new unsigned int[result.count_];
    for (int i = 0; i < result.count_; ++i)
    {
        result.digits_[i] = 0;
    }
    for (; j < cnt; ++j)
    {
        result.digits_[j] = ((unsigned long long)copy1.digits_[j] + copy2.digits_[j] + ost) % MAX_DIGIT_INT;
        ost = ((unsigned long long)copy1.digits_[j] + copy2.digits_[j] + ost) / MAX_DIGIT_INT;
    }
    *this = result;
    badZeros();
    return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& a)
{
    if (-*this == a)
    {
        *this = (BigInteger)0;
        return *this;
    }
    if (!minus_ && !a.minus_)
    {
        *this = this->sum(a);
        minus_ = false;
        return *this;
    }
    else if (minus_ && a.minus_)
    {
        *this = -this->sum(-a);
        minus_ = true;
        return *this;
    }
    else if (!minus_ && a.minus_)
    {
        if (*this < -a)  //1 += -2
        {
            *this = (-a) - *this;
            minus_ = true;
            return *this;
        }
        else  //2 += -1
        {
            *this = *this - (-a);
            return *this;
        }
    }
    else  //minus_ && !a.minus
    {
        if ((-*this) > a)//-100 += 2
        {
            *this = -*this - a;
            minus_ = true;
            return *this;
        }
        else  // -1 + 2
        {
            *this = a - (-*this);
            minus_ = false;
            return *this;
        }
    }
}

BigInteger& BigInteger::dif(const BigInteger& a)
{
    BigInteger copy = a;
    BigInteger result;
    int j = 0;
    int ost = 0;
    result.count_ = count_;
    result.digits_ = new unsigned int[result.count_];
    for (int i = 0; i < result.count_; ++i)
    {
        result.digits_[i] = 0;
    }
    if (a.count_ < count_)
    {
        copy.addZero(count_ - a.count_);
    }
    int cnt = count_;
    for (; j < cnt; ++j)
    {
        result.digits_[j] = ((long long)digits_[j] - copy.digits_[j] + ost) % MAX_DIGIT_INT;
        ost = ((long long)digits_[j] - copy.digits_[j] + ost) / MAX_DIGIT_INT;
    }
    *this = result;
    badZeros();
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& a)
{
    BigInteger copy = a;
    if (*this == a)
    {
        *this = (BigInteger)0;
        return *this;
    }
    else if (!minus_ && !a.minus_)
    {
        if (*this > a)  
        {
            this->dif(a);
            minus_ = false;
            return *this;
        }
        else  
        {
            *this = copy.dif(*this);
            minus_ = true;
            return *this;
        }
    }
    else if (minus_ && a.minus_)
    {
        if (*this > a)
        {
            *this = (-copy).dif(-*this);
            return *this;
        }
        else
        {
            *this = -this->dif(-copy);
            minus_ = true;
            return *this;
        }
    }
    else if (!minus_ && a.minus_)
    {
        *this = *this + (-a);
        minus_ = false;
        return *this;
    }
    else
    {
        *this = -*this + a;
        minus_ = true;
        return *this;
    }
}

BigInteger BigInteger::operator=(BigInteger&& a) noexcept
{
    if (this != &a)
    {
        count_ = a.count_;
        a.count_ = 0;
        minus_ = a.minus_;
        a.minus_ = false;
        delete[] digits_;
        digits_ = a.digits_;
        a.digits_ = nullptr;
    }
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger& a) const
{
    BigInteger result = *this;
    result += a;
    return result;
}

BigInteger operator+(long a, const BigInteger& b)
{
    return (BigInteger)a + b;
}

BigInteger BigInteger::operator-(const BigInteger& a) const
{
    BigInteger result = *this;
    result -= a;
    return result;
}

BigInteger operator-(long a, const BigInteger& b)
{
    return (BigInteger)a - b;
}

BigInteger BigInteger::operator~()
{
    BigInteger result = *this;
    result.bitter();
    for (unsigned int i = 0; i < count_; ++i)
    {
        result.digits_[i] = ~digits_[i];
    }
    result.bitter();
    result.minus_ = !minus_;
    result.bitter();
    result.badZeros();
    return result;
}

BigInteger BigInteger::operator&(const BigInteger& a) const
{
    BigInteger copy1, copy2, result;
    int index = count_ < a.count_ ? count_ : a.count_;
    if (count_ < a.count_)
    {
        copy1 = *this;
        copy2 = a;
    }
    else
    {
        copy1 = a;
        copy2 = *this;
    }
    copy1.bitter();
    copy2.bitter();
    result.count_ = copy2.count_;
    result.digits_ = new unsigned int[result.count_];
    for (int i = 0; i < copy1.count_; ++i)
    {
        result.digits_[i] = copy1.digits_[i] & copy2.digits_[i];
    }
    if (!copy1.minus_)
    {
        for (int i = copy1.count_; i < copy2.count_; ++i)
        {
            result.digits_[i] = 0;
        }
    }
    else
    {
        for (int i = copy1.count_; i < copy2.count_; ++i)
        {
            result.digits_[i] = copy2.digits_[i];
        }
    }
    result.minus_ = copy1.minus_ && copy2.minus_;
    result.bitter();
    return result;
}

BigInteger& BigInteger::operator&=(const BigInteger& a)
{
    BigInteger result = *this & a;
    *this = result;
    return *this;
}

BigInteger BigInteger::operator|(const BigInteger& a) const
{
    BigInteger copy1, copy2, result;//copy1 - меньший по количеству count_
    int index = count_ < a.count_ ? count_ : a.count_;
    if (count_ < a.count_)
    {
        copy1 = *this;
        copy2 = a;
    }
    else
    {
        copy1 = a;
        copy2 = *this;
    }
    copy1.bitter();
    copy2.bitter();
    result.count_ = copy2.count_;
    result.digits_ = new unsigned int[result.count_];
    for (int i = 0; i < copy1.count_; ++i)
    {
        result.digits_[i] = copy1.digits_[i] | copy2.digits_[i];
    }
    if (!copy1.minus_)
    {
        for (int i = copy1.count_; i < copy2.count_; ++i)
        {
            result.digits_[i] = copy2.digits_[i];
        }
    }
    else
    {
        for (int i = copy1.count_; i < copy2.count_; ++i)
        {
            result.digits_[i] = 1;
        }
    }
    result.minus_ = copy1.minus_ || copy2.minus_;
    result.bitter();
    return result;
}

BigInteger& BigInteger::operator|=(const BigInteger& a)
{
    BigInteger result = *this | a;
    *this = result;
    return *this;
}

BigInteger& BigInteger::operator|= (long long a)
{
    return *this |= BigInteger(a);
}

BigInteger BigInteger::operator|(long long a) const
{
    BigInteger result = *this;
    return result |= BigInteger(a);
}

BigInteger& BigInteger::operator^=(const BigInteger& a)
{
    BigInteger copy1, copy2, result;//copy1 - меньшее
    if (count_ < a.count_)
    {
        copy1 = *this;
        copy2 = a;
    }
    else
    {
        copy1 = a;
        copy2 = *this;
    }
    copy1.bitter();
    copy2.bitter();
    result.count_ = copy2.count_;
    delete[] result.digits_;
    result.digits_ = new unsigned int[result.count_];
    for (int i = 0; i < copy1.count_; ++i)
    {
        result.digits_[i] = copy1.digits_[i] ^ copy2.digits_[i];
    }
    if (!copy1.minus_)
    {
        for (int i = copy1.count_; i < copy2.count_; ++i)
        {
            result.digits_[i] = copy2.digits_[i];
        }
    }
    else
    {
        for (int i = copy1.count_; i < copy2.count_; ++i)
        {
            result.digits_[i] = ~copy2.digits_[i];
        }
    }
    result.bitter();
    result.minus_ = copy1.minus_ ^ copy2.minus_;
    result.bitter();
    *this = result;
    return *this;
}

BigInteger& BigInteger::operator^= (long long a)
{
    return *this ^= BigInteger(a);
}

BigInteger BigInteger::operator^(const BigInteger& a) const
{
    BigInteger result = *this;
    result ^= a;
    return result;
}

BigInteger BigInteger::operator^(long long a) const
{
    BigInteger result = *this;
    return result ^= BigInteger(a);
}

BigInteger& BigInteger::operator<<=(unsigned int a)
{
    if (a == 0)
    {
        return *this;
    }
    int z = a / td;
    int s = a % td;
    unsigned int* tmp = new unsigned int[count_ + z + 1];
    for (int k = 0; k < count_ + z + 1; ++k)
    {
        tmp[k] = 0;
    }
    tmp[z] = digits_[0] << s;
    for (int i = 1; i < count_; ++i)
    {
        tmp[z + i] = (digits_[i - 1] >> (td - s)) + (digits_[i] << s);
    }
    tmp[z + count_] = (digits_[count_ - 1] >> (td - s));

    delete[] digits_;
    count_ += (z + 1);
    digits_ = tmp;
    this->badZeros();
    return *this;
}

BigInteger BigInteger::operator<<(unsigned int a) const
{
    BigInteger result = *this;
    result <<= a;
    return result;
}

BigInteger& BigInteger::operator>>=(unsigned int a)
{
    if (a == 0)
    {
        return *this;
    }
    int z = a / td;
    if (z >= count_)
    {
        *this = 0;
        return *this;
    }
    int s = a % td;

    unsigned int* tmp = new unsigned int[count_ - z];
    
    tmp[count_ - z - 1] = digits_[count_ - 1] >> s;
    for (int i = z; i < count_ - 1; ++i)
    {
        tmp[i - z] = (digits_[i + 1] << (td - s)) + (digits_[i] >> s);
    }
    delete[] digits_;
    count_ -= (z);
    digits_ = tmp;
    this->badZeros();
    if (minus_)
    {
        --* this;
    }
    return *this;
}

BigInteger BigInteger::operator>>(unsigned int a) const
{
    BigInteger result = *this;
    result >>= a;
    return result;
}

BigInteger& BigInteger::operator*= (const BigInteger& a) {
    if (*this == (BigInteger)0 || a == (BigInteger)0) {
        *this = (BigInteger)0;
        return *this;
    }
    ///////////////////////////////////////////////
    BigInteger result;
    delete[] result.digits_;
    result.count_ = count_ + a.count_ + 1;
    result.minus_ = (minus_ + a.minus_) % 2;// XOR
    result.digits_ = new unsigned int[result.count_];
    unsigned long long tmp = 0;
    unsigned int ost = 0;
    for (int i = 0; i < result.count_; ++i) {
        result.digits_[i] = 0;
    }
    for (int j = 0; j < a.count_; ++j) {
        if (a.digits_[j] == 0) {
            result.digits_[j + count_] = 0;
        }
        else {
            ost = 0;
            for (int k = 0; k < count_; ++k) {
                tmp = (unsigned long long) digits_[k] * a.digits_[j] + result.digits_[k + j] + ost;
                result.digits_[k + j] = tmp % MAX_DIGIT_INT;
                ost = tmp / MAX_DIGIT_INT;
            }
            result.digits_[j + count_] = ost;
        }
    }
    *this = result;
    badZeros();
    return *this;
}

BigInteger BigInteger::operator*(const BigInteger& a) const
{
    BigInteger result;
    result.digits_[0] = 1;
    result *= *this;
    result *= a;
    return result;
}

BigInteger operator*(long a, const BigInteger& b)
{
    return (BigInteger)a * b;
}

BigInteger& BigInteger::addZero(int cnt)
{
    BigInteger result;
    unsigned int* tmp = new unsigned int[count_ + cnt];
    for (int i = 0; i < count_; ++i)
    {
        tmp[i] = digits_[i];
    }

    for (int j = count_; j <= count_ + cnt - 1; ++j)
    {
        tmp[j] = 0;
    }
    delete[] digits_;
    count_ += cnt;
    digits_ = tmp;
    return *this;
}

BigInteger& BigInteger::operator/= (const BigInteger& a)
{
    if (a == 0)
    {
        throw std::invalid_argument("Wrong argument input.");
    }
    if (a == 1)
    {
        return *this;
    }
    if (a == -1)
    {
        minus_ = !minus_;
        return *this;
    }
    if (a.count_ == 1)
    {

        BigInteger result;
        delete[] result.digits_;
        result.count_ = count_;
        result.digits_ = new unsigned int[result.count_];
        for (int i = 0; i < result.count_; ++i)
        {
            result.digits_[i] = 0;
        }
        unsigned long long tmp = 0;
        unsigned long long lt = a.digits_[0];
        for (int j = result.count_ - 1; j >= 0; --j)
        {
            result.digits_[j] = (tmp * MAX_DIGIT_INT + digits_[j]) / lt;
            tmp = (tmp * MAX_DIGIT_INT + digits_[j]) % lt;
        }
        result.minus_ = ((unsigned char)minus_ + a.minus_) % 2;
        *this = result;
        return *this;
    }
    //int n = a.count_, m = count_ - a.count_;
    int cnt = count_;
    BigInteger result;
    delete[] result.digits_;
    result.count_ = count_ - a.count_ + 1;
    result.digits_ = new unsigned int[result.count_];
    BigInteger copy2 = a;

    ////////////////////////////////////////////////////////d1
    
    unsigned long long d = MAX_DIGIT_INT / (a.digits_[a.count_ - 1] + 1);

    *this *= d;
    if (count_ <= cnt)
    {
        addZero();
    }
    copy2 *= d;
    unsigned long long qHat = 0, rHat = 0, tmp2 = 0, smth = 0;
    int ost = 0;
    ////////////////////////////////////////////////////////d2
    for (int j = result.count_ - 1; j >= 0; --j) //count_ - a.count_
    {
        //////////////d3
        qHat = ((unsigned long long)digits_[j + a.count_] * MAX_DIGIT_INT + digits_[j + a.count_ - 1]) / copy2.digits_[a.count_ - 1];
        rHat = ((unsigned long long)digits_[j + a.count_] * MAX_DIGIT_INT + digits_[j + a.count_ - 1]) % copy2.digits_[a.count_ - 1];
        do
        {
            if (qHat == MAX_DIGIT_INT || (qHat * (copy2.digits_[a.count_ - 2]) > (MAX_DIGIT_INT * rHat + digits_[j + a.count_ - 2])))
            {
                --qHat;
                rHat += copy2.digits_[a.count_ - 1];
            }
            else
            {
                break;
            }
        } while (rHat < MAX_DIGIT_INT);
        //////////////////////////d4
        ost = 0;
        tmp2 = 0;
        for (int i = 0; i < a.count_; ++i)
        {
            smth = qHat * copy2.digits_[i];
            tmp2 = digits_[i + j] - (smth % MAX_DIGIT_INT) - ost;
            digits_[i + j] = tmp2;
            ost = (smth / MAX_DIGIT_INT) - (tmp2 / MAX_DIGIT_INT);
        }
        ///////////////////d5
        tmp2 = digits_[j + a.count_] - ost;
        digits_[j + a.count_] = tmp2;
        result.digits_[j] = qHat;
        if (tmp2 < 0)
        {
            --result.digits_[j];
            ost = 0;
            for (int i = 0; i < a.count_; ++i)
            {
                tmp2 = digits_[i + j] + copy2.digits_[i] + ost;
                ost = tmp2 / MAX_DIGIT_INT;
                digits_[i + j] = tmp2;
            }
            digits_[j + a.count_] += ost;
        }
    }
    result.minus_ = ((unsigned char)minus_ + a.minus_) % 2;
    *this = result;
    this->badZeros();
    return *this;
}

BigInteger BigInteger::operator/ (const BigInteger& a) const
{
    BigInteger result = *this;
    result /= a;
    return result;
}

BigInteger operator/(long a, const BigInteger& b)
{
    return (BigInteger)a / b;
}

BigInteger operator%(long a, const BigInteger& b)
{
    return (BigInteger)a % b;
}

BigInteger& BigInteger::operator%= (const BigInteger& a)
{
    if (a == 0)
    {
        throw std::invalid_argument("Wrong argument input.");
    }
    if (a == 1)
    {
        return *this;
    }
    if (a == -1)
    {
        minus_ = !minus_;
        return *this;
    }
    if (a.count_ == 1)
    {
        unsigned long long d = MAX_DIGIT_INT / (a.digits_[a.count_ - 1] + 1);
        BigInteger result;
        delete[] result.digits_;
        result.count_ = count_;
        result.digits_ = new unsigned int[result.count_];
        for (int i = 0; i < result.count_; ++i)
        {
            result.digits_[i] = 0;
        }
        if (minus_ && !a.minus_)
        {
            result.minus_ = true;
        }
        else
        {
            result.minus_ = false;
        }
        unsigned long long tmp = 0;
        unsigned long long lt = a.digits_[0];
        for (int j = result.count_ - 1; j >= 0; --j)
        {
            result.digits_[j] = (tmp * MAX_DIGIT_INT + digits_[j]) / lt;
            tmp = (tmp * MAX_DIGIT_INT + digits_[j]) % lt;
        }
        *this = (BigInteger)tmp;
        minus_ = result.minus_;
        return *this;
    }

    int cnt = count_;
    BigInteger result;
    delete[] result.digits_;
    result.count_ = count_ - a.count_ + 1;
    result.digits_ = new unsigned int[result.count_];
    BigInteger copy2 = a;
    ////////////////////////////////////////////////////////d1
    unsigned long long d = MAX_DIGIT_INT / (a.digits_[a.count_ - 1] + 1);

    *this *= d;
    if (count_ <= cnt)
    {
        addZero();
    }
    copy2 *= d;
    unsigned long long qHat = 0, rHat = 0, tmp2 = 0, smth = 0;
    int ost = 0;
    ////////////////////////////////////////////////////////d2
    for (int j = result.count_ - 1; j >= 0; --j) //count_ - a.count_
    {
        //////////////d3
        qHat = ((unsigned long long)digits_[j + a.count_] * MAX_DIGIT_INT + digits_[j + a.count_ - 1]) / copy2.digits_[a.count_ - 1];
        rHat = ((unsigned long long)digits_[j + a.count_] * MAX_DIGIT_INT + digits_[j + a.count_ - 1]) % copy2.digits_[a.count_ - 1];
        do
        {
            if (qHat == MAX_DIGIT_INT || (qHat * (copy2.digits_[a.count_ - 2]) > (MAX_DIGIT_INT * rHat + digits_[j + a.count_ - 2])))
            {
                --qHat;
                rHat += copy2.digits_[a.count_ - 1];
            }
            else
            {
                break;
            }
        } while (rHat < MAX_DIGIT_INT);
        //////////////////////////d4
        ost = 0;
        tmp2 = 0;
        for (int i = 0; i < a.count_; ++i)
        {
            smth = qHat * copy2.digits_[i];
            tmp2 = digits_[i + j] - (smth % MAX_DIGIT_INT) - ost;
            digits_[i + j] = tmp2;
            ost = (smth / MAX_DIGIT_INT) - (tmp2 / MAX_DIGIT_INT);
        }
        ///////////////////d5
        tmp2 = digits_[j + a.count_] - ost;
        digits_[j + a.count_] = tmp2;
        result.digits_[j] = qHat;
        if (tmp2 < 0)
        {
            --result.digits_[j];
            ost = 0;
            for (int i = 0; i < a.count_; ++i)
            {
                tmp2 = digits_[i + j] + copy2.digits_[i] + ost;
                ost = tmp2 / MAX_DIGIT_INT;
                digits_[i + j] = tmp2;
            }
            digits_[j + a.count_] += ost;
        }
    }
    result /= d;
    *this = result;
    this->badZeros();
    return *this;
}

BigInteger BigInteger::operator% (const BigInteger& a) const
{
    BigInteger result = *this;
    result %= a;
    return result;
}
