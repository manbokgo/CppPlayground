#pragma once

#include <assert.h>

/*
����Ʈ ���� ����Ʈ�� ����� �����ϰ� �����͸� �����ϱ� ����
�뵵�� ����� �ȴ�. ����Ʈ�� ����ڴ� �� ��带 �𸣴���
���� ����� �����ؾ� �Ѵ�.
���� �� �ȿ��� ����Ʈ�� ����� ������ �������� ����� ��
���̹Ƿ� �ܺο����� ������ü�� �Ұ����ϰ� �۾��Ѵ�.
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
	// iterator�� ������ �ٸ����� ���ϴ°��� ������ �ִ� ����� �ּҰ�
	// ���� ���� �ּ����� �ٸ� �ּ������� �Ǵ��ϴ� ���̴�.
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
	// iterator�� ������ �ٸ����� ���ϴ°��� ������ �ִ� ����� �ּҰ�
	// ���� ���� �ּ����� �ٸ� �ּ������� �Ǵ��ϴ� ���̴�.
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

		// End�� ���� ���� nullptr�̹Ƿ� End���� ��� �����ֱ� ���ؼ�
		// nullptr�� �ƴ� ��쿡�� ���۽�Ų��.
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
	// �ڿ� �߰��� �ϴ� �Լ��̴�. �ڿ� �߰��̱� ������
	// End���� End����� ������� ���̿� �߰��� ���ش�.
	void push_back(const T& Data)
	{
		// �����͸� �����ϱ� ���� ��带 �����Ѵ�.
		PNODE	Node = new NODE;

		Node->m_Data = Data;

		// End�� End���� ���̿� ���� ������ ��带 �߰��ϹǷ�
		// End�� ���� ��带 �޾Ƶд�.
		PNODE	Prev = m_End->m_Prev;

		// End��������� ������ End�� �Ǿ��ִµ� �̸� ����
		// ������ ���� �����Ѵ�.
		Prev->m_Next = Node;

		// ���� ������ ����� �������� End�� ������带
		// �������ش�.
		Node->m_Prev = Prev;

		// ���� ���� ����� �������� End�� �����Ѵ�.
		Node->m_Next = m_End;

		// End�� �������� ���� ������ ��带 �����Ѵ�.
		m_End->m_Prev = Node;

		++m_Size;
	}

	// �տ� �߰��ϴ� ����� ��������.
	void push_front(const T& Data)
	{
		// �����͸� �����ϱ� ���� ��带 �����Ѵ�.
		PNODE	Node = new NODE;

		Node->m_Data = Data;

		// Begin�� Begin������� ���̿� ���� ������ ��带 �߰��ϹǷ�
		// Begin�� ���� ��带 �޾Ƶд�.
		PNODE	Next = m_Begin->m_Next;

		// Begin��������� �������� Begin���� �Ǿ��ִµ� �̸� ����
		// ������ ���� �����Ѵ�.
		Next->m_Prev = Node;

		// ���� ������ ����� �������� Begin�� ������带
		// �������ش�.
		Node->m_Next = Next;

		// ���� ���� ����� �������� Begin��带 �����Ѵ�.
		Node->m_Prev = m_Begin;

		// Begin�� �������� ���� ������ ��带 �����Ѵ�.
		m_Begin->m_Next = Node;

		++m_Size;
	}

	// ���� �������� ��ġ�Ǿ� �ִ� ��带 �����Ѵ�.
	void pop_back()
	{
		if(empty())
		{
			assert(false);
		}

		// ������ ���� End�� ��������̴�.
		PNODE	DeleteNode = m_End->m_Prev;

		// ������ ����� ������带 ���´�.
		PNODE	Prev = DeleteNode->m_Prev;

		// ������ ����� ��������� ������带 End���� �����Ѵ�.
		Prev->m_Next = m_End;

		// End����� ���� ��带 ������ ����� �������� �����Ѵ�.
		m_End->m_Prev = Prev;

		// ������ ��带 �����Ѵ�.
		delete	DeleteNode;

		--m_Size;
	}

	// ���� �տ� ��ġ�Ǿ��ִ� ��带 �����Ѵ�.
	void pop_front()
	{
		if (empty())
		{
			assert(false);
		}

		// ������ ���� Begin�� ��������̴�.
		PNODE	DeleteNode = m_Begin->m_Next;

		// ������ ����� ������带 ���´�.
		PNODE	Next = DeleteNode->m_Next;

		// ������ ����� ��������� ������带 Begin���� �����Ѵ�.
		Next->m_Prev = m_Begin;

		// Begin����� ���� ��带 ������ ����� �������� �����Ѵ�.
		m_Begin->m_Next = Next;

		// ������ ��带 �����Ѵ�.
		delete	DeleteNode;

		--m_Size;
	}

	// ù��° ����� �����͸� ��ȯ�Ѵ�.
	T front()	const
	{
		if (empty())
		{
			assert(false);
		}

		return m_Begin->m_Next->m_Data;
	}

	// ���� �������� ��ġ�Ǿ��ִ� ����� �����͸� ��ȯ�Ѵ�.
	T back()	const
	{
		if (empty())
		{
			assert(false);
		}

		return m_End->m_Prev->m_Data;
	}

	// ������� ��� true, �ƴϸ� false
	bool empty()	const
	{
		return m_Size == 0;
	}

	int size()	const
	{
		return m_Size;
	}

	// Begin�� End���� ��� �����.
	// Begin�� End�� ���� �������ش�.
	void clear()
	{
		PNODE	Node = m_Begin->m_Next;

		while (Node != m_End)
		{
			// ���� ��带 ���� ���� ������ ���� ���Ÿ� �ϰ� �Ǹ�
			// ���� ����� �ּҸ� ���� �� �ִ� ����� ���� �����̴�.
			PNODE	Next = Node->m_Next;

			// ��带 �����Ѵ�.
			delete	Node;

			// �̸� ������ �ξ��� ���� ����� �ּҸ� �ش�.
			Node = Next;
		}

		m_Begin->m_Next = m_End;
		m_End->m_Prev = m_Begin;

		m_Size = 0;
	}

	// Begin�� ���� ��带 iterator�� ���� �ְ� ��ȯ�Ѵ�.
	// ��, ó�� �߰��� ��尡 ���ų� �ƹ��͵� ���� ����� End�� ����
	// iterator�� ��ȯ�ǰ� �ȴ�.
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

	// ���� ����� �����Ѵ�. ������ �ϰ� �Ǹ� ������ ����� ���� ��带
	// iterator�� �־ ��ȯ���ֵ��� �Ѵ�.
	iterator erase(const T& Data)
	{
		iterator	iter;
		iterator	iterEnd = end();

		for (iter = begin(); iter != iterEnd; ++iter)
		{
			if (*iter == Data)
				return erase(iter);
		}

		// ���� �����Ͱ� ���� ��� end�� ��ȯ�Ѵ�.
		return end();
	}

	iterator erase(const iterator& iter)
	{
		if (empty())
			return end();

		// ���� ����� �������� ���� ��带 ���´�.
		PNODE	Prev = iter.m_Node->m_Prev;
		PNODE	Next = iter.m_Node->m_Next;

		// �������� ������带 ���� �����Ѵ�.
		Prev->m_Next = Next;
		Next->m_Prev = Prev;

		// ��带 �����Ѵ�.
		delete	iter.m_Node;

		--m_Size;

		iterator	result;
		result.m_Node = Next;
		return result;
	}

	// Start�� End ���̸� �����Ѵ�. End�� Start���� �ڿ� �־�� �Ѵ�.
	// �ָ� ����!!
	iterator erase(const iterator& Start, const iterator& End)
	{
		iterator	Start1 = Start;
		iterator	End1 = End;

		// ���۳�庸�� ������尡 �տ� �ִٸ� ����ó���� �Ѵ�.
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

	// ����
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

