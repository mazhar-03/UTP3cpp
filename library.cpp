#include "main_Main.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

JNIEXPORT jintArray JNICALL Java_main_Main_withoutDuplicates
        (JNIEnv *env, jclass obj, jintArray arr){
    if (arr == nullptr) {
        return nullptr;  // Return null if the array is null
    }

    // Get the length of the input array
    auto length = env->GetArrayLength(arr);
    auto elems = env->GetIntArrayElements(arr, 0);

    std::vector<jint> result;

    // Iterate through the input array and add elements to result if not already present
    for (int i = 0; i < length; ++i) {
        bool isDuplicate = false;

        // Check if the element is already in the result
        for (auto& item : result) {
            if (item == elems[i]) {
                isDuplicate = true;
                break;
            }
        }

        // If the element is not a duplicate, add it to the result
        if (!isDuplicate) {
            result.push_back(elems[i]);
        }
    }

    // Release the original array memory
    env->ReleaseIntArrayElements(arr, elems, 0);

    // Create a new jintArray to hold the result
    auto resultArray = env->NewIntArray(result.size());

    // Copy the result vector into the jintArray
    env->SetIntArrayRegion(resultArray, 0, result.size(), result.data());

    return resultArray;
}


JNIEXPORT jobjectArray JNICALL Java_main_Main_chunk
        (JNIEnv *env, jclass obj, jstring inputStr, jint n) {
    // Check if the input string is null
    if (inputStr == nullptr) {
        return nullptr;
    }

    // If n is less than 1, throw IllegalArgumentException
    if (n < 1) {
        jclass exceptionCls = env->FindClass("java/lang/IllegalArgumentException");
        env->ThrowNew(exceptionCls, std::to_string(n).c_str());
        return nullptr;
    }

    // Get the input string as a C++ string
    const char *nativeString = env->GetStringUTFChars(inputStr, 0);
    std::string input(nativeString);
    env->ReleaseStringUTFChars(inputStr, nativeString);

    int inputLen = input.length();

    // Handle the case when n is 0 (empty array expected)
    if (n == 0) {
        jclass stringClass = env->FindClass("java/lang/String");
        jobjectArray resultArray = env->NewObjectArray(0, stringClass, nullptr);
        return resultArray;
    }

    // Special case for empty input string
    if (inputLen == 0) {
        // Create an array of empty strings
        jobjectArray resultArray = env->NewObjectArray(n, env->FindClass("java/lang/String"), env->NewStringUTF(""));
        return resultArray;
    }

    // Calculate the total number of chunks needed
    int totalChunks = (inputLen + n - 1) / n;  // ceiling of inputLen / n

    // Create the result array with the total number of chunks
    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray resultArray = env->NewObjectArray(totalChunks, stringClass, env->NewStringUTF(""));

    // Split the input string into chunks
    for (int i = 0; i < totalChunks; ++i) {
        int start = i * n;
        int end = std::min(start + n, inputLen);
        std::string chunk = input.substr(start, end - start);

        // If this is the last chunk and it's shorter than n, pad with spaces
        if (chunk.length() < n && end < inputLen) {
            chunk.append(n - chunk.length(), ' ');
        }

        // Set the chunk into the result array
        env->SetObjectArrayElement(resultArray, i, env->NewStringUTF(chunk.c_str()));
    }

    return resultArray;
}


JNIEXPORT JNICALL auto Java_main_Main_greeter(
        JNIEnv *, jclass
) -> void {
    std::cout << "Greetings from C++ library!\n";
}

JNIEXPORT jboolean JNICALL Java_main_Main_isPalindrome
        (JNIEnv *env, jclass obj , jstring sVal){
    if(sVal == nullptr)
        return JNI_FALSE;

    auto inputStr = env->GetStringUTFChars(sVal, 0);
    auto s = std::string(inputStr);

    env->ReleaseStringUTFChars(sVal, inputStr);

    auto reversed = s;
    std::reverse(reversed.begin(), reversed.end());

    return (s == reversed) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jstring JNICALL Java_main_Main_reversed
        (JNIEnv *env, jclass obj, jstring sVal){
    const char* inputStr = env->GetStringUTFChars(sVal, 0);
    char res[265] = "";

    const char *tmp = inputStr;

    while(*tmp != '\0'){
        tmp ++;
    }

    //0'dan sona kadar gittik farki bize harf sayisi(len) verir.
    int len = tmp - inputStr;

    int count = 0;
    while(count < len){
        tmp--;
        res[count++] = *tmp;
    }

    env->ReleaseStringUTFChars(sVal, inputStr);
    return env->NewStringUTF(res);
}
