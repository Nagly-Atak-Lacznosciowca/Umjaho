#ifndef UMJAHO_CIRCULARBUFFER_H
#define UMJAHO_CIRCULARBUFFER_H

template<typename T>
class CircularBuffer {
	public:
		CircularBuffer(int size);
		~CircularBuffer();
		
		void push_front(T element);
		void push_back(T element);
		void pop_front();
		void pop_back();
		
		int count();
		
		T operator[](int i) {
			return this->array[(this->start + (i % this->count())) % this->size];
		};
	
	private:
		int size;
		T *array;
		int start;
		int end;
};

#include "datatypes/CircularBuffer.tpp"

#endif //UMJAHO_CIRCULARBUFFER_H
