

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <stdexcept>

using namespace std;

namespace test_namespace
{

class exception1 : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "an exception1.";
    }
};

class exception2 : public exception1
{
public:
    virtual const char* what() const throw()
    {
        return "an exception2.";
    }
};

const unsigned BUFFER_MAX_LEN = 64;

void read_file_e(FILE* f, char* buf, size_t buf_size)
{
    if (NULL == f)
        throw std::logic_error("f is NULL.");
    // ... read file ....
}

bool read_file_r(FILE* f, char* buf, size_t buf_size)
{
    if (NULL == f)
        return false;
    // ... read file ....
    return true;
}

class read_info_class
{
public:
    enum { ITEM_COUNT = 30, INFO_MAX_LEN = BUFFER_MAX_LEN };
public:
    read_info_class()
        : _file(0) {}

    read_info_class(FILE* file)
        : _file(file) {}
    ~read_info_class()
    {
        if (_file)
            fclose(_file);
    }

    void set_file (FILE* new_f)
    {
        if (_file)
            fclose(_file);
        _file = new_f;
    }
    void read_info_for_item1_e()
    {
        //assert (_file);
        string info;
        info.resize(INFO_MAX_LEN);
        read_file_e(_file, const_cast<char*>(info.c_str()), info.size());
        _info_items.push_back(info);
        read_file_e(_file, const_cast<char*>(info.c_str()), info.size());
        _info_items.push_back(info);
        // ... if read more items than 30...
    }

    void read_info_for_item2_e()
    {
        /* ... */
    }
    void read_info_for_item3_e()
    {
        /* ... */
    }
    void read_info_for_item4_e()
    {
        /* ... */
    }
    void read_info_for_item5_e()
    {
        /* ... */
    }
    // ... more ...

    bool read_info_for_item1_r()
    {
        //assert (_file);
        string info;
        info.resize(INFO_MAX_LEN);
        if (!read_file_r(_file, const_cast<char*>(info.c_str()), info.size()))
            return false;
        _info_items.push_back(info);
        if (!read_file_r(_file, const_cast<char*>(info.c_str()), info.size()))
            return false;
        _info_items.push_back(info);
        // ... if read more items than 30...

        return true;
    }

    bool read_info_for_item2_r()
    {
        /* ... */  return true;
    }
    bool read_info_for_item3_r()
    {
        /* ... */  return true;
    }
    bool read_info_for_item4_r()
    {
        /* ... */  return true;
    }
    bool read_info_for_item5_r()
    {
        /* ... */  return true;
    }
    // ... more ...

private:
    FILE* _file;
    vector<string> _info_items;
    // more other var...
};

void do_read_func_e()
{
    // do something ...
    FILE* file = NULL;
    // open file and ...
    vector<char> buf(BUFFER_MAX_LEN);
    read_file_e(file, &buf[0], buf.size());
    // handle buf's data ...
    read_file_e(file, &buf[0], buf.size());
    // more ...
    read_info_class read_info;
    // initialize read_info and ...
    read_info.read_info_for_item1_e();
    read_info.read_info_for_item2_e();
    read_info.read_info_for_item3_e();
    read_info.read_info_for_item4_e();
    read_info.read_info_for_item5_e();
    // more read_info_for_item5_e ...
    return;
}

bool do_read_func_r()
{
    // do something ...
    FILE* file = NULL;
    // open file and ...
    vector<char> buf(BUFFER_MAX_LEN);
    if (!read_file_r(file, &buf[0], buf.size()))
        return false;
    // handle buf's data ...
    if (!read_file_r(file, &buf[0], buf.size()))
        return false;
    // more ...
    read_info_class read_info;
    // initialize read_info and ...
    if (!read_info.read_info_for_item1_r() ||
            !read_info.read_info_for_item2_r() ||
            !read_info.read_info_for_item3_r() ||
            !read_info.read_info_for_item4_r() ||
            !read_info.read_info_for_item5_r() ) /// || more read_info_for_item*_r ...
        return false;
    // ...
    return true;
}
void test_read_func_e()
{
    // ...
    try
    {
        do_read_func_e();
    }
    catch (std::exception& e)
    {
        std::cerr << " catch error:" << e.what() << endl;
    }
    // ... more ...
}

