list=[]
n=int(input("Enter the length of list : "))
for i in range(0,n):
    list.append(int(input("Enter a value: ")))
print(list)
n1=int(input("Enter the index of first element to be swapped : "))
n2=int(input("Enter the index of second element to be swapped : "))
if n1 < 0 or n1 >= n or n2 < 0 or n2 >= n:
    print("Invalid indices provided. Exiting.")
else:
    # Swap the elements
    temp = list[n1]
    list[n1] = list[n2]
    list[n2] = temp
print(list)
