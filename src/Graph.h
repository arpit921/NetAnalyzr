#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <set>
#include <string>

class Graph {
public:
    void addUser(int user);
    void removeUser(int user);
    void addFriendship(int user1, int user2);
    void removeFriendship(int user1, int user2);
    std::vector<int> findShortestPath(int start, int end);
    std::vector<std::set<int>> detectCommunities();
    std::vector<int> recommendFriends(int user);
    void printGraph();

private:
    std::unordered_map<int, std::set<int>> adjList;
};

#endif // GRAPH_H
