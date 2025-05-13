#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>

struct LargeObject {
    std::array<double, 100000> data;

    inline static std::size_t count = 0;
    LargeObject() { count++; }
    ~LargeObject() { count--; }
};

// Удаляет случайный элемент из вектора
void removeRandom(std::vector<std::shared_ptr<LargeObject>> & collection, std::default_random_engine & engine) {
    if (collection.empty()) return;
    size_t index = engine() % collection.size();
    collection.erase(collection.begin() + index);
}

// Модификация объекта
void changeLargeObject(const std::shared_ptr<LargeObject> & object) {
    object->data[0] = 1.0;
}

void doStuff() {
    std::random_device device;
    std::default_random_engine engine(device());

    // Вектор умных указателей
    std::vector<std::shared_ptr<LargeObject>> objVector(10);
    for (auto & ptr : objVector) {
        ptr = std::make_shared<LargeObject>();
    }

    // Копируем вектор (shared_ptr увеличивает счётчик)
    auto objVectorCopy = objVector;

    removeRandom(objVector, engine);
    removeRandom(objVectorCopy, engine);
    removeRandom(objVectorCopy, engine);

    for (const auto & objPtr : objVector) {
        changeLargeObject(objPtr);
    }

    // shared_ptr автоматически очистит память
}

int main() {
    doStuff();
    std::cout << "Leaked large objects: " << LargeObject::count << std::endl;
}
/*
Заработало
danil_kulakov@MacBook-Air-Danil smartPointers % ./problem3
Leaked large objects: 0
danil_kulakov@MacBook-Air-Danil smartPointers % ./problem3
Leaked large objects: 0
danil_kulakov@MacBook-Air-Danil smartPointers % ./problem3
Leaked large objects: 0
*/
