# STL

这个项目是在大一暑假,为了深入学习STL而开始的一个造轮子项目.由于github帐号有所变迁,项目被转移到了这里.

现在回头来看,当时的完成度还是不够.

## 项目进度

|组件|完成度|说明|
|-|-:|:-|
|allocator|100%|可投入正式使用|  
|iterator_base|30%|适配器未完成，不可投入使用.目前各容器的iterator都差不多是重写的，能和标准库兼容|  
|vector|100%|预期功能已完成，其他功能不再补充(如：copy constructor,copy-assignment constructor.....)    |
|list|100%|预期功能已完成，其他功能不再补充|
|deque|100%|预期功能已完成，期间发现c++11新特性：：rvalue-reference|
|stack|100%||
|queue|100%||   
|heap|100%||
|priority_queue|100%|| 
|binary-search-tree|100%||
|balanced-binary-search-tree|0%||
|set|90%|底层容器使用普通的二叉树|
|map|90%|底层容器使用普通的二叉树|
  
