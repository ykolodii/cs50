from cs50 import get_string

while True:
    card_number = get_string("Number: ")
    if len(card_number) > 0:
        break

card_companies = [
    {"company": "VISA", "length": [13, 16], "first_two_digits": [40, 41, 42, 43, 44, 45, 46, 47, 48, 49]},
    {"company": "AMEX", "length": [15], "first_two_digits": [34, 37]},
    {"company": "MASTERCARD", "length": [16], "first_two_digits": [51, 52, 53, 54, 55]}
]

for company_info in card_companies:
    if len(card_number) in company_info["length"] and int(card_number[:2]) in company_info["first_two_digits"]:
        print(company_info["company"])
    else:
        print("INVALID")
