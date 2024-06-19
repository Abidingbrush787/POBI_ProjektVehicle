#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <numeric>

// Klasa szablonowa kontenera do zarządzania pojazdami
template<typename T>
class Container {
private:
    int capacity; // Pojemność kontenera
    std::vector<std::shared_ptr<T>> items; // Przechowywane elementy

public:
    Container(int cap) : capacity(cap) {}

    // Dodaje element do kontenera
    bool addItem(const std::shared_ptr<T>& item) {
        int current_capacity = std::accumulate(items.begin(), items.end(), 0,
            [](int sum, const std::shared_ptr<T>& item) {
                return sum + item->getGarageSpace();
            });

        if (current_capacity + item->getGarageSpace() > capacity) {
            return false; // Kontener jest pełny
        }

        items.push_back(item);
        return true;
    }

    // Usuwa element z kontenera
    void removeItem(const std::shared_ptr<T>& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }

    // Zwraca wszystkie elementy
    const std::vector<std::shared_ptr<T>>& getItems() const {
        return items;
    }

    // Wypisuje wszystkie elementy
    void listItems() const {
        for (const auto& item : items) {
            std::cout << *item << std::endl;
        }
    }

    // Czyści kontener
    void clear() {
        items.clear();
    }
};

#endif // CONTAINER_H
