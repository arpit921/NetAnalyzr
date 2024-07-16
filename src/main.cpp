#include <iostream>
#include "Graph.h"

void showMenu() {
    std::cout << "1. Add User" << std::endl;
    std::cout << "2. Add Friendship" << std::endl;
    std::cout << "3. Remove User" << std::endl;
    std::cout << "4. Remove Friendship" << std::endl;
    std::cout << "5. Find Shortest Path" << std::endl;
    std::cout << "6. Detect Communities" << std::endl;
    std::cout << "7. Recommend Friends" << std::endl;
    std::cout << "8. Print Graph" << std::endl;
    std::cout << "9. Exit" << std::endl;
}

int main() {
    Graph graph;
    int choice, user1, user2;

    while (true) {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter user ID: ";
                std::cin >> user1;
                graph.addUser(user1);
                break;
            case 2:
                std::cout << "Enter user IDs (user1 user2): ";
                std::cin >> user1 >> user2;
                graph.addFriendship(user1, user2);
                break;
            case 3:
                std::cout << "Enter user ID: ";
                std::cin >> user1;
                graph.removeUser(user1);
                break;
            case 4:
                std::cout << "Enter user IDs (user1 user2): ";
                std::cin >> user1 >> user2;
                graph.removeFriendship(user1, user2);
                break;
            case 5:
                std::cout << "Enter user IDs (start end): ";
                std::cin >> user1 >> user2;
                {
                    std::vector<int> path = graph.findShortestPath(user1, user2);
                    if (path.empty()) {
                        std::cout << "No path found." << std::endl;
                    } else {
                        for (int user : path) {
                            std::cout << user << " ";
                        }
                        std::cout << std::endl;
                    }
                }
                break;
            case 6:
            {
                std::vector<std::set<int>> communities = graph.detectCommunities();
                for (const auto& community : communities) {
                    for (int user : community) {
                        std::cout << user << " ";
                    }
                    std::cout << std::endl;
                }
            }
                break;
            case 7:
                std::cout << "Enter user ID: ";
                std::cin >> user1;
                {
                    std::vector<int> recommendations = graph.recommendFriends(user1);
                    for (int user : recommendations) {
                        std::cout << user << " ";
                    }
                    std::cout << std::endl;
                }
                break;
            case 8:
                graph.printGraph();
                break;
            case 9:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}
