# 插入排序

我们将欲排序的元素称为`Key`。插入排序的思想就是将`A[j]`（key）插入到前面`A[1..j-1]`有序序列的第一个使得该序列仍然保持有序的位置。

比如有这样一组数`[1,2,3,3,5,6,4]`

取key=4，前面序列为有序序列，该序列按<谓词排序，那么有两种思路：

* 从后往前：从Key前一位开始依次比较，在第一个不满足该谓词的元素后面插入
* 从前往后：从第一位开始依次比较，在第一个满足该谓词的元素前面插入

根据此思想，我们很容易写出以下伪码：

```cpp
INSERTION SORT(A,Predicate)
for j=2 to A.length
	Key=A[j]
    i=j-1
    while(i>0 and Predicate(Key,A[i]))
        A[i+1]=A[i]
		i=i-1
	A[j+1]=Key 
```

翻译成C++如下：

```cpp
template<typename T,typename Pred>
void insert_sort(std::vector<T>& vec, Pred const& p) {
	int len=vec.size();
	for (int i=1; i!=len; ++i) {
		auto key=vec[i];
		int b=i-1;
		while (b>=0&&p(key,vec[b])) {
			vec[b+1]=vec[b];
			b-=1;
		}
		vec[b+1]=key;
	}
}    
```

## 检验算法正确性

通过循环不变式检验即可：

循环不变式为：**子序列保持有序**

* 初始：在第一次迭代前序列为`A[1]`，故有序

* 维持：在下一次迭代前为`A[1..j]`，根据前面所讲，通过`A[j-1]`,`A[j-2]`,...的移动和`Key`的插入，使得`A[1..j]`依然为有序

* 终止：循环终止时，子序列为`A[1..A.length]`，显然有序

因此插入排序的算法是正确的