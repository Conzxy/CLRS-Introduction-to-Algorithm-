#ifndef ITA_MAX_SUBARRAY_H
#define ITA_MAX_SUBARRAY_H

#include <iostream>
#include <vector>
#define INF 65535

//暴力破解：Θ(n^2)
void brute_max_subarray(std::vector<int>& arr,std::vector<int>& vec){
    int len=arr.size();
    if(!len)
        return ;
    int max=-INF;
    int low=0,high=0;

    for(int i=0;i!=len;++i){
        int sum=0;
        for(int j=i;j!=len;++j){
            sum+=arr[j];
            if(sum>max){
                max=sum;
                low=i;
                high=j;
            }
        }
    }

    for(int i=low;i<=high;++i)
        vec.push_back(arr[i]);
}

//贪心算法：如前面的和为负数，则从下一个重新开始
//O(n)
void greedy_max_subarray(std::vector<int>& arr,std::vector<int>& vec){
    int len=arr.size();
    if(!len)
        return ;

    int max=-INF;
    int low=0,high=0;
    int cur=0;
    int sum=0;

    for(int i=0;i!=len;++i){
        sum+=arr[i];
        if(sum>max){
            max=sum;
            low=cur;
            high=i;
        }
        if(sum<0){
            cur+=1;
            sum=0;
        }
    }
    for(int i=low+1;i<=high;++i)
        vec.push_back(arr[i]);
}

//分治递归：最大子数组只可能出现在左边，右边或跨中点
//O(nlgn)
int find_max_crossing_subarray(std::vector<int>& vec,int low,int high,int mid){
    int left_sum=-INF;
    int sum=0;

    int max_left=-1,max_right=-1;

    for(int i=mid;i>=low;--i){
        sum=sum+vec[i];
        if(sum>left_sum){
            left_sum=sum;
        }
    }

    sum=0;
    int right_sum=-INF;
    for(int j=mid+1;j<=high;++j){
        sum=sum+vec[j];
        if(sum>right_sum){
            right_sum=sum;
        }
    }

    return left_sum+right_sum;
}

int find_max_subarray(std::vector<int>& vec,int low,int high){
    if(low==high){
        return vec[low];
    }
    else{
        int mid=(low+high)/2;

        int left_sum=find_max_subarray(vec,low,mid);
        int right_sum=find_max_subarray(vec,mid+1,high);
        int crossing_sum=find_max_crossing_subarray(vec,low,high,mid);

        return std::max(std::max(left_sum,right_sum),crossing_sum);
    }
}

#endif //ITA_MAX_SUBARRAY_H
