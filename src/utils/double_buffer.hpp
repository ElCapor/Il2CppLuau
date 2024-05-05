#ifndef DOUBLE_BUFFER_HPP
#define DOUBLE_BUFFER_HPP

#include <vector>
#include <mutex>

template<typename T>
class DoubleBuffer {
public:
    DoubleBuffer() : currentBufferIndex(0) {}

    // Add an item to the current buffer
    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex);
        buffers[currentBufferIndex].push_back(item);
    }

    // Swap buffers and clear the new current buffer
    void swapBuffers() {
        std::lock_guard<std::mutex> lock(mutex);
        currentBufferIndex = (currentBufferIndex + 1) % 2;
        buffers[currentBufferIndex].clear();
    }

    // Get a reference to the current buffer for reading
    const std::vector<T>& getCurrentBuffer() const {
        return buffers[currentBufferIndex];
    }

private:
    std::vector<T> buffers[2]; // Double buffer
    std::mutex mutex; // Mutex to protect buffer swapping
    size_t currentBufferIndex; // Index of the current buffer
};


#endif