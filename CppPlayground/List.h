#pragma once

#include <assert.h>

/*
리스트 노드는 리스트의 기능을 구현하고 데이터를 저장하기 위한
용도로 사용이 된다. 리스트의 사용자는 이 노드를 모르더라도
쉽게 사용이 가능해야 한다.
노드는 이 안에서 리스트의 기능을 구현할 목적으로 사용을 할
것이므로 외부에서는 생성자체가 불가능하게 작업한다.
*/
template <typename T>
class CListNode
{
	template <typename T>
	friend class CList;

	template <typename T>
	friend class CListIterator;

	template <typename T>
	friend class CListReverseIterator;

private:
	CListNode()	:
		m_Next(nullptr),
		m_Prev(nullptr)
	{
	}

	~CListNode()
	{
	}

private:
	T		m_Data;
	CListNode<T>* m_Next;
	CListNode<T>* m_Prev;
};


template <typename T>
class CListIterator
{
	template <typename T>
	friend class CList;

public:
	CListIterator()	:
		m_Node(nullptr)
	{
	}

	~CListIterator()
	{
	}

private:
	CListNode<T>* m_Node;

public:
	// iterator가 같은지 다른지를 비교하는것은 가지고 있는 노드의 주소가
	// 서로 같은 주소인지 다른 주소인지를 판단하는 것이다.
	bool operator == (const CListIterator<T>& iter)	const
	{
		return m_Node == iter.m_Node;
	}

	bool operator != (const CListIterator<T>& iter)	const
	{
		return m_Node != iter.m_Node;
	}

	bool operator == (const CListNode<T>* Node)	const
	{
		return m_Node == Node;
	}

	bool operator != (const CListNode<T>* Node)	const
	{
		return m_Node != Node;
	}

	void operator ++ ()
	{
		m_Node = m_Node->m_Next;
	}

	void operator ++ (int)
	{
		m_Node = m_Node->m_Next;
	}

	void operator -- ()
	{
		m_Node = m_Node->m_Prev;
	}

	void operator -- (int)
	{
		m_Node = m_Node->m_Prev;
	}

	T& operator * ()
	{
		return m_Node->m_Data;
	}
};

template <typename T>
class CListReverseIterator
{
	template <typename T>
	friend class CList;

public:
	CListReverseIterator() :
		m_Node(nullptr)
	{
	}

	~CListReverseIterator()
	{
	}

private:
	CListNode<T>* m_Node;

public:
	// iterator가 같은지 다른지를 비교하는것은 가지고 있는 노드의 주소가
	// 서로 같은 주소인지 다른 주소인지를 판단하는 것이다.
	bool operator == (const CListReverseIterator<T>& iter)	const
	{
		return m_Node == iter.m_Node;
	}

	bool operator != (const CListReverseIterator<T>& iter)	const
	{
		return m_Node != iter.m_Node;
	}

	bool operator == (const CListNode<T>* Node)	const
	{
		return m_Node == Node;
	}

	bool operator != (const CListNode<T>* Node)	const
	{
		return m_Node != Node;
	}

	void operator ++ ()
	{
		m_Node = m_Node->m_Prev;
	}

	void operator ++ (int)
	{
		m_Node = m_Node->m_Prev;
	}

	void operator -- ()
	{
		m_Node = m_Node->m_Next;
	}

	void operator -- (int)
	{
		m_Node = m_Node->m_Next;
	}

	T& operator * ()
	{
		return m_Node->m_Data;
	}
};




template <typename T>
class CList
{
public:
	CList()	:
		m_Size(0)
	{
		m_Begin = new NODE;
		m_End = new NODE;

		m_Begin->m_Next = m_End;
		m_End->m_Prev = m_Begin;
	}

