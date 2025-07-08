#include <iostream>
#include <cstdlib> // std::malloc, std::free
#include <new>     // std::bad_alloc
#include <vector>  // 프로파일링 정보를 저장하기 위한 std::vector (main 함수에서 사용)
#include <map>     // 할당된 블록 추적을 위한 맵 (직접적인 operator new/delete 내부 사용은 피함)

// --------------------------------------------------------------------------------
// 메모리 프로파일링을 위한 전역 변수 및 구조체
// --------------------------------------------------------------------------------

struct AllocationInfo {
    void* address;
    size_t size;
    // 실제 프로파일링에서는 파일명, 라인 번호, 호출 스택 등 더 많은 정보를 포함할 수 있습니다.
};

// 할당된 모든 블록 정보를 저장할 맵
// operator new/delete 오버로드 내부에서 직접적으로 std::map을 사용하지 않도록 주의!
// 이 맵은 편의상 전역으로 두지만, 실제로는 메모리 할당 추적만을 위한 별도의 경량화된 구조가 필요합니다.
// 여기서는 operator new/delete 외부에서 정보를 수집하기 위한 예시로 사용됩니다.
static std::map<void*, size_t> activeAllocations;
static long long totalAllocatedBytes = 0;
static long long currentAllocatedBytes = 0;
static long long totalFreedBytes = 0;

// --------------------------------------------------------------------------------
// operator new/delete 오버로드 (메모리 할당/해제 가로채기)
// --------------------------------------------------------------------------------

// 일반 new 연산자 오버로드
void* operator new(std::size_t size)
{
    // std::malloc은 C 표준 라이브러리 함수이므로,
    // 이 함수 자체는 오버로드된 operator new를 호출하지 않습니다.
    void* ptr = std::malloc(size);

    if (ptr == nullptr) {
        // 할당 실패 시 std::bad_alloc 예외를 던지는 것이 C++ 표준 관례입니다.
        throw std::bad_alloc();
    }

    // 프로파일링 정보 기록
    // 주의: 이 부분에서 std::map 등 동적 할당을 사용하는 STL 컨테이너를 직접 사용하면
    //       다시 operator new가 호출되어 무한 재귀에 빠질 수 있습니다.
    //       여기서는 단순히 출력만 하고, 실제 맵에 넣는 작업은 main 또는 외부에서 관리합니다.
    std::cout << "[ALLOC] Size: " << size << " bytes, Address: " << ptr << std::endl;

    // 통계 업데이트 (스레드 안전성은 고려되지 않음)
    totalAllocatedBytes += size;
    currentAllocatedBytes += size;

    return ptr;
}

// 배열 new 연산자 오버로드 (new T[N] 호출 시)
void* operator new[](std::size_t size)
{
    // 내부적으로 일반 new를 호출하도록 하여 코드 중복을 피합니다.
    return operator new(size);
}

// 일반 delete 연산자 오버로드
void operator delete(void* ptr) noexcept
{
    if (ptr) {
        // 해제될 메모리의 크기를 알 수 없으므로, map에서 찾아야 하지만
        // map 사용은 무한 루프를 야기하므로 주의해야 합니다.
        // 이 예제에서는 단순히 해제되었다는 정보만 출력합니다.
        // 실제 시스템에서는 할당 시의 정보를 어딘가에 기록하여 해제 시 활용합니다.
        std::cout << "[FREE ] Address: " << ptr << std::endl;

        // 통계 업데이트 (스레드 안전성은 고려되지 않음)
        // 해제되는 정확한 크기를 알 수 없으므로, 이 통계는 부정확할 수 있습니다.
        // 정확한 추적을 위해서는 할당 시 맵에 크기를 기록하고 해제 시 찾아야 합니다.
        // 현재는 map 사용을 피하기 위해 임의로 0으로 설정하거나, 실제 할당된 크기를 찾아야 함.
        // 여기서는 예시 목적으로 생략하거나, delete[]에서 정확히 처리합니다.
        size_t freed_size = 0; // 이 크기는 실제 할당된 크기로 채워져야 함
        auto it = activeAllocations.find(ptr);
        if (it != activeAllocations.end()) {
            freed_size = it->second;
            activeAllocations.erase(it);
        }
        totalFreedBytes += freed_size;
        currentAllocatedBytes -= freed_size;

        std::free(ptr);
    }
}

// 배열 delete 연산자 오버로드 (delete[] T 호출 시)
void operator delete[](void* ptr) noexcept
{
    // 내부적으로 일반 delete를 호출하도록 하여 코드 중복을 피합니다.
    operator delete(ptr);
}

// --------------------------------------------------------------------------------
// 메인 함수 (프로파일링 테스트 및 결과 출력)
// --------------------------------------------------------------------------------

int main()
{
    std::cout << "--- 메모리 프로파일링 시작 ---" << std::endl;

    // 1. int 배열 할당 및 해제
    std::cout << "\n--- int 배열 테스트 ---" << std::endl;
    int* arr = new int[10]; // operator new[] 호출
    // 할당된 정보를 전역 맵에 수동으로 추가 (operator new 내부에서는 하지 않음)
    activeAllocations[arr] = sizeof(int) * 10;
    delete[] arr; // operator delete[] 호출

    // 2. 단일 double 할당 및 해제
    std::cout << "\n--- double 단일 객체 테스트 ---" << std::endl;
    double* d_ptr = new double; // operator new 호출
    activeAllocations[d_ptr] = sizeof(double);
    delete d_ptr; // operator delete 호출

    // 3. std::string 객체 할당 및 해제 (std::string 내부에서도 동적 할당 발생)
    std::cout << "\n--- std::string 테스트 ---" << std::endl;
    std::string* str_ptr = new std::string("Hello Memory Profiling!"); // operator new 호출
    activeAllocations[str_ptr] = sizeof(std::string); // string 객체 자체의 크기만. 내부 버퍼 크기는 다름.
    delete str_ptr; // operator delete 호출

    std::cout << "\n--- 메모리 프로파일링 종료 ---" << std::endl;

    // 프로파일링 결과 출력
    std::cout << "\n--- 프로파일링 요약 ---" << std::endl;
    std::cout << "총 할당된 바이트: " << totalAllocatedBytes << " bytes" << std::endl;
    std::cout << "총 해제된 바이트: " << totalFreedBytes << " bytes" << std::endl;
    std::cout << "현재 할당된 바이트 (잔여): " << currentAllocatedBytes << " bytes" << std::endl;
    std::cout << "활성 할당 블록 수: " << activeAllocations.size() << std::endl;

    // 아직 해제되지 않은 블록이 있다면 출력
    if (!activeAllocations.empty()) {
        std::cout << "--- 미해제 메모리 블록 ---" << std::endl;
        for (const auto& entry : activeAllocations) {
            std::cout << "  Address: " << entry.first << ", Size: " << entry.second << " bytes" << std::endl;
        }
    }

    return 0;
}