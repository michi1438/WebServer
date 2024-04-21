import os
import sys

#!/usr/bin/env python3

# print("REQUEST_METHOD: ", os.environ.get('REQUEST_METHOD'))
# print("SCRIPT_FILENAME: ", os.environ.get('SCRIPT_FILENAME'))
# print("QUERY_STRING: ", os.environ.get('QUERY_STRING'))
# print("CONTENT_LENGTH: ", os.environ.get('CONTENT_LENGTH'))
# print("CONTENT_TYPE: ", os.environ.get('CONTENT_TYPE'))
# print("<br>")

# Get the command line arguments
num1 = int(sys.argv[1])
num2 = int(sys.argv[2])
oprtr = sys.argv[3]

if num1 == 0 and num2 == 0 and oprtr == '%2B':
    b = "La tete a Toto"
elif oprtr == '%2B':
    b = num1 + num2
elif oprtr == '-':
    b = num1 - num2
elif oprtr == '*':
    b = num1 * num2
elif oprtr == '%2F' and num2 != 0:
    b = num1 / num2
else:
    b = "ERROR BATARD(le prend pas mal hein, c'est juste pour rire, je t'aime bien quand même)"

a = """
<!DOCTYPE html>
<html>
<head><title>CALCULETTE DE LA MORT</title></head>
<body>
<h1>CALCULETTE DE LA MORT</h1>
<p>{0} {3} {1} = {2}</p>
</body>
</html>
""".format(num1, num2, b, oprtr)

print(a)