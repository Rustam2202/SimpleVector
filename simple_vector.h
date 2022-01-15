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
	explicit
		SimpleVector(size_t size) : array_(size) {
		size_ = size;
		capacity_ = size;
		std::fill(begin(), end(), 0);
	}

	// Создаёт вектор из size элементов, инициализированных значением value
	SimpleVector(size_t size, const Type& value) : array_(size) {
		size_ = size;
		capacity_ = size;
		std::fill(begin(), end(), value);
	}

	// Создаёт вектор из std::initializer_list
	SimpleVector(std::initializer_list<Type> init) : array_(init.size()) {
		size_ = init.size();
		capacity_ = init.size();
		auto it = init.begin();
		for (size_t i = 0; i < init.size(); ++i) {
			array_[i] = *it;
			it++;
		}
	}

	// Конструктор копирования
	SimpleVector(const SimpleVector& other) : array_(other.capacity_) {
		// Напишите тело конструктора самостоятельно
		SimpleVector<Type> temp(other.capacity_);
		temp.size_ = other.size_;
		std::copy(other.begin(), other.end(), temp.begin());
		swap(temp);
	}

	// Возвращает количество элементов в массиве
	size_t GetSize() const noexcept {
		return size_;
	}

	// Возвращает вместимость массива
	size_t GetCapacity() const noexcept {
		return capacity_;
	}

	// Сообщает, пустой ли массив
	bool IsEmpty() const noexcept {
		return size_ == 0;
	}

	// Возвращает ссылку на элемент с индексом index
	Type& operator[](size_t index) noexcept {
		return array_[index];
	}

	// Возвращает константную ссылку на элемент с индексом index
	const Type& operator[](size_t index) const noexcept {
		return array_[index];
	}

	// Возвращает константную ссылку на элемент с индексом index. Выбрасывает исключение std::out_of_range, если index >= size
	Type& At(size_t index) {
		if (index >= size_) {
			throw std::out_of_range("Error: out of range");
		}
		else {
			return array_[index];
		}
	}

	// Возвращает константную ссылку на элемент с индексом index. Выбрасывает исключение std::out_of_range, если index >= size
	const Type& At(size_t index) const {
		if (index >= size_) {
			throw std::out_of_range("Error: out of range");
		}
		else {
			return array_[index];
		}
	}

	// Обнуляет размер массива, не изменяя его вместимость
	void Clear() noexcept {
		size_ = 0;
	}

	// Изменяет размер массива. При увеличении размера новые элементы получают значение по умолчанию для типа Type
	void Resize(size_t new_size) {
		if (new_size <= size_) {
			size_ = new_size;
			//capacity_ = new_size;
		}
		else if (new_size <= capacity_) {
			std::fill(end(), &array_[new_size], 0);
			size_ = new_size;
			//capacity_ = new_size;
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

	// Возвращает итератор на начало массива. Для пустого массива может быть равен (или не равен) nullptr
	Iterator begin() noexcept {
		return &array_[0];
	}

	// Возвращает итератор на элемент, следующий за последним. Для пустого массива может быть равен (или не равен) nullptr
	Iterator end() noexcept {
		return &array_[size_];
	}

	// Возвращает константный итератор на начало массива. Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator begin() const noexcept {
		return &array_[0];
	}

	// Возвращает итератор на элемент, следующий за последним. Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator end() const noexcept {
		return &array_[size_];
	}

	// Возвращает константный итератор на начало массива. Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator cbegin() const noexcept {
		return &array_[0];
	}

	// Возвращает итератор на элемент, следующий за последним. Для пустого массива может быть равен (или не равен) nullptr
	ConstIterator cend() const noexcept {
		return &array_[size_];
	}

	SimpleVector& operator=(const SimpleVector& rhs) {
		// Напишите тело конструктора самостоятельно
		if (this != &rhs) {
			SimpleVector<Type> temp(rhs);
			std::copy(rhs.begin(), rhs.end(), temp.begin());
			swap(temp);
		}
		return *this;
	}

	// Добавляет элемент в конец вектора. При нехватке места увеличивает вдвое вместимость вектора
	void PushBack(const Type& item) {
		// Напишите тело самостоятельно
		if (capacity_ == 0) {
			ArrayPtr<Type> arr_ptr(1);
			array_.swap(arr_ptr);
			capacity_ = 1;
			size_ = 0;
		}

		auto old_size = size_;
		if (size_ >= capacity_) {
			Resize(capacity_ * 2);
			size_ = old_size;
		}
		array_[size_] = item;
		size_++;
	}

	// Вставляет значение value в позицию pos. Возвращает итератор на вставленное значение
	// Если перед вставкой значения вектор был заполнен полностью, вместимость вектора должна увеличиться вдвое, а для вектора вместимостью 0 стать равной 1
	Iterator Insert(ConstIterator pos, const Type& value) {
		// Напишите тело самостоятельно

		size_t index = 0;
		Type* it = begin();
		while (it != pos) {
			it++;
			index++;
		}

		if (size_ < capacity_) {
			SimpleVector<Type> temp(capacity_);
			temp.size_ = size_;
			std::copy(begin(), it, temp.begin());
			temp.array_[index] = value;
			std::copy(it, end(), &temp[index + 1]);
			array_.swap(temp.array_);
			size_++;
		}
		else {
			if (capacity_ == 0) {
				ArrayPtr<Type> arr_ptr(1);
				array_.swap(arr_ptr);
				capacity_ = 1;
				size_ = 0;
				it = begin();
			}

			SimpleVector<Type> temp(capacity_ * 2);
			temp.size_ = size_;
			std::copy(begin(), it, temp.begin());
			temp[index] = value;
			std::copy(it, end(), &temp[index + 1]);
			array_.swap(temp.array_);
			std::swap(capacity_, temp.capacity_);
			size_++;

		}
		return &array_[index];
	}

	// "Удаляет" последний элемент вектора. Вектор не должен быть пустым
	void PopBack() noexcept {
		// Напишите тело самостоятельно
		if (!IsEmpty()) {
			size_--;
		}
	}

	// Удаляет элемент вектора в указанной позиции
	Iterator Erase(ConstIterator pos) {
		// Напишите тело самостоятельно
		size_t index = 0;
		Type* it = begin();
		while (it != pos) {
			it++;
			index++;
		}

		SimpleVector<Type> temp(capacity_);

		std::copy(begin(), it, temp.begin());
		std::copy(it + 1, end(), &temp[index]);
		array_.swap(temp.array_);
		size_--;
		return &array_[index];
	}

	// Обменивает значение с другим вектором
	void swap(SimpleVector& other) noexcept {
		// Напишите тело самостоятельно
		array_.swap(other.array_);
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
	}

	// Показать содержимое массива
	void Show() {
		using namespace std;
		for (size_t i = 0; i < size_; ++i) {
			cout << array_[i] << " ";
		}
		cout << "capacity = " << capacity_ << endl;
	}

private:
	ArrayPtr<Type> array_;
	size_t size_ = 0;
	size_t capacity_ = 0;


};

template <typename Type>
inline bool operator==(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
	// Заглушка. Напишите тело самостоятельно
	return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator!=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
	// Заглушка. Напишите тело самостоятельно
	return !std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator<(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
	// Заглушка. Напишите тело самостоятельно
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator<=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
	// Заглушка. Напишите тело самостоятельно
	return !std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename Type>
inline bool operator>(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
	// Заглушка. Напишите тело самостоятельно
	return std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename Type>
inline bool operator>=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
	// Заглушка. Напишите тело самостоятельно
	return !std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}