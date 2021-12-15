#!/usr/local/bin/python3

""" Types and Variables """

# Declared variables automatically infer types
x = 1

# Python is dynamically typed: variables can be re-assigned
# to a value of a different type
x = "Aa"

# Variables start with an underscore or letters
# followed by other letters, underscores, or digits.
# They're also case-sensitive and can't be reserved keywords.
#
# Good: _yo, hello, foo123
# Not good: 1a, *123*, int, list, def

# Immutable types cannot be modified after creation

answer_to_life = 42				# int
pi = 3.14159					# float
is_tired = True					# bool
greeting = "hello"				# str
directions = ('N', 'S', 'E', 'W')		# tuple

# Mutable types can be modified after creation

words = [3, "blind", "mice"]			# list
fruits = {1: "apple", 2: "banana"}		# dict
letters = set(['a', 'b', 'c'])  		# set

# Lists, dictionaries, and sets can be heterogeneous,
# a.k.a have elements of different types

nothing = None					# like NULL in C++


""" Conditionals and Logic """

# Booleans are spelled out: and, or, not
True and False
True or False
not False

# Use == for value equality
# Use "is" for object equality (compares in memory)
x = [1]
y = [2]
z = [1]

print(x == z)
print(x == y)

print(x is x)
print(x is z)

# Other comparators from C should look familiar
1 < 2
2 > 1
1 <= 2
1 >= 1
1 != 2


""" If Statements """

rainy = False
today = "Saturday"

if (today == "Saturday" or today == "Sunday") and not rainy:
	print("Go to the beach")
elif not rainy:
	print("Go to class")
else:
	print("Stay inside")


""" Strings """

# Single and double quotes are interchangeable
"string" == 'string'

# Split strings into lists using split()
"James Bond".split()
"1,2,3".split(',')

# Remove characters at the beginning and end of the string
txt = ".....bananas...."
print(txt.strip('.'), "are my favorite fruit")


""" For Loops """

result = 0

# Iterate through sequence i = 0, 1, 2, 3, 4
for i in range(5):
	print(i)
	result += i

print(result)


""" Lists """

my_list = []					# Declare empty list
l = [1, 2, "red", "green"]		# Declare (heterogeneous) list

len(l)							# List length (len() works on other sequences too)
"red" in l						# Check if list contains value

# Modifying Lists
l.remove("green") 				# Remove first occurence of "green"
l.append("blue") 				# Append "blue"
my_list.append("yellow")		# Append "yellow"
my_list.extend(l)  				# Merge two lists (can also use +=)

# Slicing [start:end:step]
l[0] 					# First item (at index 0)
l[2:4]					# Sublist with items 2 and 3
l[1:4:2]				# Every 2nd item between 1-3
l[::-1]					# Reverse list

# Slicing also works on strings and custom data structures

# Iterate through a list
for x in l:
	print(f"{x} fish")

# Use enumerate() to get both index and value
for (i, x) in enumerate(l):
	print(f"Index {i} and Value {x}")


""" Functions """

# This function works with ints, floats, strings, lists, etc.
# It also has multiple return types
def sum_or_same(a, b):
	if a is b:
		return "same"
	else:
		return a + b

sum_or_same(10, 10)
sum_or_same(10, 12)

sum_or_same(1, 2)
sum_or_same(1.2, 3.4)
sum_or_same(True, False)
sum_or_same("race", "car")
sum_or_same(["CS 31", "CS 32"], ["CS 35L", "CS 111"])

classes = ["CS 31", "CS 32"]

# Return "same" since both arguments reference the same object
sum_or_same(classes, classes)

# Return the sum since the two arguments reference two different lists,
# just with the same values. If the function used ==, this would return "same"
sum_or_same(["CS 31", "CS 32"], ["CS 31", "CS 32"])


""" Pass-by-Object Reference """

# Arguments are pass-by-object reference, so Python passes
# a new object that holds the same reference to the original variable.

# Example 1: The function modifies the list referenced by the original variable
# test list, so both my_list and test_list will print the same result
def fun_append(my_list):
	my_list.append(1)
	print("In function:", my_list)

test_list = [0]
fun_append(test_list)
print("Outside function: ", test_list)

# Example 2: The function changes my_list to reference a new value "123", but
# it won't modify test_list's reference to the original list
def fun_replace(my_list):
	my_list = 123
	print("In function:", my_list)

test_list = [0]
fun_replace(test_list)
print("Outside function: ", test_list)


""" Classes """

# An empty class
class Animal:
	pass


# Dog inherits from Animal
class Dog(Animal):
	# Constructor					
	def __init__(self, name, sound):
		# Create instance variables
		self.name = name
		self.sound = sound

	# Instance methods always pass self as first argument
	def bark(self):
		print(self.sound)


my_dog = Dog("Pluto", "woof")
print(my_dog.name)
my_dog.bark()


# Class and Static Variables/Methods
class DiscussionSection:
	section_count = 0 # class variable

	def __init__(self, number):
		DiscussionSection.section_count += 1
		self.number = 4

	# Static methods are called on the class
	@staticmethod
	def get_section_count1():
		return DiscussionSection.section_count

	# Class methods are like static methods,
	# but always pass class as first argument to make it easier
	@classmethod
	def get_section_count2(cls):
		return cls.section_count

cs35l = DiscussionSection(4)
DiscussionSection.section_count
DiscussionSection.get_section_count1()
DiscussionSection.get_section_count2()


""" Modules """

import random				# import module named "random"
from math import pi			# import only specific code from module
from sys import *			# imports entire module directly into file
import datetime as dt			# import module using custom name

x = random.randint(0, 10)		# call function in module
print(pi * x)  # Note: didn't need to specify module name
print(dt.datetime.now())


""" Deep vs. Shallow Copying """

from copy import copy, deepcopy

a = [1, 2, [3, 4]]

# A shallow copy constructs a new compound object and then (to the extent possible) inserts references into it to the objects found in the original.
b = copy(a)

# A deep copy constructs a new compound object and then, recursively, inserts copies into it of the objects found in the original.
c = deepcopy(a)

b[0] = 0
b[2][0] = 10

print(a)
print(b)
print(c)
