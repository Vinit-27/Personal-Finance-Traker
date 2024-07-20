# Personal-Finance-Traker

## Overview

The Personal Finance Tracker is a software solution designed to help users maintain their transaction records, prioritize their wish-list based on needs, and minimize financial transactions. It simplifies financial management by providing organized and efficient tracking of personal finances.

## Features

1. **Financial Records Management**:
   - Uses linked list data structure to store transaction records.
   - Records are saved in a CSV file for easy access with Excel or other spreadsheet applications.

2. **Minimum Cash Flow**:
   - Utilizes directed and weighted graph data structure to minimize the number of transactions.
   - Implements an algorithm with O(n²) time complexity to optimize transaction flow.

3. **Priority-Based Wish-List**:
   - Employs min heap sort algorithm to set priorities on wishes.
   - Min heap sort is chosen over a 2D priority queue due to its better time complexity (O(n*log n)).

## Data Handling

- **Records.csv**: Stores transaction data.
- **LoginData.txt**: Stores login credentials for future logins.

## Usage

1. **Login and Transaction Records**:
   - The program allows users to log in and maintain their transaction records efficiently.
     ![image](https://github.com/user-attachments/assets/9ce63c02-d7e4-4955-b966-896713e5be08)
![image](https://github.com/user-attachments/assets/1dbffa76-10cb-45f3-8e62-f2a87e102f93)
![image](https://github.com/user-attachments/assets/0c3879d7-53f4-4a4b-bde2-ed32f0915dd2)

2. **Set Priority Function**:
   - Users can set priorities on their wish-list items to ensure that their most important needs are met first.
     ![image](https://github.com/user-attachments/assets/cc86f953-3dc2-440c-8683-1062f3c16a2f)

3. **Minimum Cash Flow Function**:
   - The software optimizes transactions to minimize the total number of financial movements.
     ![image](https://github.com/user-attachments/assets/a62d8a15-2dd9-4087-a224-9b4e5d147925)

## Note

This program will create two additional files in the same directory as the code:
- `Records.csv`
- `LoginData.txt`

These files are not automatically removed and should be manually deleted if no longer needed.










## Aim

The aim of this project is to develop a software solution that helps users maintain transaction records in an organized manner, prioritize their wish-list based on needs, and minimize financial transactions.

## Example

Consider a scenario where Person A gives Rs. 20 to Person B, and Person B gives Rs. 20 to Person C. In reverse, Person C returns Rs. 20 to Person B, and Person B returns Rs. 20 to Person A. This results in 4 transactions. If Person B had instructed Person A to send Rs. 20 directly to Person C and Person C returned Rs. 20 to Person A, the total number of transactions would be reduced to 2.

This software aims to achieve such optimization in financial transactions.

## Conclusion

The Personal Finance Tracker is an innovative solution to help individuals manage their finances more efficiently by keeping well-organized records, prioritizing needs, and minimizing unnecessary transactions.
