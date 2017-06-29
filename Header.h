#pragma once

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include <cmath>

class boolean_function
{
public:
	using value_type = bool;
	using size_type = size_t;
	using reference = std::vector<value_type>::reference;
	using const_reference = std::vector<value_type>::const_reference;

	using iterator = std::vector<value_type>::iterator;
	using const_iterator = std::vector<value_type>::const_iterator;

private:
	std::vector<value_type> func;

public:

	// ���������� ������� ������� ����� xn � ������������ dimension
	// ������ 1
	// n = 0
	// dimension = 3
	// �������� ������� "01010101"
	// ������ 2
	// n = 1
	// dimension = 4
	// �������� ������� "0011001100110011"
	static boolean_function var(size_t n, size_t dimension);

	// ������������� ���� "�� dimension ����������"
	static boolean_function zero(size_t dimension);
	// ������������� ������� "�� dimension ����������"
	static boolean_function one(size_t dimension);

	static boolean_function from_anf(std::vector<value_type> v);

	boolean_function() = default;

	// ������ ������ �������������� ���� �� n ����������
	boolean_function(size_t n);

	// ������ ������ �� n ����������. �������� ����� value
	// ������
	// ����� value = 14, �.�. 0...00001110 � �������� �������
	// � n = 3
	// ����� ��� boolean_function ����� ����� x + y + xy + zx + zy + zyx
	boolean_function(unsigned long long value, size_type n);


	// ����� table = "01110000"
	// ����� ��� boolean_function ����� ����� x + y + xy + zx + zy + zyx
	boolean_function(const std::string& table);

	// ����� table = {true, false, false, true};
	// ����� ��� boolean_function ����� ����� x + y + 1
	boolean_function(const std::vector<value_type>& table);
	boolean_function(const std::initializer_list<bool> vars);

	boolean_function(const boolean_function& table);

	boolean_function& operator=(const boolean_function& rhs);
	// �������� �� ������ 2
	// ���� ������ ���������� ���������� - ����������
	boolean_function& operator += (const boolean_function& rhs);

	// ����������
	// ���� ������ ���������� ���������� - ����������
	boolean_function& operator *= (const boolean_function& rhs);

	// ����������
	// ���� ������ ���������� ���������� - ����������
	boolean_function& operator |= (const boolean_function& rhs);

	// ��������� ���������
	boolean_function operator ~();

	// true ���� ������� �����
	//  ����� false
	bool operator == (const boolean_function& v) const;

	// true ���� ���� ������� �������� � ������ ��� ����� rhs
	// false ���� �������� � ������ rhs
	// logic_error ���� ������ �� ��������
	bool operator >= (const boolean_function& rhs) const;
	reference operator[](size_type ind);
	const_reference operator[](size_type ind) const;

	reference at(size_type ind);
	const_reference at(size_type ind) const;

	iterator begin();
	iterator end();

	const_iterator cbegin() const;
	const_iterator cend() const;

	// ����� ������� �������
	size_type size() const throw();

	// ���������� ����������
	size_type dimension() const throw();

	// ���������� �������� �������
	// ����� boolean_function ������ ������� f(x, y, z)
	// ����� ������� ������ f(vars[0], vars[1], vars[2])
	bool operator()(const std::vector<bool>& vars) const;
	bool operator()(const std::initializer_list<bool> vars) const;

	// T(x1, x2, ..., xN) - ������� �������
	// operator ������ ����� �������, ������� ����� ���������� G = T(fs[0], fs[1], ..., fs[N-1])
	boolean_function operator()(const std::vector<boolean_function>& fs) const;
	boolean_function operator()(const std::initializer_list<boolean_function> vars) const;

	bool is_monotone() const;
	bool is_symmetric() const;
	bool is_linear() const;
	bool is_T1() const;
	bool is_T0() const;
	bool is_balanced() const; //����������� ��
	size_t weight() const;

	bool is_functionally_complete_system() const;
	// ���������� ��� �������
	std::vector<value_type> anf() const;
};

// ����� boolean_function ������������ �� ���� ������� "01110000"
// ����� get_polynom ������ ������ "x0 + x1 + x0x1 + x0x2 + x1x2 + x0x1x2"
std::string get_polynom(const boolean_function&);

boolean_function operator + (const boolean_function& a, const boolean_function& b);

boolean_function operator * (const boolean_function& a, const boolean_function& b);

boolean_function operator | (const boolean_function& a, const boolean_function& b);

bool operator != (const boolean_function& a, const boolean_function& b);