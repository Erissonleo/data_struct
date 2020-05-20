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

private:
	int m_size;
	ListNodePosi(T) m_header;
	ListNodePosi(T) m_tailer;
protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi(T) p, int n); //�����б��д�p��ʼ��n��
	void merge(ListNodePosi(T)& p, int n, ListNodePosi(T)& q, int n); // �������б�鲢��һ��
	void mergeSort(ListNodePosi(T)& p, int n);
};



#endif // !__CH3_LIST__
