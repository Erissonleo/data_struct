/****************************************
* std::find(), std::copy() ���� algorithm ͷ�ļ��У�����
* �� http://www.cplusplus.com/reference/algorithm/ �����в���
* std::distance() ��ͷ�ļ� iterator �У������������������֮��ľ���
* initializer_list ͷ�ļ���������Ϊ�˷���� MyVector ��ʼ����ʱ�����ʹ�ó�ʼ���б���г�ʼ��
*
******************************************/


#ifndef __CHAPTER2_VECTOR__
#define __CHAPTER2_VECTOR__

#include <algorithm>
#include <iterator>
#include <initializer_list>

const int MAXCAPACITY = 1000;

template <typename T>
class MyVector {
public:
	MyVector(int c = MAXCAPACITY, int s=0, T v=0); // ����Ϊc, ����Ϊ0�� ��ʼԪ��Ϊ v;
	MyVector(T const* A, int lo, int hi); //���临��
	MyVector(T const* A, int n); //���帴��
	MyVector(MyVector<T> const& v, int lo, int hi); //�������临��
	MyVector(MyVector<T> const& v); //�������帴��
	~MyVector();
	int size() const;  // ���浱ǰ������ģ
	bool empty() const; // �ж��Ƿ�Ϊ��
	T get(int index) const; // ��ȡ����Ϊ index ��Ԫ��
	void put(int index, T elem); // �� elem �滻���� index ����Ԫ��
	void insert(int index, T const& elem); // �� index ������ elem,ͬʱ�����Ԫ�غ���
	void insert(T const& elem); // Ĭ����ΪβԪ�ز���
	T remove(int index); // ɾ�� index ����Ԫ�أ�ͬʱ�����Ԫ��ǰ��
	int remove(int lo, int hi); // ɾ������[lo, hi)֮�������Ԫ��
	bool disorted() const; // �ж��Ƿ��Ѱ���������
	int find(T& elem) const; // ���ҵ���elem����������Ԫ��
	int find(T& elem, int lo, int hi); // �������
	int search(T& elem) const; // ����Ŀ��Ԫ�� elem, ���ز����� elem����������Ԫ��
	int search(T& elem, int lo, int hi) const; // �������
	void sort(int lo, int hi); // ��������
	void sort(); //��������
	void deduplicate(); // ɾ���ظ�Ԫ��
	void uniquify(); //ɾ���ظ�Ԫ��
	T& operator[](int index) const; // �����±������
	MyVector<T>& operator=(const MyVector<T> & vec); // ��ֵ����
	MyVector<T>& operator=(const initializer_list<T>& li); // �б��ʼ��
private:
	int m_maxCapacity = maxCopacity;
	int m_size;
	T* m_array;

protected:
	void copyFrom(T const* A, int lo, int hi); // �������� A[lo, hi)
	void expand(); // �ռ䲻��ʱ����
	void shrink(); // �ռ����ʱѹ��
	void bubble(int lo, int hi); // ɨ�轻��
	void bubbleSort(int lo=0, int hi=m_size-1); // ð������
	int max(int lo, int hi) const; // ���������Ԫ��
	void selectSort(int lo = 0, int hi = m_size - 1); // ѡ������
	void mergeSort(int lo = 0, int hi = m_size - 1); // ��������
	void merge(int lo, int hi); // �����㷨
	int partition(int lo, int hi); // ��㹹���㷨
	void quickSort(int lo = 0, int hi = m_size - 1); //��������
	void heapSort(int lo = 0, int hi = m_size - 1); // ������
};

template<typename T>
MyVector<T>::MyVector(int c , int s, T v) : m_maxCapacity(c), m_size(s)
{
	m_array = new T[m_size];
	for (int i = 0; i < m_size; i++) {
		m_array[i] = v;
	}
}


template<typename T>
MyVector<T>::MyVector(T const* A, int lo, int hi) {
	copyFrom(A, lo, hi);
}


template<typename T>
MyVector<T>::MyVector(T const* A, int n) {
	copyFrom(A, 0, n);
}


