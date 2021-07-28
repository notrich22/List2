#include"List.h"

#define tab "\t"
#define delimiter    "\n=================================================================================\n"


// Operators
int& List::Iterator::operator*()
{
	return Temp->Data;
}
List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::ConstIterator it = right.cbegin(); it != right.cend(); it++)
		cat.push_back(*it);
	return cat;
}
int& List::operator[](size_t index)
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
int& List::ReverseIterator::operator*()
{
	return Temp->Data;
}
List::ConstIterator& List::ConstIterator::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
List::ConstIterator List::ConstIterator::operator ++(int)
{
	ConstIterator old = *this;
	Temp = Temp->pNext;
	return old;
}
List::ConstIterator& List::ConstIterator::operator --()
{
	Temp = Temp->pPrev;
	return *this;
}
List::ConstIterator List::ConstIterator::operator --(int)
{
	ConstIterator old = *this;
	Temp = Temp->pPrev;
	return old;
}
bool List::BaseIterator::operator==(const BaseIterator& other)const
{
	return this->Temp == other.Temp;
}
bool List::BaseIterator::operator!=(const BaseIterator& other)const
{
	return this->Temp != other.Temp;
}
const int& List::BaseIterator::operator*()const
{
	return Temp->Data;
}
// Constructors And Destructors
List::Element::Element(int Data, List::Element* pNext, List::Element* pPrev) :
	Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstrucor: \t" << this << endl;
#endif // DEBUG

}
List::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestrucor: \t" << this << endl;
#endif // DEBUG

}

List::ReverseIterator::ReverseIterator(Element* Temp) :ConstReverseIterator(Temp)
{
	cout << "RItConstructor:\t" << tab << endl;
}
List::ReverseIterator::~ReverseIterator()
{
	cout << "RItDestructor:\t" << tab << endl;
}
List::Iterator::Iterator(Element* Temp) :ConstIterator(Temp)
{
	cout << "ItConstructor:\t" << tab << endl;
}
List::Iterator::~Iterator()
{
	cout << "ItDestructor:\t" << tab << endl;
}
List::ConstReverseIterator::ConstReverseIterator(List::Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

}
List::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

}
List::ConstIterator::ConstIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

}
List::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

}
List::BaseIterator::BaseIterator(Element* Temp) :Temp(Temp)
{
	cout << "BitConstrucor: \t" << this << endl;
}
List::BaseIterator::~BaseIterator()
{
	cout << "BitDestrucor: \t" << this << endl;
}
List::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
List::List(size_t size, int value) :List()
{
	while (size--)push_back(value);
	cout << "LConstructor:\t" << this << endl;
}
List::List(const std::initializer_list<int>& il) : List()
{
	cout << typeid(il.begin()).name() << endl;
	for (int const* it = il.begin(); it != il.end(); it++)
		push_back(*it);
}
List::List(const List& other) : List()
{
	for (ConstIterator it = other.cbegin(); it != other.cend(); it++)
		push_back(*it);
	cout << "LCopyConstructor\t" << this << endl;
}
List::List(List&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;
	cout << "LMoveConstructor\t" << this << endl;
}
List::~List()
{
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}
// Add elements
void List::push_front(int Data)
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
void List::push_back(int Data)
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
void List::insert(size_t index, int Data)
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
void List::pop_front()
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
void List::pop_back()
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
void List::erase(size_t index)
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
size_t List::get_size() { return size; }
List::ConstIterator List::begin() { return Head; }
List::ConstIterator List::end() { return nullptr; }
const List::ConstIterator List::cbegin()const { return Head; }
const List::ConstIterator List::cend()const { return nullptr; }
List::ConstReverseIterator List::rbegin() { return Tail; }
List::ConstReverseIterator List::rend() { return nullptr; }
const List::ConstReverseIterator List::crbegin()const { return Tail; }
const List::ConstReverseIterator List::crend()const { return nullptr; }
void List::print()
{
	cout << "Head: " << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}
void List::reverse_print()
{
	cout << "Tail: " << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}
