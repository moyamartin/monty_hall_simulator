/// Copyright 2022 Martin Moya <moyamartin1@gmail.com>
//
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "MontyHall.hpp"
#include "Player.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/spdlog.h"
#include <argparse/argparse.hpp>

static constexpr int number_of_doors = 2;
static constexpr char thread_log_pattern[] = "[%H:%M:%S %z] [thread %t] %v";

/* declare prototype functions */
bool run_simulation(const char *name, bool player_keep_same_door);
void thread_simulation(int iterations, int *won_keep_same_door,
                       int *won_choose_new_door);
void print_intro();

std::mutex thread_simulation_mutex;

void print_intro() {
    std::cout << "Welcome to the MontyHall show!" << std::endl;
}

void thread_simulation(int iterations, int *won_keep_same_door,
                       int *won_choose_new_door) {
    spdlog::info("Running new thread with {} iterations", iterations);
    for (int i = 0; i < iterations; ++i) {
        spdlog::debug("Running iteration number #{}", i + 1);
        bool keep_same_door_won = run_simulation("thread_1", true);
        bool choose_new_door_won = run_simulation("thread_1", false);
        {
            const std::lock_guard<std::mutex> lock(thread_simulation_mutex);
            *won_keep_same_door += keep_same_door_won;
            *won_choose_new_door += choose_new_door_won;
        }
    }
}

bool run_simulation(const char *name, bool player_keep_same_door) {
    Player player(name, number_of_doors, player_keep_same_door);
    MontyHall monty_hall(number_of_doors);

    spdlog::debug("{} is picking a door", player.get_name());
    int first_door = player.pick_door(-1);
    spdlog::debug("{} picked door #{}", player.get_name(), first_door);
    int monty_hall_door = monty_hall.pick_door(first_door);
    spdlog::debug("{} picked door #{}", monty_hall.get_name(), monty_hall_door);
    int second_door = player.pick_door(monty_hall_door);
    spdlog::debug("{} second pick is door #{}", player.get_name(), second_door);
    bool has_won = monty_hall.has_won(second_door);
    spdlog::debug("{} has won? {}", player.get_name(),
                  (has_won ? "yes" : "no"));
    return has_won;
}
int main(int argc, char *argv[]) {
    /* configure spdlog */
    std::vector<spdlog::sink_ptr> sinks;
    spdlog::level::level_enum verbosity = spdlog::level::info;
    spdlog::set_pattern(thread_log_pattern);

    /* configure arguments*/
    argparse::ArgumentParser program("monty_hall_simulation", "0.0.1");
    program.add_argument("-s")
        .help("The number of simulations to run")
        .default_value(1000)
        .scan<'d', int>();
    program.add_argument("-j")
        .help("The number of jobs to run simultaneously")
        .default_value(1)
        .scan<'d', int>();
    program.add_argument("-v")
        .action([&](const auto &) { verbosity = spdlog::level::debug; })
        .help("Set logging to debug level for verbosity")
        .default_value(false)
        .implicit_value(true)
        .nargs(0);
    program.add_argument("-f")
        .help("Set path of logfile")
        .default_value(std::string(""));
    program.add_description(
        "This software implements a simulation of the "
        "Monty Hall problem, it will run the amount of simulations "
        "specified by the -s flag");

    /* try to parse arguments */
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        /* if it fails be cause an argument is invalid, show help */
        spdlog::warn("{}", err.what());
        std::cout << program << std::endl;
        std::exit(1);
    }

    // configure loggers
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
    // if file is specified then add a logger sink to that file
    // this will make spdlog to start writing to a file specified to -f
    std::string log_path = program.get<std::string>("-f");
    if (log_path.compare("") != 0) {
        sinks.push_back(
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_path));
    }
    auto combined_logger =
        std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
    spdlog::register_logger(combined_logger);
    spdlog::set_default_logger(spdlog::get("logger"));

    // parse the number of iterations
    int number_of_iterations = program.get<int>("-s");
    int number_of_jobs = program.get<int>("-j");
    int won_keep_same_door = 0;
    int won_choose_new_door = 0;

    /* start simulations */
    spdlog::set_level(verbosity);
    spdlog::info("Monty Hall Problem Simulatior (C++11)");
    spdlog::debug("Running simulation for {} iterations", number_of_iterations);

    /* determine if all the threads will have the same amount of iterations */
    int rest = number_of_iterations % number_of_jobs;
    int division = number_of_iterations / number_of_jobs;
    std::vector<std::thread> list_of_threads;

    // start measuring time before running all simulations
    auto t1 = std::chrono::high_resolution_clock::now();

    /*
     * for each job, instantiate a thread and push it back to the list of
     * threads
     */
    for (int j = 0; j < number_of_jobs - 1; ++j) {
        std::thread t(&thread_simulation, number_of_iterations / number_of_jobs,
                      &won_keep_same_door, &won_choose_new_door);
        list_of_threads.push_back(std::move(t));
    }

    // to the last thread assign the rest of the division if the number of
    // iterations cannot be divided by the number of jobs, otherwise assing the
    // result of the division
    std::thread t(&thread_simulation, (rest > 0) ? rest : division,
                  &won_keep_same_door, &won_choose_new_door);
    list_of_threads.push_back(std::move(t));
    /* wait for all threads to end */
    std::for_each(list_of_threads.begin(), list_of_threads.end(),
                  [](std::thread &t) { t.join(); });
    // stop measuring time
    auto t2 = std::chrono::high_resolution_clock::now();

    /* calculate print results */
    float probability_choose_new_door =
        (static_cast<float>(won_choose_new_door) /
         static_cast<float>(number_of_iterations)) *
        100.0;
    float probability_keep_same_door =
        (static_cast<float>(won_keep_same_door) /
         static_cast<float>(number_of_iterations)) *
        100.0;
    spdlog::info("Probability of winning keeping the same door {:03.2f}%",
                 probability_keep_same_door);
    spdlog::info("Probability of winning changing the door {:03.2f}%",
                 probability_choose_new_door);
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    spdlog::info("Execution time {}uS", (duration));
    spdlog::shutdown();
}
