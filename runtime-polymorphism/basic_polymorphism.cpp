#include <iostream>
#include <memory>
#include <string>
#include <vector>

// virtual base class
class object_t {
public:
    virtual ~object_t() {};
    virtual void write(std::ostream& out, size_t pos) = 0;
};

// container of shared ptr to base class objects
using document_t = std::vector<std::shared_ptr<object_t>>;

void write(const document_t& doc, std::ostream& out, size_t pos)
{
    out << std::string(pos, ' ') << "<document>\n";
    for (const auto& item: doc)
    {
        item->write(out, pos + 2);
    }
    out << std::string(pos, ' ') << "<document>\n";
}

// client
class word : public object_t
{
    void write(std::ostream& out, size_t pos) override
    {
        static int i = 0;
        out << std::string(pos, ' ') << "word" << ++i << '\n';
    }
};

int main()
{
    document_t doc;
    doc.reserve(5);

    // problem here: 1. word() is constructed on heap 2. it's emplaced into vector
    // if 2. fails, memory leaks -> avoid use raw new or delete
    doc.emplace_back(new word());

    // -> use make_shared instead
    doc.emplace_back(std::make_shared<word>());
    doc.emplace_back(std::make_shared<word>());
    doc.emplace_back(std::make_shared<word>());
    doc.emplace_back(std::make_shared<word>());

    write(doc, std::cout, 0);
}