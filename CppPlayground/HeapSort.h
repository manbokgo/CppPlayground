#pragma once

#include <assert.h>

template <typename T>
class CHeapSort
{
public:
	CHeapSort()
	{
		m_Size = 0;
		m_Capacity = 4;

		m_Data = new T[m_Capacity];
	}

	~CHeapSort()
	{
		delete[]	m_Data;
	}

private:
	T* m_Data;
	int	m_Size;
	int	m_Capacity;
	bool (*m_Func)(const T&, const T&);

public:
	void SetSortFunction(bool (*Func)(const T&, const T&))
	{
		m_Func = Func;
	}

	void push(const T& Data)
	{
		if (m_Size == m_Capacity)
		{
			m_Capacity *= 2;

			T* Array = new T[m_Capacity];

			for (int i = 0; i < m_Size; ++i)
			{
				Array[i] = m_Data[i];
			}

			delete[] m_Data;

			m_Data = Array;
		}

		m_Data[m_Size] = Data;

		// 새로운 데이터가 추가된 인덱스를 인자로 넘겨서 데이터
		// 순서 변경작업을 진행한다.
		// 새로 추가하는 데이터의 배열 인덱스 넘겨주는것.
		Insert(m_Size);

		++m_Size;
	}

	void pop()
	{
		if (empty())
		{
			assert(false);
		}

		else if (m_Size == 1)
		{
			m_Size = 0;
			return;
		}

		// 1개 감소시킨다.
		--m_Size;

		// 가장 마지막에 추가되어 있는 값을 루트로 올려준다.
		m_Data[0] = m_Data[m_Size];

		Delete(0);
	}

	const T& top()	const
	{
		if (empty())
		{
			assert(false);
		}

		return m_Data[0];
	}

	void clear()
	{
		m_Size = 0;
	}

	int size()	const
	{
		return m_Size;
	}

	bool empty()	const
	{
		return m_Size == 0;
	}

private:
	void Insert(int Index)
	{
		// Index가 0이면 루트노드라는 의미이기 때문에 더이상
		// 작업을 안하고 반환해준다.
		if (Index == 0)
			return;

		// 현재 인덱스의 부모 인덱스를 구해준다.
		int	ParentIndex = (Index - 1) / 2;

		if (m_Func(m_Data[ParentIndex], m_Data[Index]))
		{
			T	Temp = m_Data[ParentIndex];
			m_Data[ParentIndex] = m_Data[Index];
			m_Data[Index] = Temp;

			// 값이 바뀌었다면 바뀐 위치에서의 부모노드와도 비교를
			// 계속해서 이어나가야 한다.
			Insert(ParentIndex);
		}
	}

	void Delete(int Index)
	{
		// 왼쪽 자식노드의 인덱스를 구해준다.
		int	LeftChild = Index * 2 + 1;

		// 더이상 자식노드가 없다면 종료한다.
		if (LeftChild >= m_Size)
			return;

		// 오른쪽 자식노드의 인덱스를 구해준다.
		int	RightChild = LeftChild + 1;

		int	ChildIndex = LeftChild;

		// 오른쪽 자식노드가 존재 한다면 오른쪽과 왼쪽의 값을
		// 비교하여 둘중 어떤 자식노드와 현재노드를 비교할지를
		// 결정해준다.
		if (RightChild < m_Size)
		{
			// 최소힙을 기준으로 오른쪽이 더 작다면 현재 노드와
			// 비교를 해야하는 노드는 오른쪽 노드가 된다.
			if (m_Func(m_Data[LeftChild], m_Data[RightChild]))
				ChildIndex = RightChild;
		}

		// 현재 노드와 비교할 최종 노드의 인덱스는 ChildIndex
		// 에 들어와있다.
		if (m_Func(m_Data[Index], m_Data[ChildIndex]))
		{
			T	Temp = m_Data[Index];
			m_Data[Index] = m_Data[ChildIndex];
			m_Data[ChildIndex] = Temp;

			// 값이 바뀌었다면 바뀐 위치에서의 부모노드와도 비교를
			// 계속해서 이어나가야 한다.
			Delete(ChildIndex);
		}
	}
};

