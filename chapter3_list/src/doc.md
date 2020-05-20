列表节点的ADT接口

data() : 当前节点的数据对象
pred() : 当前节点的前驱节点的位置
succ() : 当前节点的后继节点的位置
insertAsPred(e) : 插入前驱节点，存入被人用对象e,返回新节点的位置
insertAsSucc(e) : 插入后继节点，存入被人用对象e,返回新节点的位置


列表的 ADT 接口
size()			: 返回当前列表的规模
first()			: 返回首节点的位置
last()			: 返回尾节点的位置
insertAsFirst(e): 将e当作首节点插入
insertAsLast(e)	: 将e当作尾节点插入
remove(p)		: 移除节点p,返回对应的元素
disordered()	：判断所有节点是否已按非降序排列
sort()			：调整各节点的位置，使之按非降序排列
find(e)			：查找元素e,失败是返回 nullptr
search(e)		: 查找元素e,返回不大于e且秩最大的节点		适用对象：有序列表
deduplicate()	：删除重复的节点
uniquify()		：删除重复的节点							适用对象：有序列表
traverse()		：遍历并统一处理所有节点，处理方法由函数对象指定