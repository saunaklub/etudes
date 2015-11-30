#ifndef _ETUDES_RECEIVER
#define _ETUDES_RECEIVER

#include <string>
#include <vector>
#include <map>

namespace etudes {
    class Receiver {
    public:
        typedef std::map<std::string, float> input_map_t;

        std::vector<std::string> getInputs() const;
        void setValue(std::string input, float value);
        float getValue(std::string input) const;

    protected:
        Receiver() = default;
        void registerInput(std::string input,
                           float initialValue = 0.0f);
        
    private:
        input_map_t mapInputs;
    };
}

#endif // _ETUDES_RECEIVER
