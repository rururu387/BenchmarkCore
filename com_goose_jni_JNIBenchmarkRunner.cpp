#include "com_goose_jni_JNIBenchmarkRunner.h"
#include <chrono>
#include <vector>
//#include <windows.h>
#include <unistd.h>
#include <thread>

using namespace std;
using namespace std::chrono;

int64_t runBenchmarkGetFPUProcessedOperationsCount(int64_t duration) {
    int64_t counter = 0;

    int64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int64_t endTime = startTime + duration;
    int64_t currentTime = startTime;

    while (currentTime < endTime) {
        for (double i = 0.0; i < 1000.0; i++) {
        asm volatile (
                    "fldpi\n"

                    "fld1\n"
                    "faddp\n"

                    "fldpi\n"
                    "fsubp\n"

                    "fldpi\n"
                    "fmulp\n"

                    "fldpi\n"
                    "fdivp\n"

                    "fabs\n"
                    "fsqrt\n"
                    "fsin\n"

//                    : "=t" (storage)
                );
            counter += 14;
        }
        currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
    return counter;
}

void runNOPInstruction(int64_t duration) {

    int64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int64_t endTime = startTime + duration;
    int64_t currentTime = startTime;

    while (currentTime < endTime) {
        for (double i = 0; i < 1000; i++) {
        asm volatile (
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                    "NOP\n"
                );
        }
        currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
    return;
}

JNIEXPORT jlongArray JNICALL Java_com_goose_jni_JNIBenchmarkRunner_runBenchmarkGetFPUProcessedOperationsCount(JNIEnv *env, jclass, jlong totalDurationMillis, jlong cycleMillis, jfloat loadRatio) {
    std::vector<int64_t> totalOperationsCount;
    int64_t totalDurationLong = (int64_t) totalDurationMillis;
    int64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int64_t endTime = startTime + totalDurationLong;
    int64_t currentTime = startTime;
    while (currentTime < endTime) {
        int64_t benchmarkDuration = currentTime + (cycleMillis * loadRatio) > endTime ? endTime - currentTime : cycleMillis * loadRatio ;
        int64_t operationsAmount = runBenchmarkGetFPUProcessedOperationsCount(benchmarkDuration);
        auto benchmarkTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        //TODO - run on real-time OS, kinda crunch
        while (totalOperationsCount.size() < (benchmarkTime - startTime) / cycleMillis) {
            totalOperationsCount.push_back(0);
        }
        totalOperationsCount.push_back(operationsAmount);

        int64_t NOPTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(currentTime + cycleMillis - NOPTime));
//        runNOPInstruction(currentTime + cycleMillis - NOPTime);

        currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    }

    jlongArray retVal = env->NewLongArray(totalOperationsCount.size());
    env->SetLongArrayRegion(retVal, 0, totalOperationsCount.size(), totalOperationsCount.data());
    return retVal;
}
