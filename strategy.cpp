//
// Created by Lone Kriss on 2020/11/15.
//

#include "strategy.h"
#include <utility>
#include <iostream>

using std::cout;
void bubble::sort(vector<int> &num) {
    for(size = num.size(); size > 1; size--){
        for(int i = 0, j = 1;j<size; j++,i++ ){
            if(num[i]>num[j]){
                std::swap(num[i],num[j]);
            }
        }
    }
}


void selection::sort(vector<int> &num) {

    int min_i = 0;
    size = num.size();
    for(int i = 0; i < size -1; i++){
        min  = num[i];
        for(int j = i+1; j<size;j++){
            if(num[j] < min){
                min = num[j];
                min_i = j;
            }
        }
        std::swap(num[i],num[min_i]);
    }
}


void insertion::sort(vector<int> &num) {
    size = num.size();
    int preIndex = 0, culdight = 0;
    for(int i = 1; i<size; i++){
        preIndex = i-1;
        culdight = num[i];
        while(preIndex>=0 && culdight < num[preIndex]){
            num[preIndex+1] = num[preIndex];
            --preIndex;
        }
        num[preIndex+1] = culdight;
    }
}


void myclass::merge::sort(vector<int> &num) {
    int left = 0;
    int right = num.size()-1;
    mergeSort(num, left, right);
}


void myclass::merge::mergeSort(vector<int> &num, int left, int right) {
    if(left<right){
        int mid = (left+right)/2;
        mergeSort(num, left,mid);
        mergeSort(num,mid+1,right);
        mergeArray(num,left, mid, mid+1, right);
    }

}


void myclass::merge::mergeArray(vector<int> &num, int L1, int R1, int L2, int R2) {
    int temp[R2-L1+1];
    int i = L1, j = L2;
    int k = 0;
    while(i<=R1 && j<=R2){
        num[i]<num[j]?temp[k++] = num[i++]:temp[k++] = num[j++];
    }
    while(i<=R1) temp[k++]=num[i++];
    while(j<=R2) temp[k++]=num[j++];

    for(int x = 0; x<k;x++){
        num[L1+x] = temp[x];
    }
}


void quick::sort(vector<int> &num) {
    int size = num.size();
    int right = size -1;
    int left = 0;
    quickSort(num, left , right);
}


void quick::quickSort(vector<int> &num, int left, int right) {
    if(left>=right) return;
    int base = left;
    int right_base =right;
    while(left!=right){
        while(left<right && num[right]>=num[base]) right--;
        while(left<right && num[left]<=num[base] ) left++;
        std::swap(num[left],num[right]);
    }
    std::swap(num[left],num[base]);
    //注意传入的参数
    quickSort(num,base,left-1);
    quickSort(num,left+1,right_base);
}


void heap::sort(vector<int> &num) {
    int size = num.size();
    heap_sort(num,size);
}

void heap::heapify(vector<int> &num, int size, int i) {
    int largest = i;
    int leftChild = i * 2 + 1;
    int rightChild = i * 2 + 2;

    if(leftChild<size && num[largest] < num[leftChild])
        largest = leftChild;
    if(rightChild<size && num[largest] < num[rightChild])
        largest = rightChild;

    if(largest != i)
    {
        std::swap(num[largest], num[i]);
        heapify(num,size,largest);
    }

}

void heap::heap_sort(vector<int> &num, int size) {
    for(int i = size/2 - 1; i>=0; i--){              //(n-1-1) /2
        heapify(num,size,i);
    }

    for(int i = size - 1 ; i>0;i--){
        std::swap(num[0],num[i]);
        heapify(num,i,0);     //传入i相当于把最后一个节点删除，size = i
    }
}
