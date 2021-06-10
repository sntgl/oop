#pragma once

#include <exception>
#include <string>

/* example:
throw Error(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
 */

class BaseError : std::exception
{
public:
    inline BaseError(std::string file_name, std::string class_name, std::string method_name, int line) noexcept
    {
        info = ":\n\tDate: ";
        info += __TIMESTAMP__;
        info += "\n\tFile: " + file_name + " in line " + std::to_string(line) + "\n" + \
               "\tClass: " + class_name + " in method " + method_name + "\n";
    }

    virtual ~BaseError() noexcept = default;

    virtual const char *what() const noexcept override
    {
        std::string std_message = "ERROR, " + pregenerate_title() + info;
        char *message = new char[1 + std_message.size()];
        std::strcpy(message, std_message.c_str());
        return message;
    };
protected:
    std::string info;
    std::string error_title = "Something wrong";
    inline virtual std::string pregenerate_title() const
    {
        return std::string(error_title);
    }
};

class MemoryError : public BaseError
{
public:
    MemoryError(std::string file_name, std::string class_name, std::string method_name, int line) :
        BaseError(file_name, class_name, method_name, line) {};
protected:
    inline std::string pregenerate_title() const override
    {
        return std::string(error_title);
    }
    std::string error_title = "Memory issues";
};

class PointerError : public BaseError
{
public:
    PointerError(std::string file_name, std::string class_name, std::string method_name, int line) :
    BaseError(file_name, class_name, method_name, line) {};
protected:
    inline std::string pregenerate_title() const override
    {
        return std::string(error_title);
    }
    std::string error_title = "Pointer is empty";
};

class EmptyError : public BaseError
{
public:
    EmptyError(std::string file_name, std::string class_name, std::string method_name, int line) :
            BaseError(file_name, class_name, method_name, line) {};
protected:
    inline std::string pregenerate_title() const override
    {
        return std::string(error_title);
    }
    std::string error_title = "List is empty";
};

class IndexError : public BaseError
{
public:
    IndexError(std::string file_name, std::string class_name, std::string method_name, int line) :
            BaseError(file_name, class_name, method_name, line) {};
protected:
    inline std::string pregenerate_title() const override
    {
        return std::string(error_title);
    }
    std::string error_title = "Index is not subscribable";
};

class IteratorError : public BaseError
{
public:
    IteratorError(std::string file_name, std::string class_name, std::string method_name, int line) :
            BaseError(file_name, class_name, method_name, line) {};
protected:
    inline std::string pregenerate_title() const override
    {
        return std::string(error_title);
    }
    std::string error_title = "Iterator does not belong this List";
};

class PointerExpired : public BaseError
{
public:
    PointerExpired(std::string file_name, std::string class_name, std::string method_name, int line) :
            BaseError(file_name, class_name, method_name, line) {};
protected:
    inline std::string pregenerate_title() const override
    {
        return std::string(error_title);
    }
    std::string error_title = "Iterator pointer was expired";
};