	~CList()
	{
		PNODE	Node = m_Begin;

		// End의 다음 노드는 nullptr이므로 End까지 모두 지워주기 위해서
		// nullptr이 아닐 경우에만 동작시킨다.
		while (Node != nullptr)
		{
			PNODE	Next = Node->m_Next;
			
			delete	Node;

			Node = Next;
		}
	}

private:
	typedef CListNode<T>	NODE;
	typedef CListNode<T>*	PNODE;

public:
	typedef CListIterator<T>	iterator;
	typedef CListReverseIterator<T>	reverse_iterator;

private:
	PNODE	m_Begin;
	PNODE	m_End;
	int		m_Size;

public:
	// 뒤에 추가를 하는 함수이다. 뒤에 추가이기 때문에
	// End노드와 End노드의 이전노드 사이에 추가를 해준다.
	void push_back(const T& Data)
	{
		// 데이터를 저장하기 위한 노드를 생성한다.
		PNODE	Node = new NODE;

		Node->m_Data = Data;

		// End와 End이전 사이에 새로 생성된 노드를 추가하므로
		// End의 이전 노드를 받아둔다.
		PNODE	Prev = m_End->m_Prev;

		// End이전노드의 다음은 End로 되어있는데 이를 새로
		// 생성한 노드로 변경한다.
		Prev->m_Next = Node;

		// 새로 생성한 노드의 이전노드로 End의 이전노드를
		// 지정해준다.
		Node->m_Prev = Prev;

		// 새로 생선 노드의 다음노드로 End를 지정한다.
		Node->m_Next = m_End;

		// End의 이전노드로 새로 생성한 노드를 지정한다.
		m_End->m_Prev = Node;

		++m_Size;
	}

	// 앞에 추가하는 기능을 만들어보세요.
	void push_front(const T& Data)
	{
		// 데이터를 저장하기 위한 노드를 생성한다.
		PNODE	Node = new NODE;

		Node->m_Data = Data;

		// Begin과 Begin다음노드 사이에 새로 생성된 노드를 추가하므로
		// Begin의 다음 노드를 받아둔다.
		PNODE	Next = m_Begin->m_Next;

		// Begin다음노드의 이전노드는 Begin노드로 되어있는데 이를 새로
		// 생성한 노드로 변경한다.
		Next->m_Prev = Node;

		// 새로 생성한 노드의 다음노드로 Begin의 다음노드를
		// 지정해준다.
		Node->m_Next = Next;

		// 새로 생선 노드의 이전노드로 Begin노드를 지정한다.
		Node->m_Prev = m_Begin;

		// Begin의 다음노드로 새로 생성한 노드를 지정한다.
		m_Begin->m_Next = Node;

		++m_Size;
	}

	// 가장 마지막에 배치되어 있는 노드를 제거한다.
	void pop_back()
	{
		if(empty())
		{
			assert(false);
		}

		// 삭제할 노드는 End의 이전노드이다.
		PNODE	DeleteNode = m_End->m_Prev;

		// 삭제할 노드의 이전노드를 얻어온다.
		PNODE	Prev = DeleteNode->m_Prev;

		// 삭제할 노드의 이전노드의 다음노드를 End노드로 지정한다.
		Prev->m_Next = m_End;

		// End노드의 이전 노드를 삭제할 노드의 이전노드로 지정한다.
		m_End->m_Prev = Prev;

		// 삭제할 노드를 제거한다.
		delete	DeleteNode;

		--m_Size;
	}

	// 가장 앞에 배치되어있는 노드를 제거한다.
	void pop_front()
	{
		if (empty())
		{
			assert(false);
		}

		// 삭제할 노드는 Begin의 다음노드이다.
		PNODE	DeleteNode = m_Begin->m_Next;

		// 삭제할 노드의 다음노드를 얻어온다.
		PNODE	Next = DeleteNode->m_Next;

		// 삭제할 노드의 다음노드의 이전노드를 Begin노드로 지정한다.
		Next->m_Prev = m_Begin;

		// Begin노드의 다음 노드를 삭제할 노드의 다음노드로 지정한다.
		m_Begin->m_Next = Next;

		// 삭제할 노드를 제거한다.
		delete	DeleteNode;

		--m_Size;
	}

	// 첫번째 노드의 데이터를 반환한다.
	T front()	const
	{
		if (empty())
		{
			assert(false);
		}

		return m_Begin->m_Next->m_Data;
	}

	// 가장 마지막에 배치되어있는 노드의 데이터를 반환한다.
	T back()	const
	{
		if (empty())
		{
			assert(false);
		}

		return m_End->m_Prev->m_Data;
	}

	// 비어있을 경우 true, 아니면 false
	bool empty()	const
	{
		return m_Size == 0;
	}

	int size()	const
	{
		return m_Size;
	}

