﻿/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16.12.2019 22:31:51
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cinttypes>
#include <sstream>
#include <functional>
#include <iterator>
#include <exception>
#include <execinfo.h>
#include <cstdio>
#include <cstdlib>
#include <cxxabi.h>
#include <memory>
#include <thread>
#include <array>
using namespace std;

enum class AccessMode: uint8_t {
    kPositionMode = 0,
    kImmediateMode = 1,
    kRelativeMode = 2,
    kUnknown = 3
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

const map <int, char> output_char = {
    { 0, ' ' },
    { 1, '|' },
    { 2, '#' },
    { 3, '_' },
    { 4, 'O' }
};

using reg_type = long long int;
constexpr auto kArgMaxCount = 3;

constexpr auto kMaxColumns = 45;
constexpr auto kMaxRows = 24;
constexpr auto kCapacity = 5000;
std::shared_ptr<char> cppDemangle(const char *abiName)
{
    int status;
    char *ret = abi::__cxa_demangle(abiName, 0, 0, &status);

    /* NOTE: must free() the returned char when done with it! */
    std::shared_ptr<char> retval;
    retval.reset( (char *)ret, [](char *mem) { if (mem) free((void*)mem); } );
    return retval;
}

void print_trace (void)
{
    void *array[20];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace (array, 20);
    strings = backtrace_symbols (array, size);


    cout << "Obtained " << size << " stack frames" << endl;
    for (i = 0; i < size; i++) {
        shared_ptr<char> demangled = cppDemangle(strings[i]);
        cout << strings[i] << "  ";
    }

    free (strings);
}


class Game {
public:
    vector<reg_type> turn_data;
    array<array<char, kMaxRows>, kMaxColumns> fields;
    reg_type result = 0;
    reg_type ball_position;
    reg_type paddle_position;
    void fulfill() {
        for (size_t index = 0; index < turn_data.size(); index += 3) {
            reg_type x = turn_data[index];
            reg_type y = turn_data[index + 1];
            if (x != -1 or y != 0) {
                char field = output_char.at(turn_data[index + 2]);
//                cout << "(" << x << ","
//                     << y << "): " << turn_data[index+2] << endl;
                fields[x][y] = field;
                if (field == 'O') {
                    ball_position = x;
                } else if (field == '_') {
                    paddle_position = x;
                }
            }
            else {
                result = turn_data[index + 2];
            }
        }
        turn_data.clear();
        turn_data.reserve(kCapacity);
    }

    void print() {
        std::system("clear");
        for (size_t y = 0; y < kMaxRows; y++) {
            for (size_t x = 0; x < kMaxColumns; x++) {
                cout << fields[x][y];
            }
            cout << endl;
        }
        cout << "result: " << result << endl;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20ms);
    }
    int move() {
        if (ball_position < paddle_position) {
            return -1;
        } else if (paddle_position < ball_position) {
            return 1;
        }
        return 0;
    }
};

class Processor {
public:
    vector<reg_type> state;
    size_t relative_base;
    size_t ip; // instruction pointer
    bool done;
    Game game;
    reg_type access_resize(reg_type index);
    reg_type get_param(AccessMode mode, reg_type index);
    reg_type get_param_address(AccessMode mode, reg_type index);
    reg_type get_param_address2(AccessMode mode, reg_type index);
    void resize(reg_type index);
    void add(const array<AccessMode, kArgMaxCount>& modes);
    void multiply(const array<AccessMode, kArgMaxCount>& modes);
    void load(const array<AccessMode, kArgMaxCount>& modes);
    void store(const array<AccessMode, kArgMaxCount>& modes);
    void jump_if_true(const array<AccessMode, kArgMaxCount>& modes);
    void jump_if_false(const array<AccessMode, kArgMaxCount>& modes);
    void less_than(const array<AccessMode, kArgMaxCount>& modes);
    void equals(const array<AccessMode, kArgMaxCount>& modes);
    void adjust_relative(const array<AccessMode, kArgMaxCount>& modes);
    void halt(const array<AccessMode, kArgMaxCount>& modes);
    void print();
};

void Processor::resize(reg_type index) {
    if (static_cast<size_t>(index) > state.size() and false) {
        cout << "RESIZE " << index << "  ";
        print_trace();
    }
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
    reg_type address = access_resize(index);
    reg_type param = 0;
    switch(mode) {
        case AccessMode::kUnknown:
            [[fallthrough]];
        case AccessMode::kImmediateMode:
            param = address;
            break;
        case AccessMode::kRelativeMode:
            address += relative_base;
            [[fallthrough]];
        case AccessMode::kPositionMode:
            param = access_resize(address);
    }
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
    reg_type param = access_resize(index);
    if (AccessMode::kRelativeMode == mode) {
            param += relative_base;
    }
    resize(param);
    return param;
}

