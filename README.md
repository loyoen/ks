# ks
ks server framework
<br>

### note
* 首次适应算法的内存管理在MemoryOptimize分支上
* 5个处理线程，QPS达到2.5w+

### todo
* 内存管理整个链表加锁效率太低，进一步优化
* epoll部分代码重构
* HttpParser
