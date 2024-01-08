#pragma once
#include <initializer_list>
#include <ostream>
#include <iostream>
#include <sstream>


	template <typename T>
	class Vector final
	{
	public:
		/*
		@brief ������������� ������ ���������� ���� vector � ������� initializer_list
		@param list ���� � ������� ������� ����� ������ vector
		*/

		Vector(const std::initializer_list<T> list);

		/*
		@brief �������, ������ ������ ����� �������
		*/
		~Vector();

		/*
		@brief ��������� ����������� ��������� � �������
		@return ����������� ��������� � �������
		*/
		size_t getSize() const;

		/*
		@brief �������� �������� �� ������� �� ������� ��������
		@param index ������ ��������
		*/


		void deleteI(size_t index);

		/*
		@brief ��������� ������� �������� � �������
		@param value ������� ������� �� ����
		@return ������ �������� � �������, ������ -1, ���� �������� � ������� ���
		*/
		bool findI(const T& value);

		/*
		@brief �������� �� ���������� ��������� � �������
		@return true ���� ��������� ��� � false ���� ��� ����
		*/
		bool isEmpty() const;

		/*
		@brief ���������� ��������� ���������� ������
		@param index ������ �������� � �������
		@return ������� �� ������� �� ��������� �������
		*/
		T& operator[](size_t index) const;

		/*
		@brief ���������� ��������� �����������
		@param Vector ������ ������� ����� ����������
		@return ������������� Vector
		*/
		Vector& operator=(const Vector<T>& vector);

		/*
		@brief ���������� ��������� �����������
		@param Vector ������ ��� �����������
		@return ������
		*/
		Vector& operator=(Vector<T>&& vector) noexcept;

		/*
		@brief ���������� ������������ �����������
		@param vector ������ ��� ����������
		*/
		Vector(const Vector& vector);

		/*
		@brief ���������� ������������ �����������
		@param vector ������ ��� �����������
		*/
		Vector(Vector<T>&& vector) noexcept;

		/*
		@brief ���������� ��������� ������
		@param os ����� ������
		@param vector ������ ��� ������
		*/
		friend std::ostream& operator<<(std::ostream& os, Vector<T>& vector);

		/*
		@brief ���������� ��������� �����
		@param rha ������ �������� ��� ���������
		@param lha ������ �������� ��� ���������
		@return false - ���� �����, true - ���� �� �����
		*/
		friend bool operator==(const Vector<T>& rha, const Vector<T>& lha) noexcept;

		/*
		@brief ���������� ��������� �� �����
		@param rha ������ �������� ��� ���������
		@param lha ������ �������� ��� ���������
		@return true - ���� �����, false - ���� �� �����
		*/
		friend bool operator!=(const Vector<T>& rha, const Vector<T>& lha) noexcept;

		/*
		@brief �������������� ������ � ������
		@return ������ �� �������
		*/
		std::string toString() const noexcept;

	private:
		size_t size;
		T* array;

	};
	template <typename T>
	Vector<T>::Vector(const std::initializer_list<T> list)
		:size(list.size())
	{
		this->array = new int[this->size];
		std::copy(list.begin(), list.end(), this->array);
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		delete[] this->array;
	}

	template <typename T>
	void Vector<T>::getSize() const
	{
		return this->size;
	}

	template <typename T>
	bool Vector<T>::isEmpty() const
	{
		return this->size == 0;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector& vector)
	{
		if (vector == *this)
		{
			return *this;
		}
		if (!this->isEmpty())
		{
			delete[] this->array;
			this->array = nullptr;
			this->size = 0;
		}
		this->array = new T[this->size];
		std::copy(vector.array, vector.array + vector.size, this->array);
		return *this;
	}

	template <typename T>
	Vector<T>&Vector<T>::operator=(Vector&& vector) noexcept
	{
		std::swap(vector.array, this->array);
		std::swap(vector.size, this->size);
		return *this;
	}

	template <typename T>
	Vector<T>::Vector(const Vector& vector)
		:size(vector.getSize()), array(nullptr)
	{
		std::copy(vector.array, vector.array + vector.getSize(), this->array);
	}

	template <typename T>
	Vector<T>::Vector(Vector&& vector) noexcept
		:size(0), array(nullptr)
	{
		std::swap(vector.array, this->array);
		std::swap(vector.size, this->size);
	}

	template <typename T>
	T&Vector<T>::operator[](size_t index) const
	{
		if (this->isEmpty() || index >= this->size or index < 0)
		{
			throw std::out_of_range("Incorrect Index");
		}
		return this->array[index];
	}

	template <typename T>
	void Vector<T>::deleteI(size_t index)
	{
		if (this->size == 0 or index < 0 or index >= this->size)
		{
			throw std::out_of_range("Incorrect Index");
		}
		T* vector1 = new int[this->size - 1];
		T now = 0;
		for (size_t i = 0; i < this->size; i++)
		{
			if (i != index)
			{
				vector1[now] = this->array[i];
				now++;
			}
		}
		delete[] this->array;
		this->array = vector1;
		this->size--;
	}

	template <typename T>
	bool Vector<T>::findI(const T& value)
	{
		if (this->isEmpty())
		{
			return -1;
		}
		T index = 0;
		while ((index < this->size) && this->array[index] != value)
		{
			index++;
		}
		if (index == this->size)
		{
			return -1;
		}
		else
		{
			return index;
		}
	}

	template <typename T>
	std::string Vector<T>::toString() const noexcept
	{
		std::stringstream sstring;
		for (size_t i = 0; i < this->size; i++)
		{
			sstring << this->array[i] << " ";
		}
		return sstring.str();
	}


	template <typename T>
	bool operator==(const Vector<T>& rha, const Vector<T>& lha) noexcept
	{
		return (rha.toString() == lha.toString());
	}

	template <typename T>
	bool operator!=(const Vector<T>& rha, const Vector<T>& lha) noexcept
	{
		return !(rha == lha);
	}

