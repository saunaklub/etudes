#ifndef ETUDES_RECEIVER
#define ETUDES_RECEIVER

#include <string>
#include <vector>
#include <map>
#include <mutex>

#include <Utility/Logging.hpp>

namespace etudes {

    class Receiver {
    public:
        typedef std::vector<float> vec_float_t;
        typedef std::vector<std::string> vec_string_t;

        typedef std::map<std::string, vec_float_t> input_map_float_t;
        typedef std::map<std::string, vec_string_t> input_map_string_t;

        virtual void registerInputs() = 0;

        std::vector<std::string> getInputs() const;

        template <typename T>
        void setValue(std::string input, const T &value);

        template <typename T>
        T getValue(std::string input);

    protected:
        Receiver() = default;

        void registerInput(std::string input,
                           vec_float_t initialValue = {0});
        void registerInput(std::string input,
                           vec_string_t initialValue = {""});

    private:
        template <class T>
        T getInput(std::string input);

        input_map_float_t mapInputsFloat;
        input_map_string_t mapInputsString;

        std::mutex inputLock;
    };

}

#endif // ETUDES_RECEIVER
