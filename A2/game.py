#Contain code for UI (menu, various prompts, error message, and display final score)
from grid import *

def menu(grid):
    print("--------------------")
    print("|   Brain Buster   |")
    print("--------------------")
    print("    [A]  [B]  [C]  [D]")
    grid.displayGrid()
    print("\n1. Let me select two elements")
    print("2. Uncover one element for me")
    print("3. I give up - reveal the grid")
    print("4. New game")
    print("5. Exit")

def selectTwo():
    #Not case sensitive
    #The cells will be displayed for 2 seconds if incorrect
    #If the same value they will switch to the pairs
    cell1 = input("Enter cell coordinates (e.g., a0): ")
    cell2 = input("Enter cell coordinates (e.g., a0): ")

def uncoverOne():
    #Will uncover this cell
    cell = input("Enter cell coordinates (e.g., a0): ")

def main():
    grid = Grid(4)
    menu(grid)


if __name__ == "__main__":
    main()