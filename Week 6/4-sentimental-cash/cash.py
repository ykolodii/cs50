from cs50 import get_float

# Get the change owed
while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break

# Calculate how many coins you owe
#   - Quarters: 25,
#   - Dimes: 10,
#   - Nickels: 5,
#   - Pennies: 1
total_coins = 0
cents = round(change * 100)
coin_values = [25, 10, 5, 1]

# Iterate through coin values
for value in coin_values:
    total_coins += cents // value
    cents %= value

print(total_coins)
