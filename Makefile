# Kalvin McCallum
# 01879187
# EECE 4811 Operating System & Kernel Design 
# Makefile
# The purpose of this file is to create the executable files for all programs used in assignment 1.

prog:
	gcc progA1.c -o progA1
	gcc progA2.c -o progA2
	gcc progB.c
	gcc progC.c -o progC

