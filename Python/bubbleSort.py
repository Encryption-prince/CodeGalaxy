def bubble_sort(list_values):
    n = len(list_values)
    for i in range(n):
        for j in range(0, n - i - 1):
            if list_values[j] > list_values[j + 1]:
                list_values[j], list_values[j + 1] = list_values[j + 1], list_values[j]

list_values = []
n = int(input("Enter the length of the list: "))
for i in range(n):
    list_values.append(int(input("Enter a value: ")))
print("Original list:", list_values)
bubble_sort(list_values)
print("Sorted list:", list_values)
print("The Smallest element in the list is : ",list_values[0])
print("The Second Smallest element in the list is : ",list_values[1])
print("The Largest element in the list is : ",list_values[-1])
print("The Second Largest element in the list is : ",list_values[-2])
