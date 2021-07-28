#pragma once
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
#define delimiter    "\n=================================================================================\n"
class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
		friend class ConstIterator;
		friend class ConstReverseIterator;
	}*Head, * Tail;
	size_t size;
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp);
		~BaseIterator();
		// Operators
		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;
		const int& operator*()const;
	};
public:
	class ConstIterator :public BaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator ++();
		ConstIterator operator ++(int);
		ConstIterator& operator --();
		ConstIterator operator --(int);
	};
	class ConstReverseIterator : public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);

	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp);
		~Iterator();
		int& operator*();
	};
	class ReverseIterator :ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp);
		~ReverseIterator();
		int& operator*();
	};
	size_t get_size();
	ConstIterator begin();
	ConstIterator end();
	const ConstIterator cbegin()const;
	const ConstIterator cend()const;
	ConstReverseIterator rbegin();
	ConstReverseIterator rend();
	const ConstReverseIterator crbegin()const;
	const ConstReverseIterator crend()const;
	List();
	explicit List(size_t size, int value = int());
	List(const std::initializer_list<int>& il);
	List(const List& other);
	List(List&& other);
	~List();
	// Operators
	int& operator[](size_t index);
	// Edd elements
	void push_front(int Data);
	void push_back(int Data);
	void insert(size_t index, int Data);
	//Removing elements:
	void pop_front();
	void pop_back();
	void erase(size_t index);
	// Methods:
	void print();
	void reverse_print();
};
List operator+(const List& left, const List& right);