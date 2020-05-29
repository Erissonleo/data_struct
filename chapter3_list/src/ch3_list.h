#ifndef __CH3_LIST__
#define __CH3_LIST__

#include "listNode.h"

template <typename T>
class List {
public:
	List();
	List(const List<T>& L);  //拷贝构造
	List(const List<T>& L, Rank r, int n); // 拷贝一部分
	List(ListNodePosi(T) p, int n);	//拷贝一部分
	~List();
	//只读访问接口
	Rank size() const;
	bool empty() const;
	T& operator[](Rank r) const;
	ListNodePosi(T) first() const; // 首节点位置
	ListNodePosi(T) last() const;
	bool valid(ListNodePosi(T) p); // 判断位置p是否对外合法
	int disordered() const;
	ListNodePosi(T) find(const T& e) const;
	ListNodePosi(T) find(const T& e, int n, ListNodePosi(T) p) const; //无序区间倒序查找
	ListNodePosi(T) search(const T& e) const; //有序列表查找
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); // 在 P 到 后面 n-1 个后继中选出最大
	ListNodePosi(T) selectMax(); //全局查找
	//可写访问接口
	ListNodePosi(T) insertAsFirst(const T& elem); //首节点插入
	ListNodePosi(T) insertAsLast(const T& elem);
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, const T& elem); //p的前驱插入
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, const T& elem); // p的后继插入
	T remove(ListNodePosi(T) p); //删除合法节点p, 返回删除的节点
	void merge(List<T>& L); //全列表并规
	void sort(ListNodePosi(T) p, int n); //列表区间排序
	void sort(); // 列表整体排序
	int deduplicate(); // 无序去重
	int uniquify(); // 有序去重
	void reverse(); // 前后倒置
	//遍历
	void traverse(void(*)(T& elem)); // 遍历，依次实施 visit 操作
	template<typename VST>
	void traverse(VST&);

private:
	int m_size;
	ListNodePosi(T) m_header;
	ListNodePosi(T) m_tailer;
protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi(T) p, int n); //拷贝列表中从p开始的n项
	void merge(ListNodePosi(T)& p, int n, ListNodePosi(T)& q, int m); // 将两个列表归并到一起
	void mergeSort(ListNodePosi(T)& p, int n); // 从p开始连续n个节点并规排序
	void selectionSort(ListNodePosi(T) p, int n); // 从p开始连续n个节点选择排序
	void insertionSort(ListNodePosi(T) p, int n); // 从p开始联系n个节点插入排序
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

//TODO: 我觉得此处还可以修改，可读性太差
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