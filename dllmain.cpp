// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <vector>

#ifdef TODO
- Able to decode, loadand stream a collection of the major file formats
- .mp3.ogg.wav
- Able to output the audio on the target device
- Provided 2D / 3D support
- Ie.Audio spatialization
- Sources and listeners
- Audio mask flags
- A mixer
- Stackable filters
- Priorities
- Audio balances
- All of these editable in code during runtime
#endif

//struct Vector3 {
//	union {
//        struct {
//            float x;
//            float y;
//            float z;
//        };
//        float contents[3];
//	};
//
//    Vector3() : x(0), y(0), z(0) {}
//    Vector3(float value_) : x(value_), y(value_), z(value_) {}
//    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
//
//    float& operator[] (int index) { return contents[index]; }
//
//    static Vector3 add(const Vector3& first, const Vector3& second) {
//        return Vector3(first.x + second.x, first.y + second.y, first.z + second.z);
//    }
//
//    static Vector3 subtract(const Vector3& first, const Vector3& second) {
//        return Vector3(first.x - second.x, first.y - second.y, first.z - second.z);
//    }
//
//    static Vector3 multiply(const Vector3& first, const Vector3& second) {
//        return Vector3(first.x * second.x, first.y * second.y, first.z * second.z);
//    }
//
//    static Vector3 divide(const Vector3& first, const Vector3& second) {
//        return Vector3(first.x / second.x, first.y / second.y, first.z / second.z);
//    }
//};

//class Test_Vector3
//{
//public:
//
//    static Vector3 A;
//    static Vector3 B;
//
//    static void Run() {
//
//    }
//};

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}