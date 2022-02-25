#pragma once
class Container
{
public:
	Container(int capacity = 10);
	~Container();

	int Size() const;
	int Capacity() const;
	int Get(int index) const;

	void Set(int index, int newValue);
	void PushBack(int element);




private:
	int m_Size;
	int m_Capacity;
	int* m_pElement;

	void Reserve(int newCapacity);
};

