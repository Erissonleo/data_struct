#ifndef __CHAPTER2_VECTOR__
#define __CHAPTER2_VECTOR__

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
	void insert(int index, T& elem); // �� index ������ elem,ͬʱ�����Ԫ�غ���
	void insert(T const& elem); // Ĭ����ΪβԪ�ز���
	T remove(int index); // ɾ�� index ����Ԫ�أ�ͬʱ�����Ԫ��ǰ��
	int remove(int lo, int hi); // ɾ������[lo, hi)֮�������Ԫ��
	bool disorted() const; // �ж��Ƿ��Ѱ���������
	void sort(); // ��������
	T find(T& elem) const; // ���ҵ���elem����������Ԫ��
	T find(T& elem, int lo, int hi); // �������
	int search(T& elem) const; // ����Ŀ��Ԫ�� elem, ���ز����� elem����������Ԫ��
	int search(T& elem, int lo, int hi); // �������
	void sort(int lo, int hi); // ��������
	void sort(); //��������
	void deduplicate(); // ɾ���ظ�Ԫ��
	void uniquify(); //ɾ���ظ�Ԫ��
	void traverse(void(*)(T&)); // ����������ͳһ��������Ԫ�أ��������ɺ�������ָ��
	template<typename VST>
	void traverse(VST&); // ʹ�ú���������б���
	T& operator[](int index) const; // �����±������
	MyVector<T>& operator=(MyVector<T> const& vec); // ��ֵ����
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
