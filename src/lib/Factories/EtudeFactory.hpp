#ifndef ETUDES_ETUDEFACTORY
#define ETUDES_ETUDEFACTORY

#include <memory>

namespace etudes {

    class Etude;
    class Configuration;

    class EtudeFactory {
    public:
        static std::unique_ptr<Etude>
        makeEtude(std::string name, const Configuration &config);

    private:
        static std::unique_ptr<Etude>
        makeEtudeDefault(const Configuration &config);
    };

}

#endif // ETUDES_ETUDEFACTORY
