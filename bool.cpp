#include "Header.h"

// ���������� ������� ������� ����� xn � ������������ dimension
// ������ 1
// n = 0
// dimension = 3
// �������� ������� "01010101"
// ������ 2
// n = 1
// dimension = 4
// �������� ������� "0011001100110011"
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

// ������������� ���� "�� dimension ����������"
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

// ������������� ������� "�� dimension ����������"
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
	while (i < len)
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
		while (j < (len - i))
		{
			M[j][i] = (((M[j - 1][i]) + (M[j - 1][i + 1])) % 2);
			j++;
		}
		i--;
	}

	std::vector<value_type> retval;
	i = 0;
	while (i < len)
	{
		retval.push_back(M[i][0]);
		delete[] M[i];
		i++;
	}

	boolean_function f(retval);

	delete[] M;

	return f;
}


// ������ ������ �������������� ���� �� n ����������
boolean_function::boolean_function(size_t n)
{
	size_type len = pow(2, n);
	while (func.size()<len)
	{
		func.push_back(0);
	}
}

// ������ ������ �� n ����������. �������� ����� value
// ������
// ����� value = 14, �.�. 0...00001110 � �������� �������
// � n = 3
// ����� ��� boolean_function ����� ����� x + y + xy + zx + zy + zyx
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

// ����� table = "01110000"
// ����� ��� boolean_function ����� ����� x + y + xy + zx + zy + zyx
boolean_function::boolean_function(const std::string& table)
{
	int k = 0;
	int ch = table.size();
	while (ch > 0)
	{
		k += ch % 2;
		ch /= 2;
	}
	if (k != 1)
		throw std::exception("length error\n");
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

// ����� table = {true, false, false, true};
// ����� ��� boolean_function ����� ����� x + y + 1
boolean_function::boolean_function(const std::vector<value_type>& table)
{
	func = table;
}



boolean_function::boolean_function(const std::initializer_list<bool> vars)
{

	int k = 0;
	int ch = vars.size();
	while (ch > 0)
	{
		k += ch % 2;
		ch /= 2;
	}
	if (k != 1)
		throw std::exception("length error\n");
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
// �������� �� ������ 2
// ���� ������ ���������� ���������� - ����������
boolean_function& boolean_function::operator += (const boolean_function& rhs)
{
	if (func.size() != rhs.func.size())
	{
		throw std::length_error("Length error\n");
	}
	size_type i = 0;
	while (i < size())
	{
		func[i] = (func[i] + rhs.func[i]) % 2;
		i++;
	}
	return *this;
}
// ����������
// ���� ������ ���������� ���������� - ����������
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

// ����������
// ���� ������ ���������� ���������� - ����������
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

// ��������� ���������
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

// true ���� ������� �����
//  ����� false
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
	while (i < func.size())
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

// true ���� ���� ������� �������� � ������ ��� ����� rhs
// false ���� �������� � ������ rhs
// logic_error ���� ������ �� ��������
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
	if ((size() == 0) || (ind < 0) || (ind >= size()))
	{
		throw std::out_of_range("out of range\n");
	}
	return func[ind];
}
boolean_function::const_reference boolean_function::operator[](size_type ind) const
{
	if ((size() == 0) || (ind < 0) || (ind >= size()))
	{
		throw std::out_of_range("out of range\n");
	}
	return func[ind];
}

boolean_function::reference boolean_function::at(size_type ind)
{
	if ((size() == 0) || (ind < 0) || (ind >= size()))
	{
		throw std::out_of_range("out of range\n");
	}
	return func[ind];
}
boolean_function::const_reference boolean_function::at(size_type ind) const
{
	if ((size() == 0) || (ind < 0) || (ind >= size()))
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

// ����� ������� �������
boolean_function::size_type boolean_function::size() const throw()
{
	return func.size();
}

// ���������� ����������
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

// ���������� �������� �������
// ����� boolean_function ������ ������� f(x, y, z)
// ����� ������� ������ f(vars[0], vars[1], vars[2])
bool boolean_function::operator()(const std::vector<bool>& vars) const
{
	size_type i = 0;
	size_type retval = 0;

	while (i < vars.size())
	{
		if (i >= (sizeof(size_type) * 8))
		{
			throw std::out_of_range("out of range\n");
		}
		retval |= vars[i] << i;
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
		if (i >= (sizeof(size_type) * 8))
		{
			throw std::out_of_range("out of range\n");
		}
		retval |= v << i;
		i++;
	}


	return func[retval];
}

///�� �����������!!!!
// T(x1, x2, ..., xN) - ������� �������
// operator ������ ����� �������, ������� ����� ���������� G = T(fs[0], fs[1], ..., fs[N-1])
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
	std::vector<value_type> res;
	for (int i = func.size() - 1; i > -1; i--)
	{
		if (func[i] == 1)
			res.push_back(0);
		else
			res.push_back(1);
	}

	if (res != func)
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
	while (i < f.size())
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
	return (func[func.size() - 1] == 1);
}
bool boolean_function::is_T0() const
{
	return (func[0] == 0);
}
bool boolean_function::is_balanced() const //����������� ��
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

// ���������� ��� �������
std::vector<boolean_function::value_type> boolean_function::anf() const
{
	const int len = func.size();
	std::vector<value_type> f;

	int** mas = new int*[len];
	for (int i = 0; i < len; i++)
	{
		mas[i] = new int[len];
		for (int j = 0; j < len; j++)
			mas[i][j] = 0;
	}

	for (int i = 0; i < len; i++)
		mas[i][0] = func[i];

	for (int i = 1; i < len; i++)
	{
		for (int j = 0; j < len - i; j++)
		{
			mas[j][i] = (mas[j][i - 1] + mas[j + 1][i - 1]) % 2;
		}
	}

	for (int i = 0; i < len; i++)
		f.push_back(mas[0][i]);

	for (int i = 0; i < len; i++)
		delete[] mas[i];

	delete[] mas;

	return f;
}

// ����� boolean_function ������������ �� ���� ������� "01110000"
// ����� get_polynom ������ ������ "x0 + x1 + x0x1 + x0x2 + x1x2 + x0x1x2"
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