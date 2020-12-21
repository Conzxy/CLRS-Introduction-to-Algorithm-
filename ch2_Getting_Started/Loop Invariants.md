# 循环不变式

循环不变式是一个用来证明循环过程是否正确的不变量，分为三个阶段：

* `Initialization`:在第一次迭代开始前确保不变量为真
* `Maintenace`:在一次迭代前为真，到下一次迭代前保持为真
* `Termination`:循环终止时，根据不变式是否为真可以得知循环是否正确

依据循环不变式我们可以验证任何算法的循环过程是否正确

循环不变式前两个步骤类似于数学归纳法，最后一个步骤不同，因为数学归纳法是无穷的，而循环是有穷的