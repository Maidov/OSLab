#pragma once

#include <iostream>
#include <vector>
#include "jobs.hpp"

using graph = std::vector<std::vector<IJob*> >;

bool only_connectivity_component(graph& g); //  Проверка на то что граф имеет ровно 1 компоненту связоности
bool without_cycles(graph &g, vector<IJob*> Jobs, vector<IJob*> &finish_jobs); // не имеет циклов (нет кругов)

std::vector<IJob*> start_component(graph &g, vector<IJob*> Jobs);
std::vector<IJob*> finish_component(graph &g, vector<IJob*> Jobs);
