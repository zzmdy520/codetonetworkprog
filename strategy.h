//
// Created by Lone Kriss on 2020/11/15.
//

#ifndef SORT_STRATEGY_H
#define SORT_STRATEGY_H

#include <utility>
#include <vector>
using std::vector;

class strategy {
public:
    virtual void sort(vector<int>& num) = 0;
};

class bubble: public strategy{
public:
    bubble():size(0){};
    void sort(vector<int>& num) override;
private:
    int size;
};


class selection:public strategy{
public:
    selection():size(0),min(0){};
    void sort(vector<int>& num) override;
private:
    int size;
    int min;
};

class insertion:public strategy{
public:
    insertion():size(0){};
    void sort(vector<int>& num) override;
private:
    int size;
};

namespace myclass {
    class merge : public strategy {
    public:
        void sort(vector<int> &num) override;

        void mergeSort(vector<int> &num, int left, int right);

        void mergeArray(vector<int> &num, int L1, int R1, int L2, int R2);
    };
}

class quick:public strategy{
public:
    void sort(vector<int> &num) override;
    void quickSort(vector<int> &num, int i, int j);
};

class heap:public strategy{
public:
    void sort(vector<int> &num) override;
    void heapify(vector<int> &num,int size, int index);
    void heap_sort(vector<int> &num,int n);
};

class context{
public:
    explicit context(std::shared_ptr<strategy> theStrategy):_strategy(std::move(theStrategy)){};
    void run(vector<int> &num){_strategy->sort(num);};
private:
    std::shared_ptr<strategy> _strategy;


};

#endif //SORT_STRATEGY_H
