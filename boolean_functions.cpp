#include "boolean_function.h"

// возвращает функцию которая равна xn с размерностью dimension
// пример 1
// n = 0
// dimension = 3
// вернется функция "01010101"
// пример 2
// n = 1
// dimension = 4
// вернется функция "0011001100110011"
boolean_function boolean_function::var(size_t n, size_t dimension)
{

    size_type len = pow(2, dimension);
    int p = pow(2, n);

    std::vector<value_type> retval;
    while (retval.size() != len)
    {
        int j = 0;
        while (j < p)
        {
            retval.push_back(0);
            j++;
        }
        j = 0;
        while (j < p)
        {
            retval.push_back(1);
            j++;
        }
    }
    boolean_function f(retval);
    return f;
}

// тождественный ноль "от dimension переменных"
boolean_function boolean_function::zero(size_t dimension)
{
    std::vector<value_type> retval;
    size_type len = pow(2, dimension);
    while (retval.size() != len)
    {
        retval.push_back(0);
    }
    boolean_function f(retval);
    return f;
}

// тождественная единица "от dimension переменных"
boolean_function boolean_function::one(size_t dimension)
{
    std::vector<value_type> retval;
    size_type len = pow(2, dimension);
    while (retval.size() != len)
    {
        retval.push_back(1);
    }
    boolean_function f(retval);
    return f;
}

boolean_function boolean_function::from_anf(std::vector<value_type> v)
{
    int len = v.size();
    int** M = new int*[len];
    int i = 0, j;
    while (i < len)
    {
        M[i] = new int[len];
        j = 0;
        while (j < len)
        {
            M[i][j] = 0;
            j++;
        }
        i++;
    }
    i = 0;
    while ( i < len)
    {
        if (v[i] == false)
        {
            M[0][i] = 0;
        }
        else
        {
            M[0][i] = 1;
        }
        i++;
    }
    i = len - 2;
    while (i > -1)
    {
        j = 1;
        while ( j < (len - i))
        {
            M[j][i] = (((M[j - 1][i]) + (M[j - 1][i + 1])) % 2);
            j++;
        }
        i--;
    }

    std::vector<value_type> retval;
    i = 0;
    while(i < len)
    {
        retval.push_back(M[i][0]);
        delete[] M[i];
        i++;
    }

    boolean_function f(retval);

    delete[] M;

    return f;
}


// задает фунцию тождественного нуля от n переменных
boolean_function::boolean_function(size_t n)
{
    size_type len = pow(2, n);
    while (func.size()<len)
    {
        func.push_back(0);
    }
}

// задает фунцию от n переменных. значение равно value
// пример
// пусть value = 14, т.е. 0...00001110 в двоичной системе
// а n = 3
// тогда АНФ boolean_function будет равна x + y + xy + zx + zy + zyx
boolean_function::boolean_function(unsigned long long value, size_type n)
{
    size_type i = 0;
    while (value > 0)
    {
        func.push_back(value % 2);
        i++;
        value /= 2;
    }
    size_type len = pow(2, n);
    while (i < len)
    {
        func.push_back(0);
        i++;
    }
}

// пусть table = "01110000"
// тогда АНФ boolean_function будет равна x + y + xy + zx + zy + zyx
boolean_function::boolean_function(const std::string& table)
{
    for (size_type i = 0; i < table.size(); i++)
    {
        if (table[i] == '0')
        {
            func.push_back(false);
        }
        else
        {
            func.push_back(true);
        }
    }
}

// пусть table = {true, false, false, true};
// тогда АНФ boolean_function будет равна x + y + 1
boolean_function::boolean_function(const std::vector<value_type>& table)
{
    func = table;
}



boolean_function::boolean_function(const std::initializer_list<bool> vars)
{
    for (auto &v : vars)
    {
        func.push_back(v);
    }
}
boolean_function::boolean_function(const boolean_function& table)
{
    func = table.func;
}

boolean_function& boolean_function::operator=(const boolean_function& rhs)
{
    func = rhs.func;
    return *this;
}
// сложение по модулю 2
// если разное количество переменных - исключение
boolean_function& boolean_function::operator += (const boolean_function& rhs)
{
    if (func.size() != rhs.func.size())
    {
        throw std::length_error("Length error\n");
    }
    size_type i = 0;
    while ( i < size())
    {
        func[i] = (func[i] + rhs.func[i]) % 2;
        i++;
    }
    return *this;
}
// конъюнкция
// если разное количество переменных - исключение
boolean_function& boolean_function::operator *= (const boolean_function& rhs)
{
    if (func.size() != rhs.func.size())
    {
        throw std::length_error("Length error\n");
    }
    size_type i = 0;
    while (i < size())
    {
        func[i] = (func[i] * rhs.func[i]);
        i++;
    }
    return *this;
}

