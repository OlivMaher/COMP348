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
    while True:
        cell1 = input("Enter cell coordinates (e.g., a0): ")
        column1 = ord(cell1[:-1].lower()) - ord('a')
        row1 = int(cell1[1:])
        cell2 = input("Enter cell coordinates (e.g., a0): ")
        column2 = ord(cell2[:-1].lower()) - ord('a')
        row2 = int(cell2[1:])
        if not grid.outOfRange(column1, row1) and not grid.outOfRange(column2, row2):
            valueOfCell1 = grid.revealCell(column1, row1)
            valueOfCell2 = grid.revealCell(column2, row2)
            if valueOfCell1 != valueOfCell2:
                menu(grid)
                time.sleep(2)
                grid.hideCell(column1,row1)
                grid.hideCell(column2,row2)
            break
        else:
            print("Input Error: Entry is out range for this grid. Please Try Again")


def uncoverOne(grid):
    while True:
        cell = input("Enter cell coordinates (e.g., a0): ")
        column = ord(cell[:-1].lower()) - ord('a')
        row = int(cell[1:])
        if not grid.outOfRange(column, row):
            grid.revealCell(column,row)
            break
        else:
            print("Input Error: Entry is out range for this grid. Please Try Again")
    
def uncoverAll(grid):
    grid.revealAll()

def main():
    numOfGuesses = 0
    uncoveredGrid = False

    # Get the size of the grid from the user
    while True:
        try:
            sizeOfGrid = int(input("Select the size of the grid (an even number 2-26): "))
            if 2 <= sizeOfGrid <= 26 and sizeOfGrid % 2 == 0:
                break
            elif sizeOfGrid % 2 == 1:
                print("Please enter an even number")
            else:
                print("Please enter a number between 2 and 26.")
        except ValueError:
            print("Invalid input. Please enter an integer between 2 and 26.")

    grid = Grid(sizeOfGrid)
    menu(grid)

    while True:
        try:
            selection = int(input("Select: "))
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 5.")
            continue

        if selection == 5:
            break

        if selection == 1:
            selectTwo(grid)
            numOfGuesses += 1
        elif selection == 2:
            uncoverOne(grid)
            numOfGuesses += 2
        elif selection == 3:
            uncoverAll(grid)
            uncoveredGrid = True
        elif selection == 4:
            grid.newGrid()
            numOfGuesses = 0
            uncoveredGrid = False
        else:
            print("Invalid selection. Please enter a number between 1 and 5.")
            continue

        os.system("cls")
        menu(grid)

        if grid.isWon():
            score = grid.calculateScore(numOfGuesses)
            if score == 0 or uncoveredGrid:
                print("You cheated, your score is zero")
            else:
                print("Congrats you won! Your score is ", score)
            playAgain = input("Would you like to play again (y or n): ")
            if playAgain.lower() == "n":
                break
            elif playAgain.lower() == "y":
                grid.newGrid()
                menu(grid)
                numOfGuesses = 0
                uncoveredGrid = False

if __name__ == "__main__":
    main()