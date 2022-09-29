#include <iostream>
#include <stdexcept>

template <typename T>
class PriorityStack
{
public:
	PriorityStack();

	void Push(int priority, T value);	// добавить элемент в стэк
	T Pop();							// взять элемент из стэка с максимальным приоритетом
	bool IsEmpty();						// проверяет, пустой ли стэк
	void Clear();						// очищает стэк

	void printStack();					// вывод содержимого стека (для дебага)

private:
	template<typename T>
	struct PSNode
	{
		unsigned int priority;
		T data;
		PSNode* pNext;
		PSNode* pPrev;

		PSNode(T data, unsigned int priority, PSNode* pNext = nullptr, PSNode* pPrev = nullptr) :
			data(data), priority(priority), pNext(pNext), pPrev(pPrev) {};
	};

	PSNode<T>* Top;

public:
	template<typename T>
	class PSIterator
	{
	public:
		PSNode<T>* cursor;

		PSIterator(PSNode<T>* first) : cursor(first) {}

		PSNode<T>& operator ++ ()
		{
			cursor = cursor->pNext;
			return *cursor;
		}

		PSNode<T>& operator -- ()
		{
			cursor = cursor->pPrev;
			return *cursor;
		}

		bool operator != (const PSIterator& it) { return cursor != it.cursor; };
		bool operator == (const PSIterator& it) { return cursor == it.cursor; };

		PSNode<T>& operator * () { return *cursor; }
	};
};

template<typename T>
PriorityStack<T>::PriorityStack() :Top(nullptr)
{}

template <typename T>
void PriorityStack<T>::Push(int priority, T value)
{
	if (IsEmpty())
	{
		Top = new PSNode<T>(value, priority);
		return;
	}

	PSIterator<T> it(Top);

	if (Top->priority <= priority)
	{
		PSNode<T>* newNode = new PSNode<T>(value, priority, it.cursor, nullptr);
		it.cursor->pPrev = newNode;
		Top = newNode;
		return;
	}

	while (true)
	{
		PSNode<T>* temp = it.cursor;
		if (temp->priority <= priority)
		{
			PSNode<T>* newNode = new PSNode<T>(value, priority, temp, temp->pPrev);
			if (temp->pPrev != nullptr) temp->pPrev->pNext = newNode;
			temp->pPrev = newNode;
			return;
		}
		else if (temp->pNext == nullptr)
		{
			PSNode<T>* newNode = new PSNode<T>(value, priority, nullptr, temp);
			temp->pNext = newNode;
			return;
		}
		++it;
	}
}

template <typename T>
T PriorityStack<T>::Pop()
{
	if (IsEmpty())
	{
		throw std::out_of_range("Stack is empty!");
	}
	T returnValue = Top->data;
	PSNode<T>* temp = Top;
	Top = temp->pNext;
	delete temp;
	return returnValue;
}

template <typename T>
bool PriorityStack<T>::IsEmpty()
{
	if (Top == nullptr) { return true; }
	return false;
}

template <typename T>
void PriorityStack<T>::Clear()
{
	if (IsEmpty()) return;
	PSNode<T>* temp = nullptr;
	while (Top)
	{
		temp = Top->pNext;
		delete Top;
		temp == nullptr ? Top = nullptr : Top = temp;
	}
	delete temp;
}

template <typename T>
void PriorityStack<T>::printStack()
{
	PSIterator<T> it(Top);

	while (it.cursor != nullptr)
	{
		std::cout << "Data: " << it.cursor->data << "\t| Priority: " << it.cursor->priority << std::endl;
		++it;
	}
	std::cout << std::endl;
}