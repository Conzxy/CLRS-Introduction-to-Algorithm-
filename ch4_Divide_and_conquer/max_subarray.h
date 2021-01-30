#ifndef ITA_MAX_SUBARRAY_H
#define ITA_MAX_SUBARRAY_H

#include <iostream>
#include <vector>
#include <algorithm>
#define INF 65535

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

int maxSubArray_dp(std::vector<int>& arr){
    int len=arr.size();
    std::vector<int> dp(len);
    int maxAns=arr[0];
    for(int i=1;i<len;++i){
        dp[i]=std::max(dp[i-1]+arr[i],arr[i]);
        maxAns=std::max(dp[i],maxAns);
    }
    return maxAns;
}
#endif //ITA_MAX_SUBARRAY_H
