#ifndef __LISTNODE__
#define __LISTNODE__

using Rank = int;

#define ListNodePosi(T) ListNode<T>*  //列表节点位置

template<typename T>
struct ListNode
{
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;
	ListNode() {};
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
		: data(e), pred(p), succ(s)
	{ }
	ListNodePosi(T) insertAsPred(const T& e);
	ListNodePosi(T) insertAsSucc(const T& e);
};



#endif // !__LISTNODE__

template<typename T>
inline ListNodePosi(T) ListNode<T>::insertAsPred(const T& e)
{
	ListNodePosi(T) x = new ListNode(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template<typename T>
inline ListNodePosi(T) ListNode<T>::insertAsSucc(const T& e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}
