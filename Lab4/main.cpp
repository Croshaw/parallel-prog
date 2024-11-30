#include <iostream>
#include <map>
#include "cycle.hpp"
#include "cycle_for.hpp"
#include "block.hpp"
#include "block_cycle.hpp"

void run(const std::map<char, base>& map, const std::map<char, std::string>& names) {
    char ch;
    const base& base = map.at('1');
    for (const auto &item: map)
        if(!base.equal_min(item.second))
            throw "Функция нахождения МИН элемента отработала неправильно";
    while(true) {
        system(CLEAR);
        for (const auto &item: names) {
            std::cout << "[" << item.first << "] - " << item.second << std::endl;
        }
        std::cout << "\n[0] - Завершить программу" << std::endl;
        std::cin >> ch;
        system(CLEAR);
        if (ch == '0')
            break;
        if (map.find(ch) != map.end()) {
            std::cout << names.at(ch) << ": ";
            map.at(ch).print_time();
            std::cout << "Нажмите любую клавишу...";
            std::cin >> ch;
        }
        std::cout << std::endl;
    }
}

int main() {
    srand(time(0));
    base base1;
    base1.init();

    std::map<char, base> variants;
    variants['1'] = base1;
    variants['2'] = cycle(base1);
    variants['3'] = cycle_for(base1);
    variants['4'] = block(base1);
    variants['5'] = block_cycle(base1);

    std::map<char, std::string> names = {{'1', "База"},
                                         {'2', "Цикл"},
                                         {'3', "Цикл for"},
                                         {'4', "Блок"},
                                         {'5', "Блок цикл"}};

    run(variants, names);
    return 0;
}
