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

        virtual void registerInputs() {};

        std::vector<std::string> getInputs() const;
        void setValue(std::string input, vec_t value);

        template <class T>
        T getValue(std::string input) const;

    protected:
        Receiver() = default;
        void registerInput(std::string input,
                           vec_t initialValue = {0});

    private:
        input_map_t mapInputs;
    };

    template <typename T> T
    Receiver::getValue(std::string input) const {
        using namespace std::literals::string_literals;

        const auto pair = mapInputs.find(input);
        if(pair == mapInputs.end())
            log(logging::warning,
                "Receiver::getValue: input "s + input + " not registered");

        return pair->second;
    }

    template <> float
    Receiver::getValue<float>(std::string input) const;

    extern template float
    Receiver::getValue<float>(std::string input) const;

}

#endif // ETUDES_RECEIVER
