#include <iostream>
#include <vector>
#include <string>

// dynamic strategy
class ListStrategy
{
public:
    virtual ~ListStrategy() {};
    virtual void openElement() {};
    virtual void bodyListItem(const std::string& item) {};
    virtual void closeElement() {};
};

class ListProcessor
{
public:
    ListProcessor(std::unique_ptr<ListStrategy> lStrategy)
    : strategy(std::move(lStrategy))
    {}

    void addListElements(const std::vector<std::string>& items)
    {
        strategy->openElement();

        for (const auto& item : items)
        {
            strategy->bodyListItem(item);
        }

        strategy->closeElement();
    }
private:
    std::unique_ptr<ListStrategy> strategy;
};

class MarkdownListStrategy
: public ListStrategy
{
public:
    void bodyListItem(const std::string& item) override
    {
        std::cout << " * " << item << '\n';
    }
};

class HtmlListStrategy
: public ListStrategy
{
public:
    void openElement() override
    {
        std::cout << "<ul>\n";
    }
    void closeElement() override
    {
        std::cout << "</ul>\n";
    }
    void bodyListItem(const std::string& item) override
    {
        std::cout << "<li>" << item << "</li>\n";
    }
};

// static strategy
template <typename LS>
class ListProcessorStatic
{
public:
    void addListElements(const std::vector<std::string>& items)
    {
        strategy.openElement();

        for (const auto &item : items)
        {
            strategy.bodyListItem(item);
        }

        strategy.closeElement();
    }
private:
    LS strategy;
};

int main()
{
    ListProcessor lMarkdown(std::make_unique<MarkdownListStrategy>());
    std::cout << "markdown\n";
    const std::vector<std::string> listElements = {"first", "second"};
    lMarkdown.addListElements(listElements);

    std::cout << "\nhtml\n";
    ListProcessor lHtml(std::make_unique<HtmlListStrategy>());
    lHtml.addListElements(listElements);

    ListProcessorStatic<MarkdownListStrategy> lMarkdownStatic;
    std::cout << "\nmarkdown static\n";
    lMarkdownStatic.addListElements(listElements);
}