	// Begin과 End빼고 모두 지운다.
	// Begin과 End를 서로 연결해준다.
	void clear()
	{
		PNODE	Node = m_Begin->m_Next;

		while (Node != m_End)
		{
			// 다음 노드를 먼저 얻어온 이유는 먼저 제거를 하게 되면
			// 다음 노드의 주소를 얻어올 수 있는 방법이 없기 때문이다.
			PNODE	Next = Node->m_Next;

			// 노드를 제거한다.
			delete	Node;

			// 미리 저장해 두었던 다음 노드의 주소를 준다.
			Node = Next;
		}

		m_Begin->m_Next = m_End;
		m_End->m_Prev = m_Begin;

		m_Size = 0;
	}

	// Begin의 다음 노드를 iterator의 노드로 주고 반환한다.
	// 즉, 처음 추가된 노드가 들어가거나 아무것도 없을 경우라면 End가 들어가서
	// iterator가 반환되게 된다.
	iterator begin()	const
	{
		iterator	iter;
		iter.m_Node = m_Begin->m_Next;
		return iter;
	}

	iterator end()	const
	{
		iterator	iter;
		iter.m_Node = m_End;
		return iter;
	}

	reverse_iterator rbegin()	const
	{
		reverse_iterator	iter;
		iter.m_Node = m_End->m_Prev;
		return iter;
	}

	reverse_iterator rend()	const
	{
		reverse_iterator	iter;
		iter.m_Node = m_Begin;
		return iter;
	}

	// 삭제 기능을 제작한다. 삭제를 하게 되면 삭제한 노드의 다음 노드를
	// iterator에 넣어서 반환해주도록 한다.
	iterator erase(const T& Data)
	{
		iterator	iter;
		iterator	iterEnd = end();

		for (iter = begin(); iter != iterEnd; ++iter)
		{
			if (*iter == Data)
				return erase(iter);
		}

		// 같은 데이터가 없을 경우 end를 반환한다.
		return end();
	}

	iterator erase(const iterator& iter)
	{
		if (empty())
			return end();

		// 지울 노드의 이전노드와 다음 노드를 얻어온다.
		PNODE	Prev = iter.m_Node->m_Prev;
		PNODE	Next = iter.m_Node->m_Next;

		// 이전노드와 다음노드를 서로 연결한다.
		Prev->m_Next = Next;
		Next->m_Prev = Prev;

		// 노드를 제거한다.
		delete	iter.m_Node;

		--m_Size;

		iterator	result;
		result.m_Node = Next;
		return result;
	}

	// Start와 End 사이를 제거한다. End는 Start보다 뒤에 있어야 한다.
	// 주말 숙제!!
	iterator erase(const iterator& Start, const iterator& End)
	{
		iterator	Start1 = Start;
		iterator	End1 = End;

		// 시작노드보다 도착노드가 앞에 있다면 예외처리를 한다.
		for (iterator iter = Start; iter != m_Begin; --iter)
		{
			if (iter == End)
			{
				Start1 = End;
				End1 = Start;
				break;
			}
		}


		PNODE	Prev = Start1.m_Node->m_Prev;
		PNODE	Next = End1.m_Node->m_Next;

		PNODE	Node = Start1.m_Node;

		while (Node != Next)
		{
			PNODE	Next1 = Node->m_Next;

			delete	Node;

			--m_Size;

			Node = Next1;
		}

		Prev->m_Next = Next;
		Next->m_Prev = Prev;


		iterator	iter;
		iter.m_Node = Next;

		return iter;
	}

	// 정렬
	void Sort(bool (*Func)(const T&, const T&))
	{
		iterator	iter = begin();
		iterator	iterEnd = end();
		--iterEnd;

		for (; iter != iterEnd; ++iter)
		{
			iterator	iter1 = iter;
			++iter1;

			iterator	iter1End = end();

			for (; iter1 != iter1End; ++iter1)
			{
				if (Func(*iter, *iter1))
				{
					T	Temp = *iter;
					*iter = *iter1;
					*iter1 = Temp;
				}
			}
		}

		/*for (int i = 0; i < 9; ++i)
		{
			for (int j = i + 1; j < 10; ++j)
			{
				if (Array[i] > Array[j])
				{
					int	Temp = Array[i];
					Array[i] = Array[j];
					Array[j] = Temp;
				}
			}
		}*/
	}
};