// дизъюнкция
// если разное количество переменных - исключение
boolean_function& boolean_function::operator |= (const boolean_function& rhs)
{
    if (func.size() != rhs.func.size())
    {
        throw std::length_error("Length error\n");
    }
    size_type i = 0;
    while (i<size())
    {
        if (func[i] == 1 || rhs.func[i] == 1)
        {
            func[i] = 1;
        }
        i++;
    }
    return *this;
}

// побитовое отрицание
boolean_function boolean_function::operator ~()
{
    size_type i = 0;
    while (i < size())
    {
        if (func[i] == 1)
        {
            func[i] = 0;
        }

        else
        {
            func[i] = 1;
        }
        i++;
    }
    return *this;
}

// true если функции равны
//  иначе false
bool boolean_function::operator == (const boolean_function& v) const
{
    if (size() != v.size())
    {
        bool end_1 = false;
        bool end_2 = false;
        size_type i = 0;
        size_type j = 0;
        while (1)
        {
            if (i >= func.size())
            {
                end_1 = true;
                i = 0;
            }
            if (j >= v.size())
            {
                end_2 = true;
                j = 0;
            }
            if (end_1 && end_2)
                return true;
            if (func[i] != v.func[j])
            {
                return false;
            }
            i++;
            j++;
        }
    }

    bool retval = true;
    size_type i = 0;
    while ( i < func.size())
    {
        if (func[i] != v.func[i])
        {
            retval = false;
            break;
        }
        i++;
    }
    return retval;
}

