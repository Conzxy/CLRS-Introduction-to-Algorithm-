//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2021/1/21.
//

#ifndef ITA_ACTIVITIES_CHOICE_H
#define ITA_ACTIVITIES_CHOICE_H

#include <iostream>
#include <vector>
#include <string>
#include <dimArray.h>

void print_act(int** c,int** act,int i,int j){
    if(c[i][j]>0){
        int k=act[i][j];
        print_act(c,act,i,k);
        print_act(c,act,k,j);
        std::cout<<"a"<<k<<" ";
    }
}

void Activities_Choice(int* s,int* f,int k,int n,std::vector<std::string>& act){
    int m=k+1;
    while(m<=n&&s[m]<f[k])
        ++m;
    if(m<=n) {
        act.emplace_back("a" + std::to_string(m));
        Activities_Choice(s,f,m,n,act);
    }
}

void Activity_Selector(int *s,int *f,int n){
    auto c=newArray2<int>(n+2,n+2);
    auto act=newArray2<int>(n+2,n+2);
    
    initArray2(c,n+2,n+2);

    int tmp=0;
    for(int j=1;j<=n+1;++j){
        for (int i=0; i<j; ++i) {
                for (int k=i+1; k<j; ++k) {
                    if (f[i]<=s[k]&&f[k]<=s[j]) {
                        if (tmp<c[i][k]+c[k][j]+1) {
                            tmp=c[i][k]+c[k][j]+1;
                            act[i][j]=k;
                        }
                    }
                }
                c[i][j]=tmp;
                tmp=0;
        }
    }
    
    std::cout<<c[0][n+1];
    print_act(c,act,0,n+1);

    deleteArray2(c,n+2);
    deleteArray2(act,n+2);
}

void Activity_Selection(int* s, int* f, int n) {
    auto c=newArray2<int>(n+2,n+2);
    auto act=newArray2<int>(n+2,n+2);

    for(int i=0;i<=n;++i){
        c[i][i]=0;
        c[i][i+1]=0;
    }
    c[n+1][n+1]=0;
    int j,k;
    for(int l=2;l<=n+1;++l){
        for(int i=0;i<=n+1-l;++i){
            j=i+l;
            c[i][j]=0;
            k=j-1;
            for(k=j-1;k>i;--k){
                if(f[i]<=s[k] && f[k]<=s[j] && c[i][j]<c[i][k]+c[k][j]+1){
                        c[i][j]=c[i][k]+c[k][j]+1;
                        act[i][j]=k;
                }
            }
        }
    }

    std::cout<<c[0][n+1];
    print_act(c,act,0,n+1);

    deleteArray2(c,n+2);
    deleteArray2(act,n+2);
}
#endif //ITA_ACTIVITIES_CHOICE_H
