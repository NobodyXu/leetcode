/**
 * This file compares the performance between 
 *
 *  - constructing std::vector<vector<int>> from std::set<vector<int>> 
 *    using the iterator from set
 *
 *  and
 *
 *  - moving each element from set to a constructed vector using push_back.
 */
#include <benchmark/benchmark.h>

#include <utility>

#include <set>
#include <vector>

static auto make_set(int size) {
    std::set<std::vector<int>> ret;

    std::vector<int> value = {0, 0, 0};
    for (int i = 0; i != size; ++i) {
        ret.insert(value);
        
        // Increment value
        for (int j = 2; ++value[j] == 0; ++j)
            ;
    }

    return ret;
}

using result_vec = std::vector<std::vector<int>>;

static void BM_ctor(benchmark::State &state) {
    auto set = make_set(state.range(0));

    for (auto _: state) {
        result_vec result(set.begin(), set.end());

        benchmark::DoNotOptimize(result.data());
        benchmark::ClobberMemory();
    }

    state.SetComplexityN(state.range(0));
}

// Register the function as a benchmark
BENCHMARK(BM_ctor) -> RangeMultiplier(4) -> Range(8, 32 << 17) -> Complexity(benchmark::oN);

// Define another benchmark
static void BM_manual_move(benchmark::State &state) {
    auto set = make_set(state.range(0));

    for (auto _ : state) {
        result_vec result;
        result.reserve(set.size());

        for (auto &each: set)
            result.push_back(std::move(each));

        benchmark::DoNotOptimize(result.data());
        benchmark::ClobberMemory();
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_manual_move) -> RangeMultiplier(4) -> Range(8, 32 << 17) -> Complexity(benchmark::oN);

BENCHMARK_MAIN();