// true если одна функция сравнима и больше или равна rhs
// false если сравнима и меньше rhs
// logic_error если фунции не сравнимы
bool boolean_function::operator >= (const boolean_function& rhs) const
{
    if (size() != rhs.size())
    {
        throw std::logic_error("logic_error\n");
    }

    int bigger = 0;
    int lower = 0;
    size_type i = 0;
    while (i < size())
    {
        if (func[i] > rhs.func[i])
        {
            bigger = 1;
        }
        if (func[i] < rhs.func[i])
        {
            lower = 1;
        }
        i++;
    }
    if (bigger != 0 && lower != 0)
    {
        throw std::logic_error("logic_error\n");
    }
    else
    {
        if (((bigger != 0) && (lower == 0)) || ((bigger == 0) && (lower == 0)))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}

boolean_function::reference boolean_function::operator[](size_type ind)
{
    if ((size() == 0)||(ind < 0)||(ind >= size()))
    {
        throw std::out_of_range("out of range\n");
    }
    return func[ind];
}
boolean_function::const_reference boolean_function::operator[](size_type ind) const
{
    if ((size() == 0)||(ind < 0)||(ind >= size()))
    {
        throw std::out_of_range("out of range\n");
    }
    return func[ind];
}

boolean_function::reference boolean_function::at(size_type ind)
{
    if ((size() == 0)||(ind < 0)||(ind >= size()))
    {
        throw std::out_of_range("out of range\n");
    }
    return func[ind];
}
boolean_function::const_reference boolean_function::at(size_type ind) const
{
    if ((size() == 0)||(ind < 0)||(ind >= size()))
    {
        throw std::out_of_range("out of range\n");
    }
    return func[ind];
}

boolean_function::iterator boolean_function::begin()
{
    return func.begin();
}
boolean_function::iterator boolean_function::end()
{
    return func.end();
}

boolean_function::const_iterator boolean_function::cbegin() const
{
    return func.cbegin();
}
boolean_function::const_iterator boolean_function::cend() const
{
    return func.cend();
}

// длина столбца функции
boolean_function::size_type boolean_function::size() const throw()
{
    return func.size();
}

// количество переменных
boolean_function::size_type boolean_function::dimension() const throw()
{
    size_type retval = 0;
    int len = func.size();
    while (len > 1)
    {
        len /= 2;
        retval++;
    }
    return retval;
}

// возвращает значение функции
// пусть boolean_function задает функцию f(x, y, z)
// тогда функция вернет f(vars[0], vars[1], vars[2])
bool boolean_function::operator()(const std::vector<bool>& vars) const
{
    size_type i = 0;
    size_type retval = 0;

    while (i < vars.size())
    {
        if(i>=(sizeof(size_type) * 8))
        {
            throw std::out_of_range("out of range\n");
        }
        retval |= vars[i]<<i;
        i++;

    }

    return func[retval];
}
bool boolean_function::operator()(const std::initializer_list<bool> vars) const
{
    size_type i = 0;
    size_type retval = 0;


    for (auto &v : vars)
    {
        if(i>=(sizeof(size_type) * 8))
        {
            throw std::out_of_range("out of range\n");
        }
        retval |= v<<i;
        i++;
    }


    return func[retval];
}

///Не реализовано!!!!
// T(x1, x2, ..., xN) - текущая функция
// operator вернет новую функцию, которая равна композиции G = T(fs[0], fs[1], ..., fs[N-1])
boolean_function boolean_function::operator()(const std::vector<boolean_function>& fs) const
{
    boolean_function retval("0000000");
    return retval;
}
boolean_function boolean_function::operator()(const std::initializer_list<boolean_function> vars) const
{
    boolean_function retval("0000000");
    return retval;
}

bool boolean_function::is_monotone() const
{
    if (size() == 0)
    {
        throw std::length_error("empty\n");
    }

    if (size() == 1)
    {
        return true;
    }

    int len = func.size();
    bool retval = true;
    int i = 0;
    while (i < len - 1)
    {
        if (func[i] > func[i + 1])
        {
            retval = false;
            break;
        }
        i++;
    }
    return retval;
}
bool boolean_function::is_symmetric() const
{
    std::vector<value_type> retval;
    size_type i = func.size();
    while ( i > 0)
    {
        retval.push_back(func[i-1]);
        /*
        std::cout<<func[i - 1]<<":"<<func[func.size() - i]<<"\n";
        */
        i--;

    }

    if (retval != func)
        return false;
    else
        return true;

}
bool boolean_function::is_linear() const
{
    std::vector<value_type> f = anf();
    bool retval = true;
    int k;
    int ch;
    size_type i = 0;
    while ( i < f.size())
    {
        k = 0;
        ch = i;
        while (ch > 0)
        {
            k += ch % 2;
            ch /= 2;
        }
        if (k != 1 && i != 0)
        {
            if (f[i] != 0)
            {
                retval = false;
                break;
            }
        }
        i++;
    }
    return retval;
}
bool boolean_function::is_T1() const
{
    return (func[func.size()-1] == 1);
}
bool boolean_function::is_T0() const
{
    return (func[0] == 0);
}
bool boolean_function::is_balanced() const //равновесная ли
{
    size_type len = size();
    if (len == 0)
    {
        return false;
    }

    if (weight() != len / 2)
    {
        return false;
    }
    return true;

}
size_t boolean_function::weight() const
{
    size_t retval = 0;
    size_type i = 0;
    while (i < size())
    {
        if (func[i])
        {
            retval++;
        }
        i++;
    }
    return retval;
}

bool boolean_function::is_functionally_complete_system() const
{
    bool T0 = is_T0();
    bool T1 = is_T1();
    bool symmetric = is_symmetric();
    bool linear = is_linear();
    bool monotone = is_monotone();
    bool retval = !(T0 || T1 || symmetric || linear || monotone);
    return retval;

}

// Возвращает АНФ функции
std::vector<boolean_function::value_type> boolean_function::anf() const
{
    const int len = func.size();
    std::vector<value_type> retval;

    int** M = new int*[len];
    int i = 0, j;
    while (i < len)
    {
        M[i] = new int[len];
        j = 0;
        while (j < len)
        {
            M[i][j] = 0;
            j++;
        }
        i++;

    }


    i = 0;
    while (i < len)
    {
        M[i][0] = func[i];
        i++;
    }
    i = 1;
    while (i < len)
    {
        j = 0;
        while (j < len - i)
        {
            M[j][i] = (M[j][i - 1] + M[j + 1][i - 1]) % 2;
            j++;
        }
        i++;
    }

    i = 0;
    while (i < len)
    {
        retval.push_back(M[0][i]);
        delete[] M[i];
        i++;
    }
    return retval;
}

// пусть boolean_function представляет из себя функцию "01110000"
// тогда get_polynom вернет строку "x0 + x1 + x0x1 + x0x2 + x1x2 + x0x1x2"
std::string get_polynom(const boolean_function& f)
{
    std::string retval("0");

    return retval;
}

boolean_function operator + (const boolean_function& a, const boolean_function& b)
{
    boolean_function retval(a);
    retval += b;
    return retval;
}

boolean_function operator * (const boolean_function& a, const boolean_function& b)
{
    boolean_function retval(a);
    retval *= b;
    return retval;
}

boolean_function operator | (const boolean_function& a, const boolean_function& b)
{
    boolean_function retval(a);
    retval |= b;
    return retval;
}

bool operator != (const boolean_function& a, const boolean_function& b)
{
    return !(a == b);
}


