#include <iostream>


class Student {
public:
    int age;
    std::string name;
    Student(std::string na,int ag):age(ag),name(na){};
    Student(){};
    bool equals(Student stu) {
        if(age==stu.age && name==stu.name)
            return true;
        else
            return false;
    }
};

class Node {
public:
    Student student;
    Node* next;
    Node(Student stu,Node* ne=nullptr):student(stu),next(ne){};
    Node(){};
    ~Node() {}
};

void initNodeList(Node*& header);            //初始化一个链表，参入的参数是一个Node的指针，在这个函数中创建头结点，并让头指针指向这个头结点
void addNodetoHead(Node*& header,Student& student);
                                    //在链表头部增加一个结点，传入的参数是一个链表的头指针以及添加的结点的数据段，在函数中要利用new创建
                                    //node的对象才能保证变量是分配在堆上的，那么在删除结点的时候也要delete这个对象避免内存泄漏
void addNodetoLast(Node*& header,Student& student);  //这里使用引用传参能够减小空间占用，提高效率
Student deleteNodebyNumber(Node*& header,int location);   //删除指定位置的结点，传入的参数有链表头指针，还有结点位置location，这里返回data字段
int deleteNodebyData(Node*& header,Student stu);         //根据传入的数据字段来删除，这里返回位置
void insertNode(Node*& header,Student stu,int location);              //向指定位置插入node结点，传入的参数有链表指针，node的data字段，还有插入位置number
Student getNodedata();          //获取指定位置的data字段,功能类似，比较简单，不写了
int getLocation();              //传入参数为链表指针以及data字段，返回对应数据在链表中的位置，若不存在就返回-1   //也比较简单
void printAll(Node*& header);                //打印链表中所有的所有结点中的data数据以及对应的位置
void unionNodeList(Node*& header1,Node*& header2);      //单纯首尾合并两个链表,默认header1作为合并后链表的表头
void unionSqrt(Node*& header1,Node*& header2,Node*& header);         //合并两个数组并按照默认的顺序排列,默认是以header1为最终的链表
                                                    //这个函数与下一个基本功能一致，实现这个就行
Node* generateNewList();        //将两个链表按照默认的顺序链接成新的链表，传入的参数有新链表的指针，两个合并链表的指针
void sqrt(Node*& header);        //将链表中的元素按照一定规则排序

