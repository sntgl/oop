#include <iostream>
#include "list.h"
//#include <node>
//#include "error.h"
#include "node.h"
#include "iterator.h"

//конст итератор должен возвращать объект const
typedef struct
{
    int a;
    float b;
} custom_struct;

std::ostream &b(std::ostream &os)
{
    return os << "\e[1m";
}

std::ostream &nb(std::ostream &os)
{
    return os << "\e[0m";
}

bool int_cmp_bool(const int &n1, const int &n2)
{
    return n1 == n2;
}

int int_cmp_int(const int &n1, const int &n2)
{
    return n1 - n2;
}

bool custom_struct_cmp(const custom_struct &n1, const custom_struct &n2)
{
    return n1.a == n2.a and n1.b == n2.b;
}

void run_tests()
{

    std::cout << b << "Constructors test:" << nb << std::endl;
    {
        List<int> list1;
        std::cout << "\tEmpty <int> passed" << std::endl;
        List<custom_struct> list2;
        std::cout << "\tEmpty <custom structure> passed" << std::endl;
        List<int> list3 = {};
        std::cout << "\tEmpty initializer list passed" << std::endl;
        List<int> list4(list1);
        std::cout << "\tCopy of empty <int> passed" << std::endl;
        int arr[] = {15, 9, 2, 7, 8};
        List<int> list5(arr, 5);
        std::cout << "\tArray+size passed: " << list5 << std::endl;
        List<int> list6(list5);
        std::cout << "\tCopy of previous passed: " << list6 << std::endl;
        List<int> list7 = {1, 2, 3, 4, 123};
        std::cout << "\tInitializer list passed: " << list7 << std::endl;
    }
    std::cout << b << "Virtual methods test:" << nb << std::endl;
    {
        List<int> list1;
        std::cout << "\tList " << list1 << " is_empty() = " << list1.is_empty() << std::endl;
        list1.add(3);
        std::cout << "\tAfter add to previous list " << list1 << " is_empty() = " << list1.is_empty() << std::endl;
        list1.pop();
        std::cout << "\tAfter pop from previous list " << list1 << " is_empty() = " << list1.is_empty() << std::endl;
        List<int> list2 = {1, 2, 3};
        std::cout << "\tList " << list2 << " is_empty() = " << list2.is_empty() << std::endl;
        list2.clear();
        std::cout << "\t\tclear() -> " << list2 << std::endl;
    }
    std::cout << b << "Operators test:" << nb << std::endl;
    {
        List<int> list1 = {1, 2, 3}, list2(list1);
        std::cout << "\t" << list1 << " == " << list2 << " (copy) - ";
        if (list1 == list2)
            std::cout << "true";
        else
            std::cout << "false";
        std::cout << std::endl;

        List<int> list3 = {1, 2, 5}, list4 = {1, 2, 5};
        std::cout << "\t" << list3 << " == " << list4 << " (not copy) - ";
        if (list3 == list4)
            std::cout << "true";
        else
            std::cout << "false";
        std::cout << std::endl;

        std::cout << "\t" << list1 << " == " << list3 << " - ";
        if (list1 == list3)
            std::cout << "true";
        else
            std::cout << "false";
        std::cout << std::endl;

        List<int> list5;
        std::cout << "\tList " << list5 << ", bool() - " << bool(list5) << std::endl;
        list5.add(5);
        list5.add(100);
        std::cout << "\tList " << list5 << ", bool() - " << bool(list5) << std::endl;

        List<int> list6 = {1, 2, 3}, list7 = {100, 200, 300};
        List<int> list8;
        std::cout << "\t" << list6 << " + " << list7 << " = " << list6 + list7 << std::endl;
        std::cout << "\t" << list6 << " + " << 4 << " = " << list6 + 4 << std::endl;
        std::cout << "\tList " << list6 << ".\n\tList += " << list7 << std::endl;
        list6 += list7;
        std::cout << "\tList " << list6 << ".\n\tList += " << 900 << std::endl;
        list6 += 900;
        std::cout << "\tList " << list6 << std::endl;
        list8 = list6;
        std::cout << "\tList1 = List. List1 " << list8 << std::endl;

    }
    std::cout << std::endl;
    std::cout << b << "Other methods test:" << nb << std::endl;
    {

        List<custom_struct> list1 = {{.a = 3, .b = 3.5},
                                     {.a = 10, .b = 5.5}};
        List<custom_struct> list2 = {{.a = 3, .b = 3.5},
                                     {.a = 10, .b = 5.5}};
        List<custom_struct> list3 = {{.a = 3, .b = 3.5},
                                     {.a = 10, .b = 5.501}};
        std::cout << "\tMethod equals with specified comparator (might be used for custom structures):" << std::endl;
        List<int> list4 = {1, 2, 5, 8, 9, 11};
        std::cout << "\tFor .. each iteration: ";
        for (auto elem: list4)
            std::cout << elem << " ";
        std::cout << std::endl;
    }
    {
        int arr[] = {5, 4, 12, 2, 1};
        List<int> list3(arr, 5);
        try {
            std::cout << "\t" << list3;
        } catch (std::exception &e) {
            std::cout << e.what();
        }
        if (list3) {
            std::cout << " valid";
        } else
            std::cout << " not valid";
        std::cout << std::endl;
        List<int> list4(list3);
        try {
            std::cout << "\t" << list4;
        } catch (std::exception &e) {
            std::cout << e.what();
        }


        List<int> list5 = {10, 222, 3, 4, 5, 6, 8, 12};
        std::cout << "\t" << list5;
        std::cout << ++list5.begin() << std::endl;
        List<int> list6 = {10, 222, 3, 4, 5, 6, 9, 12};
        std::cout << "\t" << list5 << " and " << list6 << " is ";
        if (list5 == list6)
            std::cout << "equal";
        else
            std::cout << "not equal";
        std::cout << "(" << std::endl;
        List<int> list7(list5);
        std::cout << "\t" << list5 << " and " << list7 << " is ";
        if (list5 == list7)
            std::cout << "equal";
        else
            std::cout << "not equal";
        std::cout << std::endl;

        std::cout << "\tPop test: ";
        {
            List<int> list8 = {1, 2, 3};
            std::cout << "\t" << list8;
            std::cout << ", pop= " << list8.pop() << ", ";
            std::cout << list8;
            std::cout << ", pop= " << list8.pop() << ", ";
            std::cout << list8;
            std::cout << ", pop= " << list8.pop() << ", ";
            std::cout << list8;
            try {
                std::cout << ", empty pop:" << std::endl << list8.pop() << std::endl;
            } catch (BaseError &e) {
                std::cout << e.what();
            }
        }
    }
    std::cout << b << "Destructor of everything previous was passed" << std::endl;
    std::cout << "If you can see this, everything was passed!" << nb << std::endl;
}


int main()
{
    run_tests();
    return 0;
}
