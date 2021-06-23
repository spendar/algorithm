package com.company;

public class Sort {

    /**
     * 冒泡排序
     * @param a 待排序数组
     */
    public void bubbleSort(int[] a){
        int len = a.length;
        for(int i = 0; i < len; i++){
            for(int j = 1; j < len-i; j++){
                if(a[j] < a[j-1]){
                    int temp = a[j];
                    a[j] = a[j-1];
                    a[j-1] = temp;
                }
            }
        }
    }

    /**
     * 选择排序
     * @param a 待排序数组
     */
    public void selectSort(int[] a){
        int len = a.length;
        for(int i = 0; i < len; i++){
            int index = 0;
            int temp = a[0];
            for(int j = 0; j < len-i; j++){
                if(a[j] > temp){
                    index = j;
                    temp = a[j];
                }
            }
            int t = a[len-1-i];
            a[len-1-i] = temp;
            a[index] = t;
        }
    }

    /**
     * 插入排序
     * @param a 待排序数组
     */
    public void insertSort(int[] a){
        int len = a.length;
        for(int i = 1; i < len; i++){
            int temp = a[i];
            int index = i;
            while(index >= 1 && temp < a[index-1]) {
                a[index] = a[index - 1];
                index--;
            }
            a[index] = temp;
        }
    }

    /**
     * 快速排序
     * @param a 待排序数组
     * @param start 数组起始位置
     * @param end 数组结束位置，左闭右开
     */
    public void quickSort(int[] a, int start, int end){
        if(start >= end)    return;
        int index = partion(a, start, end);
        quickSort(a, start, index);
        quickSort(a, index+1, end);
    }

    private int partion(int[] a, int start, int end) {
        int key = a[start];
        int left = start;
        int right = end - 1;
        while(left < right){
            while(left < right && a[right] > key)
                right--;
            if(left < right){
                int temp = a[right];
                a[right] = a[left];
                a[left] = temp;
            }
            while(left < right && a[left] < key)
                left++;
            if(left < right){
                int temp = a[right];
                a[right] = a[left];
                a[left] = temp;
            }
        }
        return left;
    }

    /**
     * 归并排序
     * @param a 待排序数组
     * @param start 数组起始位置
     * @param end 数组结束位置 左闭右开
     */
    public void mergeSort(int a[], int start, int end){
        if(start>= end-1) return;
        int mid = (start + end) / 2;
        mergeSort(a, start, mid);
        mergeSort(a, mid, end);
        merge(a, start, mid, end);
    }

    private void merge(int a[], int start, int mid, int end){
        int t[] = new int[end - start];
        int index = 0;
        int index1 = start;
        int index2 = mid;
        while(index1 < mid && index2 < end){
            if(a[index1] < a[index2])
                t[index++] = a[index1++];
            else
                t[index++] = a[index2++];
        }
        while(index1 < mid)
            t[index++] = a[index1++];
        while(index2 < end)
            t[index++] = a[index2++];
        for(int i = 0; i < end-start; i++)
            a[start+i] = t[i];
    }

    /**
     * 堆排序
     * @param a 待排序数组
     */
    public void headSort(int a[]){
        Heap heap = new Heap(a.length, false);
        for(int n : a)
            heap.push(n);
        for(int i = 0; i < a.length; i++)
            a[i] = heap.pop();
    }

    public static void main(String[] args){
        int a[] = {6,8,3,7,2,0,9,5,4,1};
        Sort s = new Sort();
        s.headSort(a);
        for(int num: a)
            System.out.print(num + " ");
    }
}

