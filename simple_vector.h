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
	SimpleVector(const SimpleVector& other) : array_(other.GetCapacity()) {
		// Напишите тело конструктора самостоятельно
		std::copy(other.begin(), other.end(), begin());
		size_ = other.size_;
		capacity_ = other.GetCapacity();
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
			SimpleVector<Type> tmp(rhs);
			std::copy(rhs.begin(), rhs.end(), array_.Get());
			size_ = rhs.GetSize();

			//swap(tmp);
		}
		return *this;
	}

	// Добавляет элемент в конец вектора. При нехватке места увеличивает вдвое вместимость вектора
	void PushBack(const Type& item) {
		// Напишите тело самостоятельно

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

		Type* it = std::find(begin(), end(), *pos);
		//*it = 0;


		using namespace std;
		{
			for (size_t i = 0; i < capacity_; ++i) {
				cout << array_[i] << " ";
			}cout << endl;
		}

		if (size_ < capacity_) {
			std::copy_backward(it, end(), end() + 1);
			*it = value;
			size_++;
		}
		else {
			SimpleVector<Type> temp(capacity_ * 2);
			temp.size_ = 0;

			std::copy(begin(), it, temp.begin());
			temp.size_;

			{
				for (size_t i = 0; i < temp.GetCapacity(); ++i) {
					cout << temp[i] << " ";
				}cout << endl;
			}

			temp.PushBack(value);

			{
				for (size_t i = 0; i < temp.GetCapacity(); ++i) {
					cout << temp[i] << " ";
				}cout << endl;
			}

			std::copy(it, end(), temp.end());

			{
				for (size_t i = 0; i < temp.GetCapacity(); ++i) {
					cout << temp[i] << " ";
				}cout << endl;
			}

			std::swap(*this,temp);
			size_++;
			capacity_ *= 2;

			{
				for (size_t i = 0; i < capacity_; ++i) {
					cout << array_[i] << " ";
				}cout << endl;
			}
		}



		size_++;
		return 0;
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
		//using namespace std;
		// Напишите тело самостоятельно
		SimpleVector<Type> temp(size_);

		//cout << array_[0] << " " << array_[1] << " " << array_[2] << endl;
		std::copy(pos + 1, cend(), temp.begin());
		//cout << temp[0] << " " << temp[1] << endl;
		std::copy(temp.cbegin(), temp.cend(), (int*)pos);
		//cout << array_[0] << " " << array_[1] << " " << array_[2] << endl;
		//std::copy(temp.begin(), temp.end(), end());
		size_--;
		return 0;
	}

	// Обменивает значение с другим вектором
	void swap(SimpleVector& other) noexcept {
		// Напишите тело самостоятельно
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