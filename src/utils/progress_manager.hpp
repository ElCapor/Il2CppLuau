#ifndef PROGRESS_MANAGER_HPP
#define PROGRESS_MANAGER_HPP
/*
AUTHOR : ElCapor
Description : A simple utility to output progress for an operation;
*/
#include <iostream>
#include <vector>
#include <cmath>
class ProgressStep
{
public:
    ProgressStep(const char* description = "") : description(description){};
    const char* GetText() { return this->description;};
private:
    const char* description;
};

class ProgressManager
{
public:
ProgressManager(int num = 0) : numberOfExpectedSteps(num), stepIndex(0){};
void Step(const char* step_str) {
    stepIndex++;
    std::cout << "[" << std::round(static_cast<double>(stepIndex) / numberOfExpectedSteps * 100) << "%] " << step_str << std::endl;
    m_Steps.push_back(ProgressStep(step_str));
}

private:
    int numberOfExpectedSteps;
    int stepIndex;
    std::vector<ProgressStep> m_Steps;
};

#endif