/****************************************
* std::find(), std::copy() 都在 algorithm 头文件中，详情
* 在 http://www.cplusplus.com/reference/algorithm/ 中自行查阅
* std::distance() 在头文件 iterator 中，用于求解两个迭代器之间的距离
* initializer_list 头文件的引入是为了方便对 MyVector 初始化的时候可以使用初始化列表进行初始化
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
	MyVector(int c = MAXCAPACITY, int s=0, T v=0); // 容量为c, 长度为0， 初始元素为 v;
	MyVector(T const* A, int lo, int hi); //区间复制
	MyVector(T const* A, int n); //整体复制
	MyVector(MyVector<T> const& v, int lo, int hi); //向量区间复制
	MyVector(MyVector<T> const& v); //向量整体复制
	~MyVector();
	int size() const;  // 报告当前向量规模
	bool empty() const; // 判断是否为空
	T get(int index) const; // 获取索引为 index 的元素
	void put(int index, T elem); // 用 elem 替换索引 index 处的元素
	void insert(int index, T const& elem); // 在 index 处插入 elem,同时将后继元素后移
	void insert(T const& elem); // 默认作为尾元素插入
	T remove(int index); // 删除 index 处的元素，同时将后继元素前移
	int remove(int lo, int hi); // 删除区间[lo, hi)之间的所有元素
	bool disorted() const; // 判断是否已按升序排列
	int find(T& elem) const; // 查找等于elem且索引最大的元素
	int find(T& elem, int lo, int hi); // 区间查找
	int search(T& elem) const; // 查找目标元素 elem, 返回不大于 elem且索引最大的元素
	int search(T& elem, int lo, int hi) const; // 区间查找
	void sort(int lo, int hi); // 区间排序
	void sort(); //整体排序
	void deduplicate(); // 删除重复元素
	void uniquify(); //删除重复元素
	T& operator[](int index) const; // 重载下标操作符
	MyVector<T>& operator=(const MyVector<T> & vec); // 赋值重载
	MyVector<T>& operator=(const initializer_list<T>& li); // 列表初始化
private:
	int m_maxCapacity = maxCopacity;
	int m_size;
	T* m_array;

protected:
	void copyFrom(T const* A, int lo, int hi); // 复制区间 A[lo, hi)
	void expand(); // 空间不足时扩容
	void shrink(); // 空间过大时压缩
	void bubble(int lo, int hi); // 扫描交换
	void bubbleSort(int lo=0, int hi=m_size-1); // 冒泡排序
	int max(int lo, int hi) const; // 区间内最大元素
	void selectSort(int lo = 0, int hi = m_size - 1); // 选择排序
	void mergeSort(int lo = 0, int hi = m_size - 1); // 并规排序
	void merge(int lo, int hi); // 并归算法
	int partition(int lo, int hi); // 轴点构造算法
	void quickSort(int lo = 0, int hi = m_size - 1); //快速排序
	void heapSort(int lo = 0, int hi = m_size - 1); // 堆排序
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
	// 推荐使用标准库中的函数
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
