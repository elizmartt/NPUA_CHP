#include <iostream>
#include <Windows.h> 
using namespace std;


typedef HANDLE THREADVAR;
typedef DWORD WINAPI THREADFUNCVAR;
typedef LPVOID THREADFUNCARGS;
typedef THREADFUNCVAR(*THREADFUNC)(THREADFUNCARGS);
typedef CRITICAL_SECTION THREAD_LOCK;


THREADVAR PrepareThread(THREADFUNC f, THREADFUNCARGS arg);
void StopThread(THREADVAR t);
void InitThreadLock(THREAD_LOCK& t);
void LockThread(THREAD_LOCK& t);
void UnlockThread(THREAD_LOCK& t);
void sleep(int ms); 


THREADFUNCVAR MyAsyncSimpleThread(THREADFUNCARGS lpParam);
THREADFUNCVAR MySecondSimpleThread(THREADFUNCARGS lpParam);


int globlint = 0;
bool quitnow = false;


int main() {
    THREAD_LOCK recv_lock;
    InitThreadLock(recv_lock);


    DWORD_PTR* svRecvThrArgs1 = new DWORD_PTR[1];
    svRecvThrArgs1[0] = (DWORD_PTR)&recv_lock;


    DWORD_PTR* svRecvThrArgs2 = new DWORD_PTR[1];
    svRecvThrArgs2[0] = (DWORD_PTR)&recv_lock;


    THREADVAR recvThrHandle1 = PrepareThread(MyAsyncSimpleThread, (THREADFUNCARGS)svRecvThrArgs1);
    THREADVAR recvThrHandle2 = PrepareThread(MySecondSimpleThread, (THREADFUNCARGS)svRecvThrArgs2);


    while (!quitnow) {
        LockThread(recv_lock); 

        globlint++;
        if (globlint > 5000) {
            quitnow = true; 
        }
        cout << "\n\tMain loop.\t" << globlint << '\n';

        UnlockThread(recv_lock); 
        sleep(5); 
    }


    StopThread(recvThrHandle1);
    StopThread(recvThrHandle2);


    DeleteCriticalSection(&recv_lock);
    delete[] svRecvThrArgs1;
    delete[] svRecvThrArgs2;

    return 0;
}


THREADFUNCVAR MyAsyncSimpleThread(THREADFUNCARGS lpParam) {
    DWORD_PTR* arg = (DWORD_PTR*)lpParam;
    THREAD_LOCK& ref_recv_lock = *((THREAD_LOCK*)arg[0]);

    while (!quitnow) {
        LockThread(ref_recv_lock); 
        globlint++;
        if (globlint > 1000) {
            quitnow = true; 
        }
        cout << "\nThread 1.\t" << globlint << endl;
        UnlockThread(ref_recv_lock); 
        sleep(1); 
    }
    return 0;
}


THREADFUNCVAR MySecondSimpleThread(THREADFUNCARGS lpParam) {
    DWORD_PTR* arg = (DWORD_PTR*)lpParam;
    THREAD_LOCK& ref_recv_lock = *((THREAD_LOCK*)arg[0]);

    while (!quitnow) {
        LockThread(ref_recv_lock);
        globlint++;
        if (globlint > 2000) { 
            quitnow = true; 
        }
        cout << "\nThread 2.\t" << globlint << endl;
        UnlockThread(ref_recv_lock); 
        sleep(2); 
    }
    return 0;
}

THREADVAR PrepareThread(THREADFUNC f, THREADFUNCARGS arg) {
    DWORD thrId;
    THREADVAR out = CreateThread(
        NULL,          
        0,             
        (LPTHREAD_START_ROUTINE)f, 
        arg,           
        0,             
        &thrId         
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