template<typename T>
MyVector<T>::MyVector(MyVector<T> const& v, int lo, int hi) {
	copyFrom(v.m_array, lo, hi);
}


template<typename T>
MyVector<T>::MyVector(MyVector<T> const& v) {
	copyFrom(v.m_array, 0, v.m_size);
}


template<typename T>
MyVector<T>::~MyVector() {
	delete[] m_array;
}

template<typename T>
inline
void MyVector<T>::put(int index, T elem) {
	m_array[index] = elem;
}


template<typename T>
inline
int MyVector<T>::size() const {
	return m_size;
}


template<typename T>
bool MyVector<T>::empty() const {
	return !m_size;
}

template<typename T>
inline
T MyVector<T>::get(int index) const {
	return m_array[index];
}

template<typename T>
int MyVector<T>::find(T& elem) const {
	return find(elem, 0, m_size);
}


template<typename T>
int MyVector<T>::find(T& elem, int lo, int hi) {
	while (hi > lo) {
		if (elem = m_array[hi - 1])
			break;
		hi--;
	}
	return hi == lo ? -1 : hi-1;
}

template <typename T>
void MyVector<T>::expand() {
	if (m_size < m_maxCapacity)
		return;
	if (m_maxCapacity < MAXCAPACITY)
		m_maxCapacity = MAXCAPACITY;
	T* oldArray = m_array;
	m_array = new T[m_maxCapacity <<= 1];
	//for (int i = 0; i < m_size; i++) {
	//	m_array[i] = oldArray[i];
	//}
	// �Ƽ�ʹ�ñ�׼���еĺ���
	std::copy(oldArray, oldArray + m_size, m_array);
	delete[] oldArray;
}


template<typename T>
void MyVector<T>::shrink() {
	if (m_maxCapacity < (MAXCAPACITY << 1))
		return;
	if ((m_size << 2) > m_maxCapacity)
		return;
	T* oldArray = m_array;
	m_array = new T[m_maxCapacity >>= 1];
	std::copy(oldArray, oldArray + m_size, m_array);
	delete[] oldArray;
}


template <typename T>
inline
T& MyVector<T>::operator [](int index) const {
	return m_array[index];
}

template <typename T>
inline
MyVector<T>& MyVector<T>::operator =(const MyVector<T> & vec) {
	if (m_array)
		delete[] m_array;
	copyFrom(vec.m_array, 0, vec.m_size);
	return *this;
}

template<typename T>
inline 
MyVector<T>& MyVector<T>::operator=(const initializer_list<T>& li)
{
	if (m_array)
		delete[] m_array;
	m_array = li.begin();
	m_size = std::distance(li.begin(), li.end());
	return *this;
}


template <typename T>
void MyVector<T>::insert(int index, T const& elem) {
	if (m_size + 1 >= m_maxCapacity)
		expand();
	std::copy(index, m_size, index + 1);
	m_array[index] = elem;
	m_size++;
}


template <typename T>
void MyVector<T>::insert(T const& elem) {
	if (m_size + 1 >= m_maxCapacity)
		expand();
	m_array[m_size] = elem;
	m_size++;
}



template<typename T>
T MyVector<T>::remove(int index) {
	T e = m_array[index];
	std::copy(index + 1, m_size, index);
	m_size--;
	return e;
}


template<typename T>
int MyVector<T>::remove(int lo, int hi) {
	if (lo == hi)
		return;
	std::copy(hi, m_size, lo);
	m_size = lo + m_size - hi;
	if ((m_size << 2) < m_maxCapacity)
		shrink();
	return hi - lo;
}



template<typename T>
inline
void MyVector<T>::deduplicate() {
	int oldSize = m_size;
	int index = 1;
	while (index < m_size) {
		int index_found =  find(m_array[index], 0, index);
		if (index_found != -1)
			remove(index_found);
		index++;
	}
}


template<typename T>
inline
int MyVector<T>::search(T& elem, int lo, int hi) const {
	int index = find(elem, lo, hi);
	return index;
}

template<typename T>
inline
int MyVector<T>::search(T& elem) const {
	return find(elem, 0, m_size);
}

#endif
