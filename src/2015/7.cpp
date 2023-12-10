#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

enum Operation {
    AND,
    OR,
    LSHIFT,
    RSHIFT,
    NOT,
    VALUE
};

template <class T>
struct Optional {
    T value;
    bool is_set;
};

std::unordered_map<std::string, Operation> operation_map = { 
    { "AND", Operation::AND },
    { "OR", Operation::OR },
    { "LSHIFT", Operation::LSHIFT },
    { "RSHIFT", Operation::RSHIFT },
    { "NOT", Operation::NOT },
    { "VALUE", Operation::VALUE }
};

struct Wire {
    Optional<int> value;
    Operation operation;
    size_t inputCount;
    std::vector<std::string> input;
    std::string name;
};

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

template <class T>
void set_optional_value(Optional<T>& optional, T value) {
    optional.value = value;
    optional.is_set = true;
}

bool can_use_value(std::string str, const std::unordered_map<std::string, Wire>& wires) {
    if (is_number(str)) return true;

    return wires.at(str).value.is_set;
}

int get_value(std::string str, const std::unordered_map<std::string, Wire>& wires) {
    if (is_number(str)) return atoi(str.c_str());

    return wires.at(str).value.value;
}

int
main (void)
{
    std::unordered_map<std::string, Wire> wires;

    // Read file and create structs
    std::fstream input_file("../input/7-input.txt");
    if (!input_file) throw std::invalid_argument("File doesn't exist");

    std::string buffer;
    while (getline(input_file, buffer)) {
        Wire wire;
        std::vector<std::string> words;

        std::stringstream buffer_stream(buffer);
        std::string word;
        
        // Get wire formula strings
        while (buffer_stream >> word) words.push_back(word);

        // Check if wire formula is a single value
        if (words.size() == 3) {
            wire.name = words[words.size() - 1];
            wire.operation = Operation::VALUE;
            wire.inputCount = 1;
            wire.input = { words[0] };
        }
        // Wire operation is "NOT"
        else if (operation_map.find(words[0]) != operation_map.end() && operation_map[words[0]] == Operation::NOT) {
            wire.name = words[words.size() - 1];
            wire.operation = Operation::NOT;
            wire.inputCount = 1;
            wire.input = { words[1] };
        } 
        // Wire requires two other wires
        else {
            wire.name = words[words.size() - 1];
            wire.operation = operation_map[words[1]];
            wire.inputCount = 2;
            wire.input = { words[0], words[2] };
        }

        wire.value = Optional<int>{ 0, false };
        wires[wire.name] = wire;

    }

    // Compute all values necessary for wire "a"
    std::stack<std::string> stack;
    stack.push("a");
    while(stack.size() != 0) {
        std::string wire_name = stack.top();
        stack.pop();
        auto wire = &wires[wire_name];

        // Process if the it's just a single value
        if (wire->operation == Operation::VALUE) {
            if (can_use_value(wire->input[0], wires)) {
                set_optional_value(wire->value, get_value(wire->input[0], wires));
            } else {
                // Push back current wire for processing
                stack.push(wire->name);
                stack.push(wire->input[0]);
            }
        } else if (wire->operation == Operation::NOT) {
            if (can_use_value(wire->input[0], wires)) {
                set_optional_value(wire->value, ~get_value(wire->input[0], wires));
            } else {
                // Push back current wire for processing
                stack.push(wire->name);
                stack.push(wire->input[0]);
            }
        } 
        // Operations that require two values
        else {
            switch(wire->operation) {
                case Operation::AND:
                {
                    // Check both values to see if they're present, if not, add 
                    // current wire back to stack then add each input wire as needed to the stack
                    auto wire1 = wire->input[0];
                    auto wire2 = wire->input[1];
                    if (can_use_value(wire1, wires) && can_use_value(wire2, wires)) {
                        set_optional_value(wire->value, get_value(wire1, wires) & get_value(wire2, wires));
                    } else {
                        stack.push(wire->name);
                        if (!can_use_value(wire1, wires)) stack.push(wire1);
                        if (!can_use_value(wire2, wires)) stack.push(wire2);
                    }
                    break;
                }
                case Operation::OR:
                {
                    // Check both values to see if they're present, if not, add 
                    // current wire back to stack then add each input wire as needed to the stack
                    auto wire1 = wire->input[0];
                    auto wire2 = wire->input[1];
                    if (can_use_value(wire1, wires) && can_use_value(wire2, wires)) {
                        set_optional_value(wire->value, get_value(wire1, wires) | get_value(wire2, wires));
                    } else {
                        stack.push(wire->name);
                        if (!can_use_value(wire1, wires)) stack.push(wire1);
                        if (!can_use_value(wire2, wires)) stack.push(wire2);
                    }
                    break;
                }
                case Operation::LSHIFT:
                {
                    // Check both values to see if they're present, if not, add 
                    // current wire back to stack then add other wire to stack
                    auto wire1 = wire->input[0];
                    auto wire2 = wire->input[1];
                    if (can_use_value(wire1, wires) && can_use_value(wire2, wires)) {
                        set_optional_value(wire->value, get_value(wire1, wires) << get_value(wire2, wires));
                    } else {
                        stack.push(wire->name);
                        if (!can_use_value(wire1, wires)) stack.push(wire1);
                        if (!can_use_value(wire2, wires)) stack.push(wire2);
                    }
                    break;
                }
                case Operation::RSHIFT:
                {
                    // Check both values to see if they're present, if not, add 
                    // current wire back to stack then add other wire to stack
                    auto wire1 = wire->input[0];
                    auto wire2 = wire->input[1];
                    if (can_use_value(wire1, wires) && can_use_value(wire2, wires)) {
                        set_optional_value(wire->value, get_value(wire1, wires) >> get_value(wire2, wires));
                    } else {
                        stack.push(wire->name);
                        if (!can_use_value(wire1, wires)) stack.push(wire1);
                        if (!can_use_value(wire2, wires)) stack.push(wire2);
                    }
                    break;
                }
                default:
                {
                    throw new std::invalid_argument("Invalid operation that requires two wires");
                }
            }
        }

    }

    // Return value of a
    std::cout << wires["a"].name << " has value of " << wires["a"].value.value << std::endl;

    return 0;
}
