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

private:
	int m_size;
	ListNodePosi(T) m_header;
	ListNodePosi(T) m_tailer;
protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi(T) p, int n); //拷贝列表中从p开始的n项
	void merge(ListNodePosi(T)& p, int n, ListNodePosi(T)& q, int n); // 将两个列表归并到一起
	void mergeSort(ListNodePosi(T)& p, int n);
};



#endif // !__CH3_LIST__
