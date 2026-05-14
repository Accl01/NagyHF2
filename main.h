#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <vector>

#include "gtest_lite.h"
#include "memtrace.h"
#include "planner.h"
#include "file.h"
#include "graph.h"
#include "node.h"
#include "edge.h"

#define ASCIICIM "  ____  __  __ _____                                           \n | __ )|  \\/  | ____|                                          \n |  _ \\| |\\/| |  _|                                            \n | |_) | |  | | |___                                           \n |____/|_|  |_|_____|      ____  _                             \n |  _ \\ ___  _   _| |_ ___|  _ \\| | __ _ _ __  _ __   ___ _ __ \n | |_) / _ \\| | | | __/ _ \\ |_) | |/ _` | '_ \\| '_ \\ / _ \\ '__|\n |  _ < (_) | |_| | ||  __/  __/| | (_| | | | | | | |  __/ |   \n |_| \\_\\___/ \\__,_|\\__\\___|_|   |_|\\__,_|_| |_|_| |_|\\___|_|   \n                                                               "

void clearScreen();
void initwalkspeed(Planner& planner);
void printMenu();
void run_tests();

#endif //MAIN_H