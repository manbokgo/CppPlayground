#pragma once

#include <assert.h>

template <typename T>
class CArray
{
public:
	CArray()
	{
		m_Capacity = 4;
		m_Size = 0;

		m_Array = new T[m_Capacity];
	}

	~CArray()
	{
		delete[]	m_Array;
	}

private:
	T* m_Array;
	int	m_Size;		// �迭�� �߰��� ����
	int	m_Capacity;	// �迭�� ��ü ����

public:
	void push_back(const T& Data)
	{
		if (Full())
		{
			// 2�� ũ���� ������ ���� ������ش�.
			m_Capacity *= 2;

			T* Array = new T[m_Capacity];

			// ������ �迭�� �ִ� �����͸� ���� �Ҵ�� �迭�� �������ش�.
			for (int i = 0; i < m_Size; ++i)
			{
				Array[i] = m_Array[i];
			}

			// ������ �迭�� �����Ѵ�.
			delete[]	m_Array;

			// ���� ������ �迭�� �ּҸ� �Ѱ��ش�.
			m_Array = Array;
		}

		m_Array[m_Size] = Data;
		++m_Size;
	}

	void pop_back()
	{
		if (empty())
		{
			assert(false);
			return;
		}

		--m_Size;
	}

	int size()	const
	{
		return m_Size;
	}

	int capacity()	const
	{
		return m_Capacity;
	}

	bool Full()	const
	{
		return m_Size == m_Capacity;
	}

	bool empty()	const
	{
		return m_Size == 0;
	}

	void clear()
	{
		m_Size = 0;
	}

	T& operator [] (int Index)
	{
		if (Index < 0 || Index >= m_Size)
		{
			assert(false);
		}

		return m_Array[Index];
	}

	void erase(int Index)
	{
		for (int i = Index; i < m_Size; ++i)
		{
			m_Array[i] = m_Array[i + 1];
		}

		--m_Size;
	}

	void erase(int StartIndex, int EndIndex)
	{
		if (StartIndex > EndIndex)
		{
			int	Temp = StartIndex;
			StartIndex = EndIndex;
			EndIndex = Temp;
		}

		if (StartIndex < 0 || StartIndex >= m_Size ||
			EndIndex < 0 || EndIndex >= m_Size)
		{
			assert(false);
			return;
		}

		int	Count = m_Size - EndIndex - 1;

		for (int i = 0; i < Count; ++i)
		{
			m_Array[StartIndex + i] = m_Array[EndIndex + 1 + i];
		}

		m_Size -= (EndIndex - StartIndex + 1);
	}

	void eraseData(const T& Data)
	{
		for (int i = 0; i < m_Size; ++i)
		{
			if (m_Array[i] == Data)
			{
				for (int j = i; j < m_Size; ++j)
				{
					m_Array[j] = m_Array[j + 1];
				}

				--m_Size;

				break;
			}
		}
	}

	void Sort(bool(*Func)(const T&, const T&))
	{
		for (int i = 0; i < m_Size - 1; ++i)
		{
			for (int j = i + 1; j < m_Size; ++j)
			{
				if (Func(m_Array[i], m_Array[j]))
				{
					T	Temp = m_Array[i];
					m_Array[i] = m_Array[j];
					m_Array[j] = Temp;
				}
			}
		}
	}
};

