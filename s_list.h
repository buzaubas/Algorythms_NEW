#ifndef _s_list_h
#define _s_list_h

#include <iostream>

using namespace std;

/**
Структура как элемент списка и хранения данных.
*/
template<class T>
struct node
{
	T data;			// Данные
	node<T>* next;	// Адрес следующего элемента списка
	node() : next(nullptr) {}
};

/**
Реализация класса итератора для организации доступа
к элементам контейнера.
*/
template<class T>
class s_iterator
{
	node<T>* ptr;
public:
	s_iterator() : ptr(nullptr) {}
	s_iterator(node<T>* ptr) : ptr(ptr) {}
	s_iterator& operator++() { ptr = ptr->next; return *this; }
	T& operator*() const { return ptr->data; }
	node<T> operator->() { return ptr; }
	bool operator!=(const s_iterator& obj) const { return ptr != obj.ptr; }
	~s_iterator() { ptr = nullptr; }
};

/**
Описание класса списка.
*/
template<class T>
class s_list {
	node<T>* first;									// адрес первого элемента списка
	node<T>* last;									// адрес последнего элемента списка
public:
	friend class s_iterator<T>;						// включение класса итератора
	s_list();										// конструктор по умолчанию
	s_list(const s_list<T>& obj);					// конструктор копирования
	s_list(s_list<T>&& obj);						// конструктор перемещения
	s_list<T>& operator=(const s_list<T>& obj);		// оператор равно копированием
	s_list<T>& operator=(s_list<T>&& obj);			// оператор равно перемещением
	T& operator[](size_t pos) const;				// оператор индексирования

	void add_to_head(const T& data);				// добавление элемента в начало 
	void add_to_tail(const T& data);				// добавление элемента в конец 
	T front() const;								// возвращает первое значение
	T back() const;									// возвращает последнее значение
	T delete_from_head();							// удаление первого элемента
	T delete_from_tail();							// удаление последнего элемента
	void delete_all();								// удаление всех элементов          
	void show() const;								// отображение всех элементов
	size_t size() const;							// количество элементов

	s_iterator<T> begin() const;					// возвращает итератор на первый элемент
	s_iterator<T> end() const;						// возвращает итератор на элемент, следующий за последним

	void insert_at(size_t pos, const T& data);		// вставка в указанную позицию
	void delete_at(size_t pos);						// удаление по указанной позиции
	size_t find(const T& data) const;				// поиск элемента (NULL в случае неудачи)
	size_t find_and_replace(const T& data, const T& repl_data);	// поиск и замена всех элементов (возвращаем кол-во замен)
	void reverse();									// переворот списка

	void sort();									// сортирует элементы (вставками)
	void splice(s_list<T>& obj);					// перемещает элементы из другого list 

	~s_list();										// деструктор ничем не отличается от delete all
private:
	void add_to_head(node<T>* ptr);					// добавляет ноду в голову списка
	void add_to_tail(node<T>* ptr);					// добавляет ноду в конец списка
};

template<class T>
inline void s_list<T>::insert_at(size_t pos, const T& data)
{
	size_t index{ 0 };
	node<T>* temp{ first };
	while (temp)
	{
		if (index == pos)
		{
			node<T>* newnode = new node<T>();
			newnode->data = data;
			newnode->next = temp->next;
			temp->next = newnode;
			break;
		}
		index++;
		temp = temp->next;
	}
}

template<class T>
inline void s_list<T>::delete_at(size_t pos)
{
	size_t index{ 0 };
	node<T>* temp{ first };
	while (temp)
	{
		if (index == (pos - 1))
		{
			node<T>* to_delete{ temp };
			temp = ((*temp).next).next;
			break;
		}
		index++;
		temp = temp->next;
	}
	delete[] temp;
}

template<class T>
inline size_t s_list<T>::find(const T& data) const
{
	size_t index{ 0 };
	node<T>* temp{ first };
	while (temp)
	{
		if (*temp == data)
		{
			return index + 1;
		}
		index++;
		temp = temp->next;
	}
	return 0;
}

template<class T>
inline size_t s_list<T>::find_and_replace(const T& data, const T& repl_data)
{
	size_t num_rep{ 0 };
	size_t index{ 0 };
	node<T>* temp{ first };
	while (temp)
	{
		if (*temp == data)
		{
			*temp = repl_data;
			num_rep++;
		}
		index++;
		temp = temp->next;
	}
	return num_rep;
}

template<class T>
inline void s_list<T>::reverse()
{
	node<T>* temp{ first };
	size_t size_list = (*this).size();
}

template<class T>
inline s_list<T>::s_list() : first(nullptr), last(nullptr) {}

template<class T>
inline s_list<T>::s_list(const s_list<T>& obj)
{
	//????????????????
}

template<class T>
inline s_list<T>& s_list<T>::operator=(const s_list<T>& obj)
{
	node<T>* newnode = new node<T>();
	newnode->data = (*obj).*first;

	this->first = newnode;
	this->last = newnode;

	node<T>* temp{ first.next };
	for (auto i = 1; i < (*this).size(); i++)
	{
		(*this).insert_at(i, *temp);
		temp = temp->next;
	}
}

template<class T>
inline size_t s_list<T>::size() const
{
	size_t index{ 0 };
	node<T>* temp{ first };
	while (temp)
	{
		index++;
		temp = temp->next;
	}
	return index + 1;
}

template<class T>
inline s_iterator<T> s_list<T>::begin() const
{
	return first;
}

template<class T>
inline s_iterator<T> s_list<T>::end() const
{
	return last;
}

template<class T>
inline T& s_list<T>::operator[](size_t pos) const
{
	size_t index{ 0 };
	node<T>* temp{ first };
	while (temp)
	{
		if (index == pos)
		{
			return *temp;
		}
		index++;
		temp = temp->next;
	}
	return 999999999999999999;
}

template<class T>
inline void s_list<T>::add_to_head(const T& data)
{
	node<T>* newnode = new node<T>();
	newnode->data = data;
	newnode->next = first;
	first = newnode;
}

template<class T>
inline void s_list<T>::add_to_tail(const T& data)
{
	node<T>* newnode = new node<T>();
	newnode->data = data;
	last->next = newnode;
	last = newnode;
	newnode->next = nullptr;
}

template<class T>
inline T s_list<T>::front() const
{
	return *first;
}

template<class T>
inline T s_list<T>::back() const
{
	return *last;
}

template<class T>
inline T s_list<T>::delete_from_head()
{
	node<T>* temp{ first };
	first = first->next;
	delete[] *temp;
}

template<class T>
inline T s_list<T>::delete_from_tail()
{

	node<T>* temp{ last };
	for(auto i = first; first <= (*this).size() - 1; last = i){}
	delete[] * temp;
}

template<class T>
inline void s_list<T>::delete_all()
{
	delete[] * this;
}

template<class T>
inline void s_list<T>::show() const
{
	size_t index{ 0 };
	node<T>* temp{ first };
	while (temp)
	{
		std::cout << *temp->(node.data)<< " ";
		index++;
		temp = temp->next;
	}
}


#endif
