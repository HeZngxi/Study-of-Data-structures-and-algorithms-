#include <iostream>

#define MAXSIZE 100
using namespace std;

class Warehousesqrt {
public:
    int* value;
    int rear;
    int front;

    bool initWare() {
        value = new int[MAXSIZE];
        if(value==nullptr) {
            std::cout<<"Wrong"<<std::endl;
            return false;
        }
        front=rear=0;
        return true;
    }
    ~Warehousesqrt() {
        delete[] value;
    }    //销毁栈
    bool isEmpty() {
        if(front==rear) {
            return true;
        }
        return false;
    }
    int getLength() {            //返回栈的长度
        return ((rear-front)+MAXSIZE)%MAXSIZE;
    }
    bool Push(int number) {          //入栈
        if(((rear-front)+MAXSIZE)%MAXSIZE==MAXSIZE-1) {
            //这里判断是否栈满，rear指向的位置实际没有内容，空内容便于判断栈满和栈空
            cout<<"Already full"<<endl;
            return false;
        }
        value[rear]=number;
        rear=(rear+1)%MAXSIZE;
        return false;
    }
    int Pop() {
        if(isEmpty()==true) {
            cout<<"Blank"<<endl;
            return 0;
        }
        int delele=value[front];
        front++;
        return delele;
    }
    int getTop() {
        if(isEmpty()==1) {
            cout<<"Empty"<<endl;
            return -1;
        }
        return value[rear-1];
    }
    void clearStack() {
        rear=front=0;
    }
    void Printall() {
        if(front==rear) {
            cout<<"there is no factor"<<endl;
            return;
        }
        for(int i=front;i<rear;i++) {
            cout<<value[i]<<"\t";
        }
    }

};
class LinkWarehouse {
    //链栈中不需要设计头结点，并且只需要一个头指针即可
public:
    LinkWarehouse(int vau,LinkWarehouse* p=nullptr):value(vau),prev(p){};
    LinkWarehouse(){};
    int value;  //数据字段
    LinkWarehouse* prev;
};
void initLink(LinkWarehouse*& top) {
    top=new LinkWarehouse;
    if(top==nullptr) {
        cout<<"fail to set top"<<endl;
        return;
    }
    top->prev=nullptr;
    top->value=-1;
}
void PushLink(LinkWarehouse*& top,int value) {
    LinkWarehouse* ele=new LinkWarehouse(value);
    ele->prev=top;
    // cout<<ele<<"\t"<<ele->prev<<endl;
    top=ele;
}
void PopLink(LinkWarehouse*& top) {
    if(top->prev==nullptr) {
        cout<<"There is no factor"<<endl;
        return;;
    }
    LinkWarehouse* temp=top->prev;
    top=temp;
}
void Printall(LinkWarehouse* top) {
    LinkWarehouse* temp=top;
    while(temp->prev!=nullptr) {
        cout<<temp->value<<"\t";
        temp=temp->prev;
    }
    if(top->prev==nullptr)
        cout<<"there is no factor";
    cout<<endl;
}
void clearLink(LinkWarehouse*& top) {
    while(top->prev!=nullptr) {
        top=top->prev;
    }
}
void destoryLink(LinkWarehouse*& top) {
    LinkWarehouse* current=top;
    while(top->prev!=nullptr) {
        top=top->prev;
        delete current;
        current=top;
    }
    delete top;
    top=nullptr;
}

int main() {
    // Warehousesqrt* obj=new Warehousesqrt;
    // obj->initWare();
    // bool result=obj->isEmpty();
    // cout<<result<<endl;
    // obj->Push(1);
    // obj->Push(2);
    // obj->Push(3);
    // obj->Push(4);
    // obj->Push(5);
    // obj->Push(6);
    // obj->Push(7);
    // obj->Pop();
    // cout<<obj->getLength()<<endl;
    // cout<<obj->getTop()<<endl;
    // obj->clearStack();
    // cout<<obj->isEmpty()<<endl;
    // obj->Printall();
    //以上代码实现了顺序栈基本操作的检测
    //以下代码实现链栈基本操作的检测
    LinkWarehouse* top;
    initLink(top);
    cout<<top<<endl;
    cout<<top->value<<"\t"<<top->prev<<endl;     //初始换函数是没问题的
     PushLink(top,1);
    cout<<top<<"\t"<<endl;
    PushLink(top,2);
    PushLink(top,3);
    PushLink(top,4);
    PushLink(top,5);
    PopLink(top);
    Printall(top);
    clearLink(top);
    Printall(top);
    destoryLink(top);
    cout<<top;

}
