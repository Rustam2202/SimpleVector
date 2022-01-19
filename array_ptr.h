#include <utility>

template <typename Type>
class ArrayPtr {
public:
	// �������������� ArrayPtr ������� ����������
	ArrayPtr() = default;

	// ������ � ���� ������ �� size ��������� ���� Type. ���� size == 0, ���� raw_ptr_ ������ ���� ����� nullptr
	explicit ArrayPtr(size_t size) {
		if (!size == 0) {
			Type* arr = new Type[size];
			raw_ptr_ = arr;
		}
	}

	// ����������� �� ������ ���������, ��������� ����� ������� � ���� ���� nullptr
	explicit ArrayPtr(Type* raw_ptr) noexcept {
		raw_ptr_ = raw_ptr;
	}

	// ��������� �����������
	ArrayPtr(const ArrayPtr&) = delete;

	ArrayPtr(ArrayPtr&& other) {
		raw_ptr_ = std::exchange(other.raw_ptr_, nullptr);
	}

	// ��������� ������������
	ArrayPtr& operator=(const ArrayPtr&) = delete;

	ArrayPtr& operator=(ArrayPtr&& other) {
		raw_ptr_ = std::exchange(other.raw_ptr_, nullptr);
		return *this;
	}

	~ArrayPtr() {
		delete[]raw_ptr_;
	}

	// ���������� ��������� �������� � ������, ���������� �������� ������ �������. ����� ������ ������ ��������� �� ������ ������ ����������
	[[nodiscard]] Type* Release() noexcept {
		Type* temp = raw_ptr_;
		raw_ptr_ = nullptr;
		return temp;
	}

	// ���������� ������ �� ������� ������� � �������� index
	Type& operator[](size_t index) noexcept {
		return raw_ptr_[index];
	}

	// ���������� ����������� ������ �� ������� ������� � �������� index
	const Type& operator[](size_t index) const noexcept {
		return raw_ptr_[index];
	}

	// ���������� true, ���� ��������� ���������, � false � ��������� ������
	explicit operator bool() const {
		return raw_ptr_ != nullptr;
	}

	// ���������� �������� ������ ���������, ��������� ����� ������ �������
	Type* Get() const noexcept {
		return raw_ptr_;
	}

	// ������������ ��������� ��������� �� ������ � �������� other
	void swap(ArrayPtr& other) noexcept {
		Type* temp = other.Get();
		other.raw_ptr_ = raw_ptr_;
		raw_ptr_ = temp;
	}

private:
	Type* raw_ptr_ = nullptr;
};