void Processor::add(const array<AccessMode, kArgMaxCount>& modes) {
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    reg_type result_addr = get_param_address(modes[2], ip + 3);
    reg_type result = param1 + param2;
    state.at(result_addr) = result;
    ip += 4;
}

void Processor::multiply(const array<AccessMode, kArgMaxCount>& modes) {
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    reg_type result_addr = get_param_address(modes[2], ip + 3);
    reg_type result = param1 * param2;
    state.at(result_addr) = result;
    ip += 4;
}

void Processor::load(const array<AccessMode, kArgMaxCount>& modes)
{
    reg_type address = 0;
    address = get_param_address(modes[0], ip + 1);
    reg_type value = 0;
    game.fulfill();
    game.print();
//    cout << "Please give a value: ";
//    cin >> value;
    value = game.move();
    state.at(address) = value;
    cout << endl;
    ip += 2;
}

void Processor::store(const array<AccessMode, kArgMaxCount>& modes)
{
    reg_type value = get_param(modes[0], ip + 1);
    game.turn_data.push_back(value);
    ip += 2;
}

void Processor::jump_if_true(const array<AccessMode, kArgMaxCount>& modes)
{
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    if (param1 != 0) {
        ip = param2;
    } else {
        ip += 3;
    }
}

void Processor::jump_if_false(const array<AccessMode, kArgMaxCount>& modes)
{
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    if (param1 == 0) {
        ip = param2;
    } else {
        ip += 3;
    }
}

void Processor::less_than(const array<AccessMode, kArgMaxCount>& modes)
{
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    reg_type param3 = get_param_address(modes[2], ip + 3);
    state.at(param3) = (param1 < param2) ? 1 : 0;
    ip += 4;
}

void Processor::equals(const array<AccessMode, kArgMaxCount>& modes)
{
    reg_type param1 = get_param(modes[0], ip + 1);
    reg_type param2 = get_param(modes[1], ip + 2);
    reg_type param3 = get_param_address(modes[2], ip + 3);
    state.at(param3) = (param1 == param2) ? 1 : 0;
    ip += 4;
}

void Processor::adjust_relative(const array<AccessMode, kArgMaxCount>& modes)
{
    reg_type param1 = get_param(modes[0], ip + 1);
    relative_base += param1;
    ip += 2;
}

void Processor::halt(const array<AccessMode, kArgMaxCount>& modes)
{
    static_cast<void>(modes);
    done = true;
    ip = state.size() + 1;
}

void Processor::print() {
    for (size_t i = 0; i < state.size(); i++) {
        cout << i << ": " << state.at(i) << endl;
    }
}

int main(int argc, char** argv) {
    string program;
    if (argc == 1) {
        cerr << "Require filename parameter";
        return -1;
    }
    ifstream input;
    input.open(argv[1]);
    getline(input, program);
    stringstream ss { program };
    vector<reg_type> code;
    code.reserve(program.size());
    for(string instruction; getline(ss, instruction, ',');) {
        code.push_back(stoll(instruction));
    }
    Processor processor;
    /*map<int, function<void, AccessMode[]>>*/
    const map<Opcode, function<void(const array<AccessMode, kArgMaxCount>&)>> opcodes = {
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
    processor.state.reserve(kCapacity);
    std::copy(code.begin(), code.end(), back_inserter(processor.state));
    processor.ip = 0;
    processor.done = false;
    processor.relative_base = 0;
    processor.state.resize(kCapacity);
    processor.game.turn_data.reserve(kCapacity);
    try {
        while (not processor.done) {
            reg_type instruction = processor.state.at(processor.ip);
            int mode = instruction / 100;
            Opcode opcode = static_cast<Opcode>(instruction % 100);
            array<AccessMode, kArgMaxCount> modes { AccessMode::kUnknown };
            modes.fill(AccessMode::kUnknown);
            for (int i = 0; i < 3; i++) {
                modes[i] = static_cast<AccessMode>(mode % 10);
                mode /= 10;
            }
            opcodes.at(opcode)(modes);
        }

    } catch (std::exception& exc) {
        cout << endl;
        cout << exc.what() << endl;
        cout << processor.state.size() << "  ";
        cout << processor.ip << "  ";
        cout << processor.done << endl;
    }
    processor.game.fulfill();
    cout << "Full result: " << processor.game.result;
    cout << endl;
    return 0;
}
