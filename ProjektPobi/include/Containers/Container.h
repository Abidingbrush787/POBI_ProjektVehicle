#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <numeric>

template<typename T>
class Container {
private:
    int capacity;
    std::vector<std::shared_ptr<T>> items;

public:
    Container(int cap) : capacity(cap) {}

    bool addItem(const std::shared_ptr<T>& item) {
        int current_capacity = std::accumulate(items.begin(), items.end(), 0,
            [](int sum, const std::shared_ptr<T>& item) {
                return sum + item->getGarageSpace();
            });

        if (current_capacity + item->getGarageSpace() > capacity) {
            return false; // Container is full
        }

        items.push_back(item);
        return true;
    }

    void removeItem(const std::shared_ptr<T>& item) {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }

    const std::vector<std::shared_ptr<T>>& getItems() const {
        return items;
    }

    void listItems() const {
        for (const auto& item : items) {
            std::cout << *item << std::endl;
        }
    }

    void clear() {
        items.clear();
    }
};

#endif // CONTAINER_H
