#ifndef __LIMITED_MAP_TESTS__
#define __LIMITED_MAP_TESTS__

#include <test_helpers.h>
#include <chrono>

class LimitedMapTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(LimitedMapTests::singleElementTest);
        ADD_TEST(LimitedMapTests::thousandElementTest);
        ADD_TEST(LimitedMapTests::replaceTest);
        ADD_TEST(LimitedMapTests::removeTest);
        ADD_TEST(LimitedMapTests::relevanceTest);
    }

private:
	static bool singleElementTest();
    static bool thousandElementTest();
    static bool replaceTest();
    static bool removeTest();
    static bool relevanceTest();

    static Test_Registrar<LimitedMapTests> registrar;
};

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_start; 

public:
    Timer() : m_start(clock_t::now())
    {
    }

    void reset()
    {
        m_start = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_start).count();
    }

    void printElapsed() const
    {
        auto timeTaken = std::chrono::duration_cast<second_t>(clock_t::now() - m_start).count();
        std::cout << "Time elapsed: " << timeTaken << "\n";
    }
};

#endif