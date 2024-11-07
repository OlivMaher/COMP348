#Contain code for UI (menu, various prompts, error message, and display final score)
from grid import *
import time
import os

def menu(grid):
    print("--------------------")
    print("|   Brain Buster   |")
    print("--------------------")
    grid.displayGrid()
    print("\n1. Let me select two elements")
    print("2. Uncover one element for me")
    print("3. I give up - reveal the grid")
    print("4. New game")
    print("5. Exit")

def selectTwo(grid):
    cell1 = input("Enter cell coordinates (e.g., a0): ")
    column1 = ord(cell1[:-1].lower()) - ord('a')
    row1 = int(cell1[1:])
    cell2 = input("Enter cell coordinates (e.g., a0): ")
    column2 = ord(cell2[:-1].lower()) - ord('a')
    row2 = int(cell2[1:])

    valueOfCell1 = grid.revealCell(column1, row1)
    valueOfCell2 = grid.revealCell(column2, row2)
    if valueOfCell1 != valueOfCell2:
        menu(grid)
        time.sleep(2)
        grid.hideCell(column1,row1)
        grid.hideCell(column2,row2)

def uncoverOne(grid):
    cell = input("Enter cell coordinates (e.g., a0): ")
    column = ord(cell[:-1].lower()) - ord('a')
    row = int(cell[1:])
    grid.revealCell(column,row)
    
def uncoverAll(grid):
    grid.revealAll()

#Implement Score
def main():
    grid = Grid(4)
    menu(grid)
    selection = int(input("Select: "))

    while selection != 5:
        if selection == 1:
            selectTwo(grid)
        elif selection == 2:
            uncoverOne(grid)
        elif selection == 3:
            uncoverAll(grid)
        elif selection == 4:
            grid.newGrid()
        
        os.system("cls")
        menu(grid)
        selection = int(input("Select: "))

if __name__ == "__main__":
    main()