int main() {
    //这里创建头指针并实现链表的初始化
    Node* header=nullptr;
    Node* header2=nullptr;
    Node* header3=nullptr;
    initNodeList(header);
    initNodeList(header2);
    initNodeList(header3);

    //这里手动创建一些Student对象
    Student student1=Student("Ken",19);
    Student student2=Student("King",20);
    Student student3=Student("Ben",18);
    Student student4=Student("Alice",21);
    Student student5=Student("Kara",18);
    Student student6=Student("Sora",20);
    Student student7=Student("Wang",22);
    Student student8=Student("Hezx",24);
    Student student9=Student("Libz",25);
    Student student10=Student("Zhao",23);

    //这个方法实现从链表头部添加新的结点
    addNodetoHead(header,student1);
    addNodetoHead(header,student2);

    //这个函数验证在链表尾部添加结点
    addNodetoLast(header,student3);
    addNodetoLast(header,student4);
    addNodetoHead(header2,student8);
    addNodetoLast(header2,student9);
    addNodetoHead(header2,student10);

    //这个函数尝试删除指定位置的结点
    Student stu=deleteNodebyNumber(header,2);
    std::cout<<"被删除人员的信息：："<<"name:"<<stu.name<<"\t\tage:"<<stu.age<<std::endl;

    //这个函数尝试删除指定data字段的结点并返回该Node在链表中的位置
    int location=deleteNodebyData(header,student2);
    std::cout<<"删除元素在链表中的原位置："<<location<<std::endl;

    //这个函数实现向链表中插入Node结点
    insertNode(header,student5,1);
    insertNode(header,student6,3);
    insertNode(header,student7,5);

    printAll(header);
    std::cout<<std::endl;
    printAll(header2);

    // unionNodeList(header,header2);
    // std::cout<<"以下是合并后的列表"<<std::endl;
    // printAll(header);                                     //合并后的链表已经delete了一个，所以这两个函数只能存其一

    unionSqrt(header,header2,header3);
    std::cout<<std::endl<<"以下是排序后的链表"<<std::endl;
    printAll(header3);

}
void printAll(Node*& header) {
    Node* p=header->next;
    int i=1;
    while (p!=nullptr) {
        std::cout<<"number:"<<i<<"\t\tname:"<<p->student.name<<"\t\tage:"<<p->student.age<<std::endl;
        p=p->next;
        i++;
    }
}
void initNodeList(Node*& header) {
    header=new Node();
    header->next=nullptr;
    if(!header) {
        std::cout<<"Wrong"<<std::endl;
    }
}
void addNodetoHead(Node*& header,Student& student) {
    Node* ele=new Node(student);
    ele->next=header->next;
    header->next=ele;
}
void addNodetoLast(Node*& header,Student& student) {
    Node* p=header->next;
    if(!p) {
        header->next=new Node(student);               //如果此链表中此时还没有元素的话就需要单独考虑
    }else {
        while(p->next!=nullptr){p=p->next;}
        p->next=new Node(student);
    }
}
Student deleteNodebyNumber(Node*& header,int location) {
    // Node* p=header;
    // int i=1;
    // while(location!=i && p!=nullptr) {
    //     p=p->next;
    //     i++;
    // }
    // if(location==i) {
    //     const Node* q=p->next;
    //     p->next=p->next->next;
    //     return q->student;
    // }else {
    //     std::cout<<"Location is invalid"<<std::endl;
    //     return header->student;
    // }

    Node* p = header->next; // 从头结点的下一个节点开始遍历
    Node* prev = header; // 用于保存前一个节点，以便删除节点
    int i = 0;

    while (p != nullptr && i < location) {
        prev = p;
        p = p->next;
        ++i;
    }

    if (p == nullptr || i != location) {
        std::cerr << "Location is invalid" << std::endl;
        return Student(); // 返回一个默认构造的 Student 对象
    }

    // 删除节点
    Student stu = p->student;
    prev->next = p->next;
    delete p; // 释放节点内存    prev是指向链表非重复的元素的，如果释放了prev那么就会出现有元素没有指向，出现无法访问的情况
    return stu;
}
int deleteNodebyData(Node*& header,Student stu){
    Node* p=header->next;
    Node* prev=header;
    int i=1;
    while(p!=nullptr && p->student.equals(stu)!=true) {
        prev=p;
        p=p->next;
        i++;
    }
    if(p==nullptr) {
        std::cout<<"Student is invalid"<<std::endl;
        return 0;
    }else {
        //删除结点的时候就涉及到了delete指针，这里也是删除p，因为要删除的元素就是用p指向的
        prev->next=p->next;
        delete p;
        p=nullptr;
        return i;
    }
}
void insertNode(Node*& header,Student stu,int location) {
    int i=1;
    Node* p=header;
    //三种情况：1.插在了首元素位置，直接调用方法即可   2.插入在了末尾位置直接调用方法   3.插入在了中间
    if(location==1) {
        addNodetoHead(header,stu);
        return ;
    }
    Node* ele=new Node(stu);
    while (i<location && p->next!=nullptr) {    //这里的代码用于将p指向要插入位置的前一个Node节点元素
        p=p->next;
        i++;
    }
    if(i<location && p->next==nullptr) {          //判断是否超出链表长度
        std::cout<<"Location is invalid"<<std::endl;
    }else {                                       //插入位置在中间和末尾可以用相同的代码实现
        ele->next=p->next;
        p->next=ele;
    }
}
void unionNodeList(Node*& header1,Node*& header2) {
    if(header1->next==nullptr || header1==nullptr) {
        header1=header2;
        return ;
    }
    Node* p=header1->next;
    while(p->next!=nullptr) {         //这里判断的的是p的next值是否为空
        p=p->next;
    }
    p->next=header2->next;            //链表中是有头指针和头结点的，这里应该将p.next赋值为header2中的第一个元素的地址，即header2.next
    delete header2;
    header2=nullptr;
}
void unionSqrt(Node*& header1,Node*& header2,Node*& header) {
    sqrt(header1);
    sqrt(header2);                      //先使用排序按年龄从小到大排序
    //我这里传入的链表就是从小到大排序的，所以不影响
    Node* p1=header1->next;
    Node* p2=header2->next;
    header=(header1!=nullptr)?header1:header2;    //将header设置为不为空的链表头指针
    Node* p=header;
    while (p1 && p2) {
        if(p1->student.age<=p2->student.age) {
            p->next=p1;
            p=p->next;
            p1=p1->next;
        }else {
            p->next=p2;
            p=p->next;
            p2=p2->next;
        }
    }
    p->next=(p1==nullptr)?p2:p1;

    if(header==header1) {
        delete header2;
        header2=nullptr;
    }else {
        delete header1;
        header1=nullptr;
    }
}
void sqrt(Node*& header) {
    //使用冒泡排序实现

}               //这里没有写实现