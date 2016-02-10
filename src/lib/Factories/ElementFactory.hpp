#ifndef ETUDES_ELEMENTFACTORY
#define ETUDES_ELEMENTFACTORY

#include <memory>
#include <map>
#include <string>

namespace YAML {
    class Node;
}

namespace etudes {
    class Element;

    class ElementFactory {
    public:
        static std::unique_ptr<Element>
        makeElement(const YAML::Node &config);

    private:
        typedef std::function<
        std::unique_ptr<Element>(const YAML::Node &)> creation_t;

        static std::map<std::string, creation_t> creationMap;

        template <typename T> static
        std::unique_ptr<Element>
        createElement(const YAML::Node &node) {
            std::unique_ptr<Element> product =
                std::make_unique<T>();
            return product;
        }

    };
}

#endif // ETUDES_ELEMENTFACTORY
