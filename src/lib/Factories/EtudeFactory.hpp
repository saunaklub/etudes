#ifndef ETUDES_ETUDEFACTORY
#define ETUDES_ETUDEFACTORY

#include <memory>

#include <yaml-cpp/yaml.h>

namespace etudes {

    class Etude;

    class EtudeFactory {
    public:
        static std::unique_ptr<Etude>
        makeEtude(const YAML::Node &config);

    private:
        static std::unique_ptr<Etude>
        makeEtudeDefault(const YAML::Node &config);
    };

}

#endif // ETUDES_ETUDEFACTORY
