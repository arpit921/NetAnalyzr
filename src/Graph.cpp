#include "Graph.h"
#include <queue>
#include <iostream>
#include <algorithm>

void Graph::addUser(int user) {
    adjList[user];
}

void Graph::removeUser(int user) {
    adjList.erase(user);
    for (auto& pair : adjList) {
        pair.second.erase(user);
    }
}

void Graph::addFriendship(int user1, int user2) {
    adjList[user1].insert(user2);
    adjList[user2].insert(user1);
}

void Graph::removeFriendship(int user1, int user2) {
    adjList[user1].erase(user2);
    adjList[user2].erase(user1);
}


std::vector<int> Graph::findShortestPath(int start, int end) {
    std::unordered_map<int, int> prev;
    std::queue<int> q;
    q.push(start);
    prev[start] = 0;  // Mark start node as visited by setting its predecessor

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == end) {
            std::vector<int> path;
            for (int at = end; at != start; at = prev[at]) {
                path.push_back(at);
            }
            path.push_back(start);  // Add the start node at the end of the path
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (int neighbor : adjList[node]) {
            if (prev.find(neighbor) == prev.end()) {  // Neighbor not visited
                q.push(neighbor);
                prev[neighbor] = node;
            }
        }
    }

    return {};  // Return an empty vector if no path is found
}

std::vector<std::set<int>> Graph::detectCommunities() {
    std::vector<std::set<int>> communities;
    std::set<int> visited;

    for (const auto& pair : adjList) {
        int user = pair.first;
        if (visited.find(user) == visited.end()) {
            std::queue<int> q;
            std::set<int> community;
            q.push(user);

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                if (visited.find(node) == visited.end()) {
                    visited.insert(node);
                    community.insert(node);
                    for (int neighbor : adjList[node]) {
                        q.push(neighbor);
                    }
                }
            }

            communities.push_back(community);
        }
    }

    return communities;
}

std::vector<int> Graph::recommendFriends(int user) {
    std::unordered_map<int, int> mutualFriends;
    for (int friend1 : adjList[user]) {
        for (int friend2 : adjList[friend1]) {
            if (friend2 != user && adjList[user].find(friend2) == adjList[user].end()) {
                mutualFriends[friend2]++;
            }
        }
    }

    std::vector<std::pair<int, int>> sortedMutuals(mutualFriends.begin(), mutualFriends.end());
    std::sort(sortedMutuals.begin(), sortedMutuals.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::vector<int> recommendations;
    for (const auto& pair : sortedMutuals) {
        recommendations.push_back(pair.first);
    }

    return recommendations;
}

void Graph::printGraph() {
    for (const auto& pair : adjList) {
        std::cout << pair.first << ": ";
        for (int neighbor : pair.second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}
