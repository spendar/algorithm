package com.company;

public class Heap {
    private int size;
    private int capacity;
    private int data[];
    private boolean flag;

    public Heap(){
        size = 0;
        capacity = 16;
        data = new int[capacity+1];
        flag = true;
    }

    public Heap(boolean flag){
        size = 0;
        capacity = 16;
        data = new int[capacity+1];
        this.flag = flag;
    }

    public Heap(int capacity){
        size = 0;
        this.capacity = capacity;
        data = new int[capacity+1];
        flag = true;
    }

    public Heap(int capacity, boolean flag){
        size = 0;
        this.capacity = capacity;
        data = new int[capacity+1];
        this.flag = flag;
    }

    public boolean isMaxHeap(){
        return flag;
    }

    public boolean isMinHeap(){
        return !flag;
    }

    private void upMax(int index){
        int f = index / 2;
        while(f > 0){
            if(data[f] < data[index]){
                int temp = data[f];
                data[f] = data[index];
                data[index] = temp;
                index = f;
                f = index / 2;
            }else{
                break;
            }
        }
    }

    private void downMax(int index){
        int c = index * 2;
        while(c <= size){
            if(c+1 <= size && data[c+1] > data[c])
                c++;
            if(data[index] < data[c]) {
                int temp = data[c];
                data[c] = data[index];
                data[index] = temp;
                index = c;
                c = index * 2;
            }else{
                break;
            }
        }
    }

    private void upMin(int index){
        int f = index / 2;
        while(f > 0){
            if(data[f] > data[index]){
                int temp = data[f];
                data[f] = data[index];
                data[index] = temp;
                index = f;
                f = index / 2;
            }else{
                break;
            }
        }
    }

    private void downMin(int index){
        int c = index * 2;
        while(c <= size){
            if(c+1 <= size && data[c+1] < data[c])
                c++;
            if(data[index] > data[c]) {
                int temp = data[c];
                data[c] = data[index];
                data[index] = temp;
                index = c;
                c = index * 2;
            }else{
                break;
            }
        }
    }

    public void push(int val){
        if(size == capacity)    return;
        data[++size] = val;
        if(flag)
            upMax(size);
        else
            upMin(size);
    }

    public int pop(){
        if(size == 0)   return -1;
        int temp = data[1];
        data[1] = data[size--];
        if(flag)
            downMax(1);
        else
            downMin(1);
        return temp;
    }
}
