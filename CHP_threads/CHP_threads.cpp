#include <iostream>
#include <Windows.h> // Required for Windows thread and synchronization APIs
using namespace std;

// Type definitions for Windows
typedef HANDLE THREADVAR;
typedef DWORD WINAPI THREADFUNCVAR;
typedef LPVOID THREADFUNCARGS;
typedef THREADFUNCVAR(*THREADFUNC)(THREADFUNCARGS);
typedef CRITICAL_SECTION THREAD_LOCK;

// Cross-platform function definitions for Windows
THREADVAR PrepareThread(THREADFUNC f, THREADFUNCARGS arg);
void StopThread(THREADVAR t);
void InitThreadLock(THREAD_LOCK& t);
void LockThread(THREAD_LOCK& t);
void UnlockThread(THREAD_LOCK& t);
void sleep(int ms); // Sleep function in milliseconds

// Thread function declarations
THREADFUNCVAR MyAsyncSimpleThread(THREADFUNCARGS lpParam);
THREADFUNCVAR MySecondSimpleThread(THREADFUNCARGS lpParam);

// Globals
int globlint = 0;
bool quitnow = false;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Entry Point                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    THREAD_LOCK recv_lock;
    InitThreadLock(recv_lock);

    // Prepare parameters for the first thread
    DWORD_PTR* svRecvThrArgs1 = new DWORD_PTR[1];
    svRecvThrArgs1[0] = (DWORD_PTR)&recv_lock;

    // Prepare parameters for the second thread
    DWORD_PTR* svRecvThrArgs2 = new DWORD_PTR[1];
    svRecvThrArgs2[0] = (DWORD_PTR)&recv_lock;

    // Start two threads with parameters
    THREADVAR recvThrHandle1 = PrepareThread(MyAsyncSimpleThread, (THREADFUNCARGS)svRecvThrArgs1);
    THREADVAR recvThrHandle2 = PrepareThread(MySecondSimpleThread, (THREADFUNCARGS)svRecvThrArgs2);

    // Main thread loop
    while (!quitnow) {
        LockThread(recv_lock); // Lock shared resource

        globlint++;
        if (globlint > 5000) {
            quitnow = true; // Exit condition
        }
        cout << "\n\tMain loop.\t" << globlint << '\n';

        UnlockThread(recv_lock); // Unlock shared resource
        sleep(5); // Sleep 5 milliseconds
    }

    // Stop the worker threads
    StopThread(recvThrHandle1);
    StopThread(recvThrHandle2);

    // Cleanup
    DeleteCriticalSection(&recv_lock);
    delete[] svRecvThrArgs1;
    delete[] svRecvThrArgs2;

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Worker Thread 1                                                                                      //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
THREADFUNCVAR MyAsyncSimpleThread(THREADFUNCARGS lpParam) {
    DWORD_PTR* arg = (DWORD_PTR*)lpParam;
    THREAD_LOCK& ref_recv_lock = *((THREAD_LOCK*)arg[0]);

    while (!quitnow) {
        LockThread(ref_recv_lock); // Lock shared resource
        globlint++;
        if (globlint > 1000) {
            quitnow = true; // Exit condition for the thread
        }
        cout << "\nThread 1.\t" << globlint << endl;
        UnlockThread(ref_recv_lock); // Unlock shared resource
        sleep(1); // Sleep 1 millisecond
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Worker Thread 2                                                                                      //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
THREADFUNCVAR MySecondSimpleThread(THREADFUNCARGS lpParam) {
    DWORD_PTR* arg = (DWORD_PTR*)lpParam;
    THREAD_LOCK& ref_recv_lock = *((THREAD_LOCK*)arg[0]);

    while (!quitnow) {
        LockThread(ref_recv_lock); // Lock shared resource
        globlint++;
        if (globlint > 2000) { // Different condition for the second thread
            quitnow = true; // Exit condition for the thread
        }
        cout << "\nThread 2.\t" << globlint << endl;
        UnlockThread(ref_recv_lock); // Unlock shared resource
        sleep(2); // Sleep 2 milliseconds
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cross-Platform Thread and Lock Management for Windows                                                //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
THREADVAR PrepareThread(THREADFUNC f, THREADFUNCARGS arg) {
    DWORD thrId;
    THREADVAR out = CreateThread(
        NULL,          // Default security attributes
        0,             // Default stack size
        (LPTHREAD_START_ROUTINE)f, // Thread function name
        arg,           // Argument to thread function
        0,             // Default creation flags
        &thrId         // Returns thread identifier
    );
    if (out == NULL) {
        cerr << "Failed to create thread. Error: " << GetLastError() << endl;
        exit(1);
    }
    return out;
}

void StopThread(THREADVAR t) {
    TerminateThread(t, 0);
    CloseHandle(t);
}

void InitThreadLock(THREAD_LOCK& t) {
    InitializeCriticalSection(&t);
}

void LockThread(THREAD_LOCK& t) {
    EnterCriticalSection(&t);
}

void UnlockThread(THREAD_LOCK& t) {
    LeaveCriticalSection(&t);
}

void sleep(int ms) {
    Sleep(ms); // Sleep in milliseconds
}
