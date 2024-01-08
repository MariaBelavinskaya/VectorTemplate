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
		@brief Инициализация нового экземпляра типа vector с помощью initializer_list
		@param list Лист с помощью которго будет создан vector
		*/

		Vector(const std::initializer_list<T> list);

		/*
		@brief Удаляет, чистит память после вектора
		*/
		~Vector();

		/*
		@brief Получение колличества элементов в векторе
		@return Колличество элементов в векторе
		*/
		size_t getSize() const;

		/*
		@brief Удаление элемента из вектора по индексу элемента
		@param index Индекс элемента
		*/


		void deleteI(size_t index);

		/*
		@brief Получение индекса элемента в векторе
		@param value Элемент который мы ищем
		@return Индекс элемента в векторе, вернет -1, если элемента в векторе нет
		*/
		bool findI(const T& value);

		/*
		@brief Проверка на отсутствие элементов в векторе
		@return true если элементов нет и false если они есть
		*/
		bool isEmpty() const;

		/*
		@brief Перегрузка оператора квадратных скобок
		@param index Индекс элемента в векторе
		@return Элемент из вектора по заданному индексу
		*/
		T& operator[](size_t index) const;

		/*
		@brief Перегрузка оператора копирования
		@param Vector Вектор который будет скопирован
		@return Скопированный Vector
		*/
		Vector& operator=(const Vector<T>& vector);

		/*
		@brief Перегрузка оператора перемещения
		@param Vector Вектор для перемещения
		@return Вектор
		*/
		Vector& operator=(Vector<T>&& vector) noexcept;

		/*
		@brief Перегрузка конструктора перемещения
		@param vector Вектор для перемещния
		*/
		Vector(const Vector& vector);

		/*
		@brief Перегрузка конструктора копирования
		@param vector Вектор для копирования
		*/
		Vector(Vector<T>&& vector) noexcept;

		/*
		@brief Перегрузка оператора вывода
		@param os Поток вывода
		@param vector Вектор для вывода
		*/
		friend std::ostream& operator<<(std::ostream& os, Vector<T>& vector);

		/*
		@brief Перегрузка оператора равно
		@param rha Первый аргумент для сравнения
		@param lha Второй аргумент для сравнения
		@return false - если равны, true - если не равны
		*/
		friend bool operator==(const Vector<T>& rha, const Vector<T>& lha) noexcept;

		/*
		@brief Перегрузка оператора не равно
		@param rha Первый аргумент для сравнения
		@param lha Второй аргумент для сравнения
		@return true - если равны, false - если не равны
		*/
		friend bool operator!=(const Vector<T>& rha, const Vector<T>& lha) noexcept;

		/*
		@brief Преобразование объета в строку
		@return Строка из объекта
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

