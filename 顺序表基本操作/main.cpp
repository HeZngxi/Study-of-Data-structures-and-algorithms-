#include <iostream>

#define MAXNUM 100

class Student {
public:
    std::string name;                        //这里我把属性设置为了public，这实际上是不好的，但我为了方便书写，简化一下所以没有私有化
    int age;
    Student(){};
    Student(std::string na,int ag):name(na),age(ag){};
};

class  SList {

private:
    Student* students;
    int length;

public:
    SList() {
        students=nullptr;
        length=0;
    }                           //构造函数，初始化指针为空，length=0，

    ~SList() {
        if(students!=nullptr){delete[] students;}               //先判断，再清除指针
        length =0;
    }

    void initList() {
        students = new Student[MAXNUM]; // 分配数组内存
        if (students == nullptr) {
            std::cerr<<"students[] went wrong"<<std::endl;
            return;
        }
        length = 0;
    }

    int getLength() {
        return length;
    }

    void addStu(const Student& stu) {
        if(length<MAXNUM) {
            students[length]=stu;
            length++;
        }else {
            std::cerr<<"List is full"<<std::endl;
        }
    }

    void deleteStuBynumber(int num) {
        //这里实现删除元素其实不用真的删除，只需要将后面的元素全部向前移动一位，并减小length，那么下次添加元素时就能够实现覆盖从而删除
        if(num>=1 && num<length) {
            for (int i=num;i<length;i++) {
                students[i-1]=students[i];
            }
            length--;
        }else if(num==length) {
            length--;
        }else {
            std::cerr<<"Invalid number"<<std::endl;
        }

    }

    void deleteStuByname(std::string name) {
        int number=0;
        for (int i=0;i<length;i++) {
            if(students[i].name==name)            //c++的string中重载了==，能够直接使用==比较两个字符串
                number=i+1;
        }
        if(number==0) {
            std::cout<<"Wrong name"<<std::endl;
        }else {
            if(number!=length){
                for (int i=number;i<length;i++) {
                    students[i-1]=students[i];
                }
                length--;
            }else {
                length--;
            }
        }
    }

    void printAll() {
        if(students==nullptr) {
            std::cout<<"array has been destoried"<<std::endl;
        }
        else if(length==0 && students!=nullptr) {
            std::cout<<"there's no factor"<<std::endl;
        }
        for (int i=0;i<length;i++) {    //这里的students声明的是一个指针，所以不能用for-each来遍历
            std::cout<<"number:"<<i+1<<"\tname:"<<students[i].name<<"\t\tage:"<<students[i].age<<std::endl;
        }

    }

    void insertStu(Student stu,int number) {
        if(number<1 || number>length+1) {
            std::cout<<"Invalid position to insert"<<std::endl;
            return;;
        }
        if(number==length+1) {
            students[length]=stu;
            length++;
        }else {
            for(int i=length;i>number-1;i--) {
                students[i]=students[i-1];
            }
            students[number-1]=stu;
            length++;
        }
    }

    void destoryList() {
        if (students!=nullptr) {
            delete[] students;
            students=nullptr;
        }
        length=0;
    }

    void clearList() {
        length=0;
    }

    bool isEmpty() {
        if(length==0) {
            return true;
        }else
            return false;
    }

    int locatStu(Student stu) {
        for (int i=0;i<length;i++) {
            if(stu.name==students[i].name && stu.age==students[i].age)
                return i+1;
            else
                return 0;
        }
    }

    void getStu(int number,Student& stu) {
        if(number<1 || number>length) {
            std::cout<<"number is invalid"<<std::endl;
            return;
        }else {
            stu.name=students[number-1].name;
            stu.age=students[number-1].age;
        }
    }
};


int main() {
    SList list;
    list.initList();
    list.addStu(Student("Alice",19));
    list.addStu(Student("Ben",20));
    list.insertStu(Student("King",19),2);
    list.insertStu(Student("Ken",19),1);
    list.insertStu(Student("Lucy",20),4);
    list.printAll();
    std::cout<<list.getLength()<<std::endl;
    //list.destoryList();
    //list.deleteStuBynumber(1);
    //list.deleteStuByname("Alice");
    //list.clearList();
    //list.printAll();
    Student student;
    list.getStu(3,student);
    std::cout<<student.name<<"\t\t"<<student.age<<std::endl;
    return 0;
}
