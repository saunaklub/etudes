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

        static std::unique_ptr<Element>
        makeLineElement(const YAML::Node &config);
    };
}

#endif // ETUDES_ELEMENTFACTORY
