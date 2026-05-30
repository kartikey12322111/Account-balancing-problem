# Debt Simplification and Cash Flow Minimization

## Project Overview

When a group of people spend money on behalf of each other, a complex network of debts is created. Settling each debt individually can result in unnecessary transactions and payment chains. This project aims to simplify these debts and generate an optimized set of transactions that settles all balances with fewer money transfers.

The system calculates the net balance of each participant and directly matches debtors with creditors, eliminating unnecessary intermediate payments.

---

# Problem Statement

Given a list of transactions in the form:

```
Person A owes Person B amount X
```

Determine an optimized set of transactions such that:

* Every person's final balance becomes zero.
* The total amount paid and received remains unchanged.
* Unnecessary intermediate transactions are removed.
* The debt network is simplified.

---

# Objectives

* Calculate the net balance of every participant.
* Identify debtors and creditors.
* Generate a simplified settlement plan.
* Reduce the number of money transfers.
* Handle large numbers of transactions efficiently.

---

# Approach

## Step 1: Compute Net Balance

A hash map is used to store the net balance of each person.

For every transaction:

```
A owes B amount X
```

The balance is updated as:

```
balance[A] -= X
balance[B] += X
```

After processing all transactions:

* Negative balance → Person must pay money.
* Positive balance → Person should receive money.
* Zero balance → Already settled.

### Example

Input:

```
Tom -> Jerry : 1000
Jerry -> Spike : 1000
Spike -> Tom : 500
```

Net Balances:

```
Tom    = -500
Jerry  = 0
Spike  = +500
```

---

## Step 2: Separate Debtors and Creditors

After computing balances:

### Debtors

People having negative balances.

Example:

```
Tom : 500
Alice : 300
```

### Creditors

People having positive balances.

Example:

```
Spike : 400
Bob : 400
```

---

## Step 3: Settle Debts

Two pointers are maintained:

* One for debtors.
* One for creditors.

At each step:

```
amount = min(debtor_balance, creditor_balance)
```

A transaction is generated:

```
debtor pays creditor amount
```

Balances are updated and pointers are moved whenever a balance becomes zero.

This process continues until all balances are settled.

---

# Algorithm

1. Read all transactions.
2. Calculate net balance of every person.
3. Create separate debtor and creditor lists.
4. Match debtors and creditors using a two-pointer approach.
5. Generate optimized transactions.
6. Continue until all balances become zero.
7. Return the final settlement list.

---

# Data Structures Used

## unordered_map<string, long long>

Stores net balances.

Example:

```cpp
unordered_map<string, long long> balance;
```

---

## vector<pair<string, long long>>

Stores debtors and creditors.

```cpp
vector<pair<string,long long>> debtors;
vector<pair<string,long long>> creditors;
```

---

## Structure for Result

```cpp
struct Settlement
{
    string from;
    string to;
    long long amount;
};
```

---

# Example

## Input

```cpp
{
    {"Tom", "Jerry", 1000},
    {"Jerry", "Spike", 1000},
    {"Spike", "Tom", 500}
}
```

## Balance Calculation

```
Tom    = -500
Jerry  = 0
Spike  = +500
```

## Optimized Settlement

```
Tom pays Spike 500
```

## Output

```cpp
{
    {"Tom", "Spike", 500}
}
```

---

# Complexity Analysis

Let:

* T = Number of transactions
* P = Number of unique people

## Time Complexity

### Balance Computation

```
O(T)
```

Each transaction is processed exactly once.

### Settlement Generation

```
O(P)
```

Each debtor and creditor is visited at most once.

### Total Time Complexity

```
O(T + P)
```

---

## Space Complexity

Hash map and vectors store information about participants.

```
O(P)
```

---
