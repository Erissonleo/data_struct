#ifndef __CH3_LIST__
#define __CH3_LIST__

#include "listNode.h"

template <typename T>
class List {
public:
	List();
	List(const List<T>& L);  //��������
	List(const List<T>& L, Rank r, int n); // ����һ����
	List(ListNodePosi(T) p, int n);	//����һ����
	~List();
	//ֻ�����ʽӿ�
	Rank size() const;
	bool empty() const;
	T& operator[](Rank r) const;
	ListNodePosi(T) first() const; // �׽ڵ�λ��
	ListNodePosi(T) last() const;
	bool valid(ListNodePosi(T) p); // �ж�λ��p�Ƿ����Ϸ�
	int disordered() const;
	ListNodePosi(T) find(const T& e) const;
	ListNodePosi(T) find(const T& e, int n, ListNodePosi(T) p) const; //�������䵹�����
	ListNodePosi(T) search(const T& e) const; //�����б����
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); // �� P �� ���� n-1 �������ѡ�����
	ListNodePosi(T) selectMax(); //ȫ�ֲ���
	//��д���ʽӿ�
	ListNodePosi(T) insertAsFirst(const T& elem); //�׽ڵ����
	ListNodePosi(T) insertAsLast(const T& elem);
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, const T& elem); //p��ǰ������
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, const T& elem); // p�ĺ�̲���
	T remove(ListNodePosi(T) p); //ɾ���Ϸ��ڵ�p, ����ɾ���Ľڵ�
	void merge(List<T>& L); //ȫ�б���
	void sort(ListNodePosi(T) p, int n); //�б���������
	void sort(); // �б���������
	int deduplicate(); // ����ȥ��
	int uniquify(); // ����ȥ��
	void reverse(); // ǰ����
	//����
	void traverse(void(*)(T& elem)); // ����������ʵʩ visit ����
	template<typename VST>
	void traverse(VST&);

private:
	int m_size;
	ListNodePosi(T) m_header;
	ListNodePosi(T) m_tailer;
protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi(T) p, int n); //�����б��д�p��ʼ��n��
	void merge(ListNodePosi(T)& p, int n, ListNodePosi(T)& q, int m); // �������б�鲢��һ��
	void mergeSort(ListNodePosi(T)& p, int n); // ��p��ʼ����n���ڵ㲢������
	void selectionSort(ListNodePosi(T) p, int n); // ��p��ʼ����n���ڵ�ѡ������
	void insertionSort(ListNodePosi(T) p, int n); // ��p��ʼ��ϵn���ڵ��������
};



#endif // !__CH3_LIST__

template<typename T>
inline List<T>::List()
{
	init();
}

template<typename T>
inline Rank List<T>::size() const
{
	return m_size;
}

template<typename T>
inline bool List<T>::empty() const
{
	return m_size <= 0;
}

template<typename T>
inline T& List<T>::operator[](Rank r) const
{
	ListNodePosi(T) p = first();
	while (r > 0)
	{
		p = p->succ;
		--r;
	}
	return p->data;
}

template<typename T>
inline ListNodePosi(T) List<T>::first() const
{
	return m_header->succ;
}

template<typename T>
inline ListNodePosi(T) List<T>::last() const
{
	return m_tailer->pred;
}

template<typename T>
inline bool List<T>::valid(ListNodePosi(T) p)
{
	return p && (m_tailer != p) && (m_header != p);
}

template<typename T>
inline ListNodePosi(T) List<T>::find(const T& e) const
{
	return find(e, m_size, m_tailer);
}

//TODO: �Ҿ��ô˴��������޸ģ��ɶ���̫��
template<typename T>
inline ListNodePosi(T) List<T>::find(const T& elem, int n, ListNodePosi(T) p) const
{
	while (0 < n--)
	{
		if (elem == (p = p->pred)->data)
			return p;
	}
	return nullptr;
}

template<typename T>
inline ListNodePosi(T) List<T>::selectMax()
{
	return selectMax(m_header->succ, m_size);
}

template<typename T>
inline ListNodePosi(T) List<T>::insertAsFirst(const T& elem)
{
	m_size++;
	return m_header->insertAsSucc(elem);
}

template<typename T>
inline ListNodePosi(T) List<T>::insertAsLast(const T& elem)
{
	m_size++;
	return m_tailer->insertAsPred(elem);
}

template<typename T>
inline ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, const T& elem)
{
	m_size++;
	return p->insertAsPred(elem);
}

template<typename T>
inline ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, const T& elem)
{
	m_size++;
	return p->insertAsSucc(elem);
}

template<typename T>
inline void List<T>::merge(List<T>& L)
{
	merge(first(), m_size, L.first(), L.m_size);
}

template<typename T>
inline void List<T>::sort()
{
	sort(first(), m_size);
}

template<typename T>
inline void List<T>::init()
{
	m_header = new ListNode<T>;
	m_tailer = new ListNode<T>;
	m_header->succ = m_tailer;
	m_header->pred = nullptr;
	m_tailer->succ = nullptr;
	m_tailer->pred = m_header;
	m_size = 0;
}