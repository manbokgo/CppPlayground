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

		// ���ο� �����Ͱ� �߰��� �ε����� ���ڷ� �Ѱܼ� ������
		// ���� �����۾��� �����Ѵ�.
		// ���� �߰��ϴ� �������� �迭 �ε��� �Ѱ��ִ°�.
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

		// 1�� ���ҽ�Ų��.
		--m_Size;

		// ���� �������� �߰��Ǿ� �ִ� ���� ��Ʈ�� �÷��ش�.
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
		// Index�� 0�̸� ��Ʈ����� �ǹ��̱� ������ ���̻�
		// �۾��� ���ϰ� ��ȯ���ش�.
		if (Index == 0)
			return;

		// ���� �ε����� �θ� �ε����� �����ش�.
		int	ParentIndex = (Index - 1) / 2;

		if (m_Func(m_Data[ParentIndex], m_Data[Index]))
		{
			T	Temp = m_Data[ParentIndex];
			m_Data[ParentIndex] = m_Data[Index];
			m_Data[Index] = Temp;

			// ���� �ٲ���ٸ� �ٲ� ��ġ������ �θ���͵� �񱳸�
			// ����ؼ� �̾���� �Ѵ�.
			Insert(ParentIndex);
		}
	}

	void Delete(int Index)
	{
		// ���� �ڽĳ���� �ε����� �����ش�.
		int	LeftChild = Index * 2 + 1;

		// ���̻� �ڽĳ�尡 ���ٸ� �����Ѵ�.
		if (LeftChild >= m_Size)
			return;

		// ������ �ڽĳ���� �ε����� �����ش�.
		int	RightChild = LeftChild + 1;

		int	ChildIndex = LeftChild;

		// ������ �ڽĳ�尡 ���� �Ѵٸ� �����ʰ� ������ ����
		// ���Ͽ� ���� � �ڽĳ��� �����带 ��������
		// �������ش�.
		if (RightChild < m_Size)
		{
			// �ּ����� �������� �������� �� �۴ٸ� ���� ����
			// �񱳸� �ؾ��ϴ� ���� ������ ��尡 �ȴ�.
			if (m_Func(m_Data[LeftChild], m_Data[RightChild]))
				ChildIndex = RightChild;
		}

		// ���� ���� ���� ���� ����� �ε����� ChildIndex
		// �� �����ִ�.
		if (m_Func(m_Data[Index], m_Data[ChildIndex]))
		{
			T	Temp = m_Data[Index];
			m_Data[Index] = m_Data[ChildIndex];
			m_Data[ChildIndex] = Temp;

			// ���� �ٲ���ٸ� �ٲ� ��ġ������ �θ���͵� �񱳸�
			// ����ؼ� �̾���� �Ѵ�.
			Delete(ChildIndex);
		}
	}
};

