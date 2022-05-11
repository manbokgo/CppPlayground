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
	int	m_Size;		// 배열에 추가된 개수
	int	m_Capacity;	// 배열의 전체 개수

public:
	void push_back(const T& Data)
	{
		if (Full())
		{
			// 2배 크기의 공간을 새로 만들어준다.
			m_Capacity *= 2;

			T* Array = new T[m_Capacity];

			// 기존의 배열에 있던 데이터를 새로 할당된 배열에 복사해준다.
			for (int i = 0; i < m_Size; ++i)
			{
				Array[i] = m_Array[i];
			}

			// 기존의 배열을 제거한다.
			delete[]	m_Array;

			// 새로 생성한 배열의 주소를 넘겨준다.
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

