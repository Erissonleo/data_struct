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
