#ifndef INSERT_SORT_H
#define INSERT_SORT_H

#include <vector>

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

#endif //INSERT_SORT_H