void test_read_func_r()
{
    if (!do_read_func_r())
    {
        std::cerr << " occur error from do_read_func_r." << endl;
    }
}
} /// namespace test_namespace

void test_exception_list()
{
    using namespace test_namespace;
    /// ˵����catch �쳣�б�˳��Ӱ���������ץȡ�쳣������������쳣��catch��֧��
    /// ���飺���쳣catch�б��쳣���ࣨ�����ࣩ�Ĵ������������쳣���ദ��֮ǰ��
    /// ���Υ���ù����쳣���ദ�������쳣����֮ǰ����Щ����������������ʾ���磺
    //    warning: exception of type 'derived_class' will be caught|
    //    warning:    by earlier handler for 'base_clase'|

    /// ��������˵�����£�
    /// 1-1.
    try
    {
        std::cout << " throw a exception2.\n";
        throw exception2();
    }
    catch (const exception1& e)
    {
        std::cout << " catch (const exception1& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
    catch (const exception2& e)
    {
        std::cout << " catch (const exception2& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }

    /// 1-2.
    try
    {
        std::cout << " throw a exception2.\n";
        throw exception2();
    }
    catch (const exception2& e)
    {
        std::cout << " catch (const exception2& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
    catch (const exception1& e)
    {
        std::cout << " catch (const exception1& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
    /// ---
    /// 2-1.
    try
    {
        std::cout << " throw a logic_error.\n";
        throw std::logic_error("a logic_error");
    }
    catch (const std::logic_error& e)
    {
        std::cout << " catch (const logic_error& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << " catch (const exception& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }

    /// 2-2.
    try
    {
        std::cout << " throw a logic_error.\n";
        throw std::logic_error("a logic_error");
    }
    catch (const std::exception& e)
    {
        std::cout << " catch (const exception& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
    catch (const std::logic_error& e)
    {
        std::cout << " catch (const logic_error& e).\n";
        std::cout << " catch "<< e.what() << "\n";
    }
/// Output��
// throw a exception2.
// catch (const exception1& e).
// catch an exception2.
// throw a exception2.
// catch (const exception2& e).
// catch an exception2.
// throw a logic_error.
// catch (const logic_error& e).
// catch a logic_error
// throw a logic_error.
// catch (const exception& e).
// catch a logic_error
}

int main()
{
    {
    using namespace test_namespace;
    test_read_func_e();
    test_read_func_r();
    test_exception_list();
    }

    cout << " Hello world!" << endl;
    return 0;
}

/**
//��΢�ܽ�һ�£�try-throw-catch�ṹ�쳣������ƣ����Ƶĵط���
// 1. ���ڼ��д���ͬ���쳣�����������Բ�ͬ���ࣩ�߼���ε��쳣�������������ò�Ҫ��ģ�鴦���쳣��
     // ��Բ�ͬ���ࣩ�߼���ε��쳣��������ʹ���쳣������ƣ�����Ҫ�ڴ����쳣�����ֵط��ط�һ��㷵�ش��������ֱ���õ�������д����ʱ������׸�Ƚϴ�

// 2. ����쳣��������������չ�ԱȽϺá�
     // �����ӻ����һ���쳣�Ĵ���������漰�����߼����޸ıȽ�С��ֻҪȡ�������throw��catch�����Ӧ�����

// 3. �����ִ��������throw��������ֹ�������߼���ִ�У�ֱ���ҵ���Ӧ��catch�����������������
     // �����ŵ�Ҳ��ȱ�㡣

// 4. ��ȥ�ֶ���д�ܶ��if-return�߼�����������Ӱ������߼������������ۣ����������Щ���д�����ĳ���Ա��

// 5. ���飺�ڲ�Ӱ������������ܵ�����£��ɿ���ʹ���쳣�������������ڸ��ӵĴ����쳣����������ġ�
     // Ҳ����˵�����ӵĴ������߼������ǳ�����Ҫ�߼�����ʹʹ����C++�쳣����Ҳ��Ӱ�������������ܡ�
// ***/
