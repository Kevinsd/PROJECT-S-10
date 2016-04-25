#ifndef _Vector_
#define _Vector_
#include <stdio.h>

template <class TYPE>

class Vector
{
private:
	TYPE* buffer = nullptr;
	unsigned int capacity = 5;
	unsigned int num_elements = 0;

public:
	Vector()
	{


		buffer = new TYPE[capacity];

	}
	Vector(const Vector& other)
	{

		capacity = other.capacity;
		num_elements = other.num_elements;
		buffer = new TYPE[capacity];
		for (unsigned int i = 0; i < num_elements; i++)
		{
			buffer[i] = other.buffer[i];
		}

	}

	void push_back(const TYPE& element)
	{
		TYPE* temp = nullptr;
		if (capacity == num_elements)
		{
			capacity += 8;
			temp = new TYPE[capacity];

			for (unsigned int i = 0; i < num_elements; i++)
			{
				temp[i] = buffer[i];
			}

			delete[]buffer;
			buffer = temp;
		}

		buffer[num_elements++] = element;

	}
	bool pop_back(TYPE& value)
	{
		if (value.num_elements > 0){
			value.num_elements--;
			return true;
		}
		return false;
	}

	TYPE Pop_Back()
	{
		if (num_elements > 0)
		{

			num_elements--;

			return buffer[num_elements];
		}

	}
	void push_front(const TYPE& element)
	{
		if (capacity == num_elements)
		{

			TYPE* temp = nullptr;
			capacity += 8;
			temp = new TYPE[capacity];

			for (unsigned int i = num_elements; i > 0; i--)
			{
				temp[i] = buffer[i - 1];
			}
			delete[] buffer;
			buffer = temp;
		}
		else
		{
			for (unsigned int i = num_elements; i > 0; i--)
			{
				buffer[i] = buffer[i - 1];
			}
		}
		buffer[0] = element;
		num_elements++;
	}

	TYPE* Pick(int to_pick)
	{
		if (to_pick < num_elements)
		{
			TYPE* tmp = &buffer[to_pick];
			for (unsigned int i = to_pick + 1; i < num_elements; i++)
			{
				buffer[i - 1] = buffer[i];
			}
			num_elements--;
			return tmp;
		}
			return NULL;
	}

	bool empty() const
	{
		return num_elements == 0;
	}

	unsigned int size()const
	{
		return num_elements;
	}

/*	const TYPE& operator[]( unsigned int &index)const
	{
//		assert(index >= 0 && index < num_elements)
			return buffer[index];
	}
	*/

	TYPE operator[]( unsigned int &index)
	{
	//	assert(index >= 0 && index < num_elements)
			return buffer[index];
	}

	void PrintVector()const
	{
		for (unsigned int i = 1; i < num_elements; i++)
		{
			printf("%i", buffer[i]);
		}
	}

	void clear()
	{
		num_elements = 0;
	}


	~Vector()
	{
			
		delete[] buffer;
	}

};
#endif