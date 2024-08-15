#include <iostream>
#define MAXSIZE 100
using namespace std;

class Mysqueue {
    //利用数组创建有序队列    数据就存储int类型      栈的main中实现了顺序队列的代码，这里实现顺序栈和链队列
public:
    int* array;         //顺序队列中一个数组实现数据存储
    int index;          //index用于记录栈顶元素的下标
    Mysqueue() {
        array=new int[MAXSIZE];
        index=0;
    }
    ~Mysqueue() {
        delete array;
        array=nullptr;
    }
    bool isEmpty() {
        if(index==0)
            return true;
        return false;
    }
    void PushStack(int value) {
        if(index>MAXSIZE-2) {
            std::cout<<"Stack is full"<<std::endl;
            return;
        }
        array[index]=value;
        index++;
    }
    int Popstack() {
        if(index==0) {
            std::cout<<"Stack is blank"<<std::endl;
            return -1;
        }
        index--;
        return array[index];
    }
    int getLength() {
        return index;
    }
    void clearStack() {
        index=0;
    }




};

class Sque {             //这里开始书写链队列基本操作
    //这个代码的实现就是实现之前链标的设计中，从链表头删除元素和在链表尾添加元素的操作，此处称为入队和出队
public:
    int value;    //作为数据字段
    Sque* next;   //记录下一个结点的位置
    //在链队列的实现中可以设计一个头指针和尾指针，尾指针始终指向链表末尾
    Sque(int val,Sque* sq=nullptr):value(val),next(sq){}
    Sque(){};
};
void initSque(Sque*& header,Sque*& last) {
    header=new Sque();
    if(header==nullptr) {
        std::cout<<"Wrong"<<std::endl;
        return;
    }
    last=header;
}
void PushLink(Sque* header,Sque*& last,int value) {
    Sque* ele=new Sque(value);
    if(header==last) {
        header->next=ele;
        last=ele;
    }else {
        last->next=ele;
        last=ele;
    }
}
int PopLink(Sque*& header) {
    Sque* temp=header->next;
    header->next=temp->next;
    int value=temp->value;
    delete temp;
    return value;
}
void Printall(Sque* header,Sque* last) {
    if(header==last) {
        std::cout<<"There is no factor"<<std::endl;
    }
    while(header!=last) {
        header=header->next;
        std::cout<<header->value<<std::endl;
    }
}
int getLength(Sque* header,Sque* last) {
    int i=0;
    if(header==last)
        return 0;
    while(header!=last) {
        header=header->next;
        i++;
    }
    return i;
}

int main() {
    // Mysqueue* queue=new Mysqueue;
    // std::cout<<queue->isEmpty()<<std::endl;
    // queue->PushStack(1);
    // queue->PushStack(2);
    // queue->PushStack(3);
    // queue->PushStack(4);
    // queue->PushStack(5);
    // std::cout<<queue->getLength()<<std::endl;
    // queue->Popstack();
    // queue->Popstack();
    // std::cout<<queue->getLength()<<std::endl;
    // for(int i=0;i<queue->getLength();i++) {
    //     std::cout<<queue->array[i]<<std::endl;
    // }
    //以上代码实现了顺序栈的基本操作检验

    Sque* header;
    Sque* last;
    initSque(header,last);
    cout<<header<<"\t"<<last<<endl ;
    PushLink(header,last,1);
    cout<<header<<"\t"<<last<<endl;
    PushLink(header,last,2);
    cout<<header<<"\t"<<last<<endl;
    PushLink(header,last,3);
    cout<<header<<"\t"<<last<<endl;
    PushLink(header,last,4);
    cout<<header<<"\t"<<last<<endl;
    Printall(header,last);
    PushLink(header,last,5);
    cout<<header<<"\t"<<last<<endl;
    PopLink(header);
    Printall(header,last);
    cout<<getLength(header,last)<<endl;        //有一个问题，我的链表是连续的空间
    return 0;
}
