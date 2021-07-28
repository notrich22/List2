#include"List.h"


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