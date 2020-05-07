#ifndef __CHAPTER2_VECTOR__
#define __CHAPTER2_VECTOR__

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
	void insert(int index, T& elem); // 在 index 处插入 elem,同时将后继元素后移
	void insert(T const& elem); // 默认作为尾元素插入
	T remove(int index); // 删除 index 处的元素，同时将后继元素前移
	int remove(int lo, int hi); // 删除区间[lo, hi)之间的所有元素
	bool disorted() const; // 判断是否已按升序排列
	void sort(); // 升序排列
	T find(T& elem) const; // 查找等于elem且索引最大的元素
	T find(T& elem, int lo, int hi); // 区间查找
	int search(T& elem) const; // 查找目标元素 elem, 返回不大于 elem且索引最大的元素
	int search(T& elem, int lo, int hi); // 区间查找
	void sort(int lo, int hi); // 区间排序
	void sort(); //整体排序
	void deduplicate(); // 删除重复元素
	void uniquify(); //删除重复元素
	void traverse(void(*)(T&)); // 遍历向量并统一处理所用元素，处理方法由函数对象指定
	template<typename VST>
	void traverse(VST&); // 使用函数对象进行遍历
	T& operator[](int index) const; // 重载下标操作符
	MyVector<T>& operator=(MyVector<T> const& vec); // 赋值重载
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

inline
template<typename T>
MyVector<T>::MyVector(int c = MAXCAPACITY, int s = 0, T v = 0) : m_maxCapacity(c), m_size(s)
{
	m_array = new T[m_size];
	for (int i = 0; i < m_size; i++) {
		m_array[i] = v;
	}
}

inline
template<typename T>
MyVector<T>::MyVector(T const* A, int lo, int hi) {
	copyFrom(A, lo, hi);
}

inline
template<typename T>
MyVector<T>::MyVector(T const* A, int n) {
	copyFrom(A, 0, n);
}

inline
template<typename T>
MyVector<T>::MyVector(MyVector<T> const& v, int lo, int hi) {
	copyFrom(v.m_array, lo, hi);
}

inline
template<typename T>
MyVector<T>::MyVector(MyVector<T> const& v) {
	copyFrom(v.m_array, 0, v.m_size);
}

inline
template<typename T>
MyVector<T>::~MyVector() {
	delete[] m_array;
}


inline
template<typename T>
int MyVector::size() const {
	return m_size;
}

inline
template<typename T>
bool MyVector<T>::empty() const {
	return !m_size;
}

inline
template<typename T>
int MyVector<T>::find(T& elem) const {
	return find(elem, 0, m_size);
}



#endif
