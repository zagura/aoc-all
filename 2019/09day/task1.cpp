/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11.12.2019 22:31:51
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cinttypes>
#include <sstream>
#include <functional>
#include <iterator>
using namespace std;

enum class AccessMode: uint8_t {
    kPositionMode = 0,
    kImmediateMode = 1,
    kRelativeMode = 2
};

enum class Opcode: uint8_t {
    kAdd            = 1,
    kMultiply       = 2,
    kLoad           = 3,
    kStore          = 4,
    kJumpIfTrue     = 5,
    kJumpIfFalse    = 6,
    kLessThan       = 7,
    kEquals         = 8,
    kAdjustRelative = 9,
    kHalt           = 99
};


using reg_type = long long int;

class Processor {
public:
    vector<reg_type> state;
    size_t relative_base;
    size_t ip; // instruction pointer
    bool done;
    reg_type access_resize(reg_type index);
    reg_type get_param(AccessMode mode, reg_type index);
    reg_type get_param_address(AccessMode mode, reg_type index);
    reg_type get_param_address2(AccessMode mode, reg_type index);
    void resize(reg_type index);
    void add(AccessMode modes[]);
    void multiply(AccessMode modes[]);
    void load(AccessMode modes[]);
    void store(AccessMode modes[]);
    void jump_if_true(AccessMode modes[]);
    void jump_if_false(AccessMode modes[]);
    void less_than(AccessMode modes[]);
    void equals(AccessMode modes[]);
    void adjust_relative(AccessMode modes[]);
    void halt(AccessMode modes[]);
};

void Processor::resize(reg_type index) {
    size_t new_size = static_cast<size_t>(index + 1);
    if (new_size > state.size()) {
        state.resize(new_size);
    }
}
reg_type Processor::access_resize(reg_type index) {
    resize(index);
    return state.at(index);
}


reg_type Processor::get_param(AccessMode mode, reg_type index) {
    reg_type param = access_resize(index);
    switch(mode) {
        case AccessMode::kImmediateMode:
            break;
        case AccessMode::kRelativeMode:
            param += relative_base;
            [[fallthrough]];
        case AccessMode::kPositionMode:
            param = access_resize(param);
    }
//    resize(param);
    return param;
}

reg_type Processor::get_param_address(AccessMode mode, reg_type index) {
    reg_type param = access_resize(index);
    if (AccessMode::kRelativeMode == mode) {
            param += relative_base;
    }
    resize(param);
    return param;
}

reg_type Processor::get_param_address2(AccessMode mode, reg_type index) {
    if (AccessMode::kRelativeMode == mode) {
            index += relative_base;
    }
    reg_type param = access_resize(index);
    resize(param);
    return param;
}

void Processor::add(AccessMode modes[]) {
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    reg_type result_addr = get_param_address(modes[2], ip + 1);
    reg_type result = param1 + param2;
    state.at(result_addr) = result;
    ip += 4;
}

void Processor::multiply(AccessMode modes[]) {
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    reg_type result_addr = get_param_address(modes[2], ip + 3);
    reg_type result = param1 * param2;
    state.at(result_addr) = result;
    ip += 4;
}

void Processor::load(AccessMode modes[])
{
    reg_type address = get_param_address2(modes[0], ip + 1);
    reg_type value = 0;
    cout << "Please give a value: ";
    cin >> value;
    state.at(address) = value;
    ip += 2;
}

void Processor::store(AccessMode modes[])
{
    reg_type printed_address = get_param(modes[0], ip + 1);
    cout << printed_address << " ";
    ip += 2;
}

void Processor::jump_if_true(AccessMode modes[])
{
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    if (param1 != 0) {
        ip = param2;
    } else {
        ip += 3;
    }
}

void Processor::jump_if_false(AccessMode modes[])
{
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    if (param1 == 0) {
        ip = param2;
    } else {
        ip += 3;
    }
}

void Processor::less_than(AccessMode modes[])
{
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    reg_type param3 = get_param_address(modes[2], ip + 3);
    state.at(param3) = (param1 < param2) ? 1 : 0;
    ip += 4;
}

void Processor::equals(AccessMode modes[])
{
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    reg_type param3 = get_param_address(modes[2], ip + 3);
    state.at(param3) = (param1 == param2) ? 1 : 0;
    ip += 4;
}

void Processor::adjust_relative(AccessMode modes[])
{
    reg_type param1 = get_param(modes[0], ip + 1);
    relative_base += param1;
    ip += 2;
}

void Processor::halt(AccessMode modes[])
{
    static_cast<void>(modes);
    done = true;
    ip = state.size() + 1;
}

int main() {
    string program;
    getline(std::cin, program);
    stringstream ss { program };
    vector<reg_type> code;
    code.reserve(program.size());
    for(string instruction; getline(ss, instruction, ',');) {
        code.push_back(stoll(instruction));
    }
    Processor processor;
    /*map<int, function<void, AccessMode[]>>*/
    map<Opcode, function<void(AccessMode[])>> opcodes = {
        { Opcode::kAdd, bind(&Processor::add, &processor, placeholders::_1) },
        { Opcode::kMultiply, bind(&Processor::multiply, &processor, placeholders::_1) },
        { Opcode::kLoad, bind(&Processor::load, &processor, placeholders::_1) },
        { Opcode::kStore, bind(&Processor::store, &processor, placeholders::_1) },
        { Opcode::kJumpIfTrue, bind(&Processor::jump_if_true, &processor, placeholders::_1) },
        { Opcode::kJumpIfFalse, bind(&Processor::jump_if_false, &processor, placeholders::_1) },
        { Opcode::kLessThan, bind(&Processor::less_than, &processor, placeholders::_1) },
        { Opcode::kEquals, bind(&Processor::equals, &processor, placeholders::_1) },
        { Opcode::kAdjustRelative, bind(&Processor::adjust_relative, &processor, placeholders::_1) },
        { Opcode::kHalt, bind(&Processor::halt, &processor, placeholders::_1)}
    };
    processor.state.reserve(code.size());
    std::copy(code.begin(), code.end(), back_inserter(processor.state));
    processor.ip = 0;
    processor.done = false;
    while (not processor.done) {
        reg_type instruction = processor.state.at(processor.ip);
        int mode = instruction / 100;
        Opcode opcode = static_cast<Opcode>(instruction % 100);
        AccessMode modes[3];
        for (int i = 0; i < 3; i++) {
            modes[i] = static_cast<AccessMode>(mode % 10);
            mode /= 10;
        }
        opcodes.at(opcode)(modes);
    }
    cout << endl;
    return 0;
}
