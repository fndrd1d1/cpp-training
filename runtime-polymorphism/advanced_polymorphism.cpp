#include <iostream>
#include <string>
#include <vector>


void write(const int& obj, std::ostream& out, size_t pos)
{
    out << std::string(pos, ' ') << obj << "\n";
}

class object_t
{
public:
    object_t(const int& value) : _internal(value) {}

    friend void write(const object_t& obj, std::ostream& out, size_t pos)
    {
        write(obj._internal, out, pos);
    }
private:
    int _internal;
};

using document_t = std::vector<object_t>;

void write(const document_t& doc, std::ostream& out, size_t pos)
{
    out << std::string(pos, ' ') << "<document>\n";
    for (const auto& item: doc)
    {
        write(item, out, pos + 2);
    }
    out << std::string(pos, ' ') << "<document>\n";
}

int main()
{
    document_t doc;
    doc.reserve(5);

    doc.emplace_back(1);
    doc.emplace_back(2);
    doc.emplace_back(3);
    doc.emplace_back(4);
    doc.emplace_back(5);

    write(doc, std::cout, 0);
}