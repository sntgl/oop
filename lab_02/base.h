#pragma once

class Base
{
public:
    virtual ~Base() = default;
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;

private:
    size_t size;
};