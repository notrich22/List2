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
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstrucor: \t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestrucor: \t" << this << endl;
#endif // DEBUG

		}
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
		BaseIterator(Element* Temp) :Temp(Temp)
		{
			cout << "BitConstrucor: \t" << this << endl;
		}
		~BaseIterator()
		{
			cout << "BitDestrucor: \t" << this << endl;
		}

		// Operators

		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}

	};
public:
	class ConstIterator :public BaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		ConstIterator& operator ++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator ++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator --()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator --(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

	};
	class ConstReverseIterator : public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp)
		{
			cout << "ItConstructor:\t" << tab << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << tab << endl;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator :ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp)
		{
			cout << "RItConstructor:\t" << tab << endl;
		}
		~ReverseIterator()
		{
			cout << "RItDestructor:\t" << tab << endl;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	size_t get_size() { return size; }
	ConstIterator begin() { return Head; }
	ConstIterator end() { return nullptr; }
	const ConstIterator cbegin()const { return Head; }
	const ConstIterator cend()const { return nullptr; }
	ConstReverseIterator rbegin() { return Tail; }
	ConstReverseIterator rend() { return nullptr; }
	const ConstReverseIterator crbegin()const { return Tail; }
	const ConstReverseIterator crend()const { return nullptr; }


	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit List(size_t size, int value = int()) :List()
	{
		while (size--)push_back(value);
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	List(const List& other) : List()
	{
		for (ConstIterator it = other.cbegin(); it != other.cend(); it++)
			push_back(*it);
		cout << "LCopyConstructor\t" << this << endl;
	}
	List(List&& other)
	{
		this->size = other.size;
		this->Head = other.Head;
		this->Tail = other.Tail;
		other.Head = other.Tail = nullptr;
		cout << "LMoveConstructor\t" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	// Operators
	int& operator[](size_t index)
	{
		if (index >= size)throw std::exception("Error: out of range");
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		return Temp->Data;
	}

	// Edd elements

	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		size++;

	}
	void insert(size_t index, int Data)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < index; i++)Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pPrev = Temp->pPrev;
		New->pNext = Temp;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}

	//Removing elements:

	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)
		{
			delete Tail;
			Tail = Head = nullptr;
			size--;
			return;
		}
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(size_t index)
	{

		if (index == 0)return pop_front();
		if (index == size)return;
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < index; i++)Temp = Temp->pPrev;
		}
		Element* Eraser;
		Eraser = Temp;
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Eraser;
		size--;
	}

	// Methods:

	void print()
	{
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()
	{
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
};
List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::ConstIterator it = right.cbegin(); it != right.cend(); it++)
		cat.push_back(*it);
	return cat;
}



//#define BASE_CHECK
//#define SIZE_COSTRUCTOR_AND_SUBSCRIPT
//#define HARDCORE
//#define ITERATORS_CHECK
//#define COPY_CONSTRUCTOR_CHECK
//#define COPY_ASSIGNMENT_CHECK
#define OPERATOR_PLUS
void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef BASE_CHECK
	int n; cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}

	list.print();
	list.reverse_print();
	list.push_front(777);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	cout << delimiter;
	size_t index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	cout << delimiter;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef SIZE_COSTRUCTOR_AND_SUBSCRIPT
	int n; cout << "Введите размер списка: "; cin >> n;
	List list(n);
	for (int i = 0; i < list.get_size(); i++)
		list[i] = rand() % 100;
	for (int i = 0; i < list.get_size(); i++)
		cout << list[i] << tab;
	cout << endl;
	for (int i = list.get_size() - 1; i >= 0; i--)
		cout << list[i] << tab;
	cout << endl;
#endif // SIZE_COSTRUCTOR_AND_SUBSCRIPT

#ifdef HARDCORE
	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)
		cout << i << tab;
	cout << endl;
	for (List::ReverseIterator rit = list.rbegin(); rit != list.rend(); rit++)
		cout << *rit << tab;
	cout << endl;


#endif // HARDCORE

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();
#endif // ITERATORS_CHECK

#ifdef COPY_CONSTRUCTOR_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	list.reverse_print();
	cout << delimiter;
	List list2 = list;
	list2.print();
	cout << delimiter;
	list2.reverse_print();
#endif // COPY_CONSTRUCTOR_CHECK

#ifdef COPY_ASSIGNMENT_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list = list;
	list.print();
	list.reverse_print();
	List list2;
	list2 = list;
	list2.print();
	list2.reverse_print();
#endif // COPY_ASSIGNMENT_CHECK

#ifdef OPERATOR_PLUS
	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	list3.print();
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;

#endif // OPERATOR_PLUS


}