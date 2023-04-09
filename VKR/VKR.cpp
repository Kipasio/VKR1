#include <iostream>
#include <future>

#include <thread>
#include <mutex>

std::mutex mtx; // мьютекс для блокировки камеры
double chamber = 0.0; // начальное значение камеры

void fillLock(int num) {
    for (int i = 0; i < 10; i++) {
        mtx.lock(); // блокируем камеру
        chamber += 0.1;
        mtx.unlock(); // разблокируем камеру
    }
}

int Manual() {
    std::thread t1(fillLock, 1);
    std::thread t2(fillLock, 2);
    std::thread t3(fillLock, 3);
    std::thread t4(fillLock, 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "ManualChamber value: " << chamber << std::endl;

    return 0;
}
double fillAsync() {
    double chamber = 0.0;
    for (int i = 0; i < 10; i++) {
        chamber += 0.1;
    }
    return chamber;
}

int Auto() {
    std::future<double> f1 = std::async(std::launch::async, fillAsync);
    std::future<double> f2 = std::async(std::launch::async, fillAsync);
    std::future<double> f3 = std::async(std::launch::async, fillAsync);
    std::future<double> f4 = std::async(std::launch::async, fillAsync);

    double chamber = f1.get() + f2.get() + f3.get() + f4.get();

    std::cout << "AutoChamber value: " << chamber << std::endl;

    return 0;
}
int main()
{
	Auto();
    Manual();
    return 0;
}
