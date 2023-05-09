
#include <iostream>
#include <vector>
#include <chrono>

class MultidimensionalArray {
public:
    MultidimensionalArray() {

        dims[0] = 4;
        dims[1] = 3;
        dims[2] = 4;
        dims[3] = 3;


        int size = getSize();
        data = new int[size];


        for (int i = 0; i < size; i++) {
            data[i] = i;
        }
    }

    ~MultidimensionalArray() {

        delete[] data;
    }

    int& operator()(int i, int j, int k, int l) {
        // прямой доступ к элементам массива
        return data[i * (dims[1] * dims[2] * dims[3]) + j * (dims[2] * dims[3]) + k * dims[3] + l];
    }

    int& operator[](int index) {
        // доступ через векторы Айлиффа
        return data[index];
    }

    void set(int i, int j, int k, int l, int value) {
        // задание элемента массива
        (*this)(i, j, k, l) = value;
    }

    int get(int i, int j, int k, int l) {
        // получение элемента массива
        return (*this)(i, j, k, l);
    }

private:
    int dims[4];
    int* data;

    int getSize() {
        int size = 1;
        for (int i = 0; i < 4; i++) {
            size *= (dims[i] + 1);
        }
        return size;
    }
};

int main() {
MultidimensionalArray arr;

// замер времени выполнения и используемой памяти при прямом доступе

auto start_time = std::chrono::high_resolution_clock::now();
int value1 = arr(3, 2, 1, 0);

auto end_time = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

std::cout << "Direct access: value = " << value1 << ", time = " << duration.count() << " ns, memory = " << sizeof(arr) << " bytes" << std::endl;


// замер времени выполнения и используемой памяти при доступе через векторы Айлиффа

start_time = std::chrono::high_resolution_clock::now();
int value2 = arr[54];

end_time = std::chrono::high_resolution_clock::now();
duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

std::cout << "Ailiff access: value = " << value2 << ", time = " << duration.count() << " ns, memory = " << sizeof(arr) << " bytes" << std::endl;

// замер времени выполнения и используемой памяти при задании и получении элемента массива

start_time = std::chrono::high_resolution_clock::now();
arr.set(1, 1, 2, 2, 2);

int value3 = arr.get(1, 1, 2, 2);
end_time = std::chrono::high_resolution_clock::now();
duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

std::cout << "Set and get: value = " << value3 << ", time = " << duration.count() << " ns, memory = " << sizeof(arr) << " bytes" << std::endl;

return 0;
}

