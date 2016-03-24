#ifndef ETUDES_RECEIVER
#define ETUDES_RECEIVER

#include <string>
#include <vector>
#include <map>

#include <Utility/Logging.hpp>

namespace etudes {

    class Receiver {
    public:
        typedef std::vector<float> vec_t;
        typedef std::map<std::string, vec_t> input_map_t;

        virtual void registerInputs() = 0;

        std::vector<std::string> getInputs() const;
        void setValue(std::string input, vec_t value);

        template <class T>
        T getValue(std::string input) const;

    protected:
        Receiver() = default;
        void registerInput(std::string input,
                           vec_t initialValue = {0});

    private:
        const vec_t &getInput(std::string input) const;

        input_map_t mapInputs;
    };

}

#endif // ETUDES_RECEIVER
