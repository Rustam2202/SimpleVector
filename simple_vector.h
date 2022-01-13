#pragma once

#include "array_ptr.h"

#include <cassert>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename Type>
class SimpleVector {
public:
	using Iterator = Type*;
	using ConstIterator = const Type*;

	SimpleVector() noexcept = default;

	// Создаёт вектор из size элементов, инициализированных значением по умолчанию
	explicit SimpleVector(size_t size) : array_(size) {
		// Напишите тело конструктора самостоятельно
		size_ = size;
		capacity_ = size;
		std::fill(begin(), end(), 0);

		/*for (int i = 0; i < size; ++i) {
			array_[i] = 0;
		}*/
	}

	// Создаёт вектор из size элементов, инициализированных значением value
	SimpleVector(size_t size, const Type& value) : array_(size) {
		// Напишите тело конструктора самостоятельно
		size_ = size;
		capacity_ = size;
		std::fill(begin(), end(), value);

		/*for (int i = 0; i < size; ++i) {
			array_[i] = value;
		}*/
	}

	// Создаёт вектор из std::initializer_list
	SimpleVector(std::initializer_list<Type> init) : array_(init.size()) {
		// Напишите тело конструктора самостоятельно
		size_ = init.size();
		capacity_ = init.size();
		auto it = init.begin();
		for (size_t i = 0; i < init.size(); ++i) {
			array_[i] = *it;
			it++;
		}
	}

	// Возвращает количество элементов в массиве
	size_t GetSize() const noexcept {
		// Напишите тело самостоятельно
		return size_;
	}

	// Возвращает вместимость массива
	size_t GetCapacity() const noexcept {
		// Напишите тело самостоятельно
		return capacity_;
	}

	// Сообщает, пустой ли массив
	bool IsEmpty() const noexcept {
		return !(bool)size_;
	}

	// Возвращает ссылку на элемент с индексом index
	Type& operator[](size_t index) noexcept {
		// Напишите тело самостоятельно
		return array_[index];
	}

	// Возвращает константную ссылку на элемент с индексом index
	const Type& operator[](size_t index) const noexcept {
		// Напишите тело самостоятельно
		return array_[index];
	}

	// Возвращает константную ссылку на элемент с индексом index
	// Выбрасывает исключение std::out_of_range, если index >= size
	Type& At(size_t index) {
		// Напишите тело самостоятельно
		if (index >= size_) {
			throw std::out_of_range("Error: out of range");
		}
		else {
			return array_[index];
		}
	}

	// Возвращает константную ссылку на элемент с индексом index
	// Выбрасывает исключение std::out_of_range, если index >= size
	const Type& At(size_t index) const {
		// Напишите тело самостоятельно
		if (index >= size_) {
			throw std::out_of_range("Error: out of range");
		}
		else {
			return array_[index];
		}
	}

	// Обнуляет размер массива, не изменяя его вместимость
	void Clear() noexcept {
		// Напишите тело самостоятельно
		size_ = 0;
	}

	// Изменяет размер массива.
	// При увеличении размера новые элементы получают значение по умолчанию для типа Type
	void Resize(size_t new_size) {
		// Напишите тело самостоятельно
		if (new_size <= size_) {
			size_ = new_size;
		}
		else if (new_size <= capacity_) {
			std::fill(end(), &array_[new_size], 0);
			size_ = new_size;
		}
		else if (new_size > capacity_) {

			ArrayPtr<Type> new_array(new_size);
			std::fill(&new_array[0], &new_array[new_size], 0);
			std::copy(begin(), end(), new_array.Get());
			array_.swap(new_array);
			size_ = new_size;
			capacity_ = new_size;
		}
	}

	// Возвращает итератор на начало массива
	// Для пустого массива может быть равен (или не равен) nullptr
	Iterator begin() noexcept {
		// Напишите тело самостоятельно
		return &array_[0];
	}

	// Возвращает итератор на элемент, следующий за последним
	// Для пустого массива может быть равен (или не равен) nullptr
	Iterator end() noexcept {
		// Напишите тело самостоятельно
		return &array_[size_];
	}

	// Возвращает константный итератор на начало массива
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator begin() const noexcept {
		// Напишите тело самостоятельно
		return &array_[0];
	}

	// Возвращает итератор на элемент, следующий за последним
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator end() const noexcept {
		// Напишите тело самостоятельно
		return &array_[size_];
	}

	// Возвращает константный итератор на начало массива
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator cbegin() const noexcept {
		// Напишите тело самостоятельно
		return &array_[0];
	}

	// Возвращает итератор на элемент, следующий за последним
	// Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator cend() const noexcept {
		// Напишите тело самостоятельно
		return &array_[size_];
	}

private:
	ArrayPtr<Type> array_;
	size_t size_ = 0;
	size_t capacity_ = 0;
};