#include <cstdlib>

template <typename T>
CircularBuffer<T>::CircularBuffer(int size) {
	this->start = 0;
	this->end = 0;
	
	this->size = size;
	
	this->array = (T*)malloc(this->size * sizeof(T));
}

template <typename T>
CircularBuffer<T>::~CircularBuffer() {
	free(this->array);
}

template <typename T>
void CircularBuffer<T>::push_front(T element) {
	if (--this->start < 0)
		this->start = this->size - 1;
	
	this->array[this->start] = element;
}

template <typename T>
void CircularBuffer<T>::push_back(T element) {
	this->array[this->end] = element;
	
	this->end = (this->end + 1) % this->size;
}

template <typename T>
void CircularBuffer<T>::pop_front() {
	this->start = (this->start + 1) % this->size;
}

template <typename T>
void CircularBuffer<T>::pop_back() {
	if (--this->end < 0)
		this->end = this->size - 1;
}

template <typename T>
int CircularBuffer<T>::count() {
	return (this->end - this->start + this->size) % this->